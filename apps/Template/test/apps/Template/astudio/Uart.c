/*
 * Uart.c
 */ 

#include <avr/interrupt.h>
#include <stdbool.h>
#include "Uart.h"
#include "Timer.h"

// Max number of characters
#define HAL_UART_TX_FIFO_SIZE 200

// generic fifo struct
typedef struct
{
	uint16_t  head;
	uint16_t  tail;
	uint16_t  size;
	uint16_t  bytes;
	uint8_t   *data;
} FifoBuffer_t;

// Declare transmit fifo buffer
static FifoBuffer_t txFifo;
static uint8_t txData[HAL_UART_TX_FIFO_SIZE+1];

// udrEmpty is a flag used to ensure udr is empty before
// loading with new character
static volatile bool udrEmpty;

// tx_fifo_empty is a flag indicating there are no more
// characters to transmit
volatile uint8_t tx_fifo_empty;

// used to store received character and decide what to do with it
uint8_t received_character;

// flag used to indicate a character has been received
uint8_t rx_flag;

// embedded state machine variables
volatile uint8_t machine_current_state;
volatile uint8_t turn_on_the_machine;

void UartInit(uint32_t baudrate)
{
	// calculate value to load in baud rate register
	uint32_t brr = ((uint32_t)F_CPU * 2) / (16 * baudrate) - 1;
	
	// load baud rate register with calculated value
	UBRR1H = (brr >> 8) & 0xff;
	UBRR1L = (brr & 0xff);
	
	// enable double speed mode
	UCSR1A = (1 << U2X1);
	
	// enable transmitter, enable receiver, enable receive complete interrupt
	UCSR1B = (1 << TXEN1) | (1 << RXEN1) | (1 << RXCIE1);
	
	// enable asynch mode, no parity, 1 stop-bit, 8-bit data, default clock polarity
	UCSR1C = (3 << UCSZ10);
	
	// initialize tx fifo parameters
	txFifo.data = txData;
	txFifo.size = HAL_UART_TX_FIFO_SIZE;
	txFifo.bytes = 0;
	txFifo.head = 0;
	txFifo.tail = 0;
	
	// clear flags
	tx_fifo_empty = 1;
	rx_flag = 0;
	udrEmpty = true;
}

void UartWriteByte(uint8_t byte){
	if (txFifo.bytes == txFifo.size) // if fifo is full
	return;
	
	// Add byte to tx fifo
	txFifo.data[txFifo.tail++] = byte;
	if (txFifo.tail == txFifo.size) // if fifo index is maxed out
	txFifo.tail = 0; // reset index
	
	txFifo.bytes++; // increment index
	tx_fifo_empty = 0; // ensure tx_fifo_empty flag is cleared
}

// UDR empty interrupt handler
ISR(USART1_UDRE_vect)
{
	udrEmpty = true; //usart data reg is empty
	UCSR1B &= ~(1 << UDRIE1); //disable UDR empty interrupt
}

// USART receive complete interrupt handler
ISR(USART1_RX_vect)
{
	uint8_t status = UCSR1A; //store status bits

	if (0 == (status & ((1 << FE1) | (1 << DOR1) | (1 << UPE1)))) // if there are no errors
	{
		received_character = UDR1; // save received character
		rx_flag = 1; // set character received flag
	}
}

void Uart_Tx_data(void)
{
	if (txFifo.bytes && udrEmpty) // if tx fifo has something to transmit
	// and we aren't going to overwrite anything in the USART data reg
	{
		uint8_t byte;
		
		byte = txFifo.data[txFifo.head++]; // load first byte in fifo
		if (txFifo.head == txFifo.size) // if head is at the end, reset to 0
		txFifo.head = 0;
		txFifo.bytes--; // decrement number of bytes in fifo

		UDR1 = byte; // put byte in UDR to be transmitted
		UCSR1B |= (1 << UDRIE1); // enable UDR empty interrupt to indicate transmission completed
		udrEmpty = false; // clear udrEmpty flag
	}
	
	if(txFifo.bytes == 0) { // if there is nothing to transmit
		tx_fifo_empty = 1; // set tx fifo empty flag
	}
}

void Check_Received_Bytes(void) {
	
	if(rx_flag) { // if a character has been received
		
		if(machine_current_state == 0) { // if the machine is currently off
			if( received_character == '\r' ) { // if <enter> was pressed
				turn_on_the_machine = 1; // set start signal
				}else{
				// ignore other characters - do nothing
			}
			}else{ // if machine is currently on
			if( received_character == '\e' ) { // if <esc> was pressed
				turn_on_the_machine = 0; // set stop signal
			}
		}
		
		rx_flag = 0; // reset rx_flag
		
		}else{
		// Didn't receive any characters - do nothing
		return;
	}
}