/*
 * Uart.h
 */ 

#ifndef UART_H_
#define UART_H_

void UartInit(uint32_t baudrate);
void UartWriteByte(uint8_t byte);
void Uart_Tx_data(void);
void Check_Received_Bytes(void);

// tx_fifo_empty is a flag indicating there
// are no more characters to transmit
extern volatile uint8_t tx_fifo_empty;

// machine_current_state lets the application
// determine what state it is in and whether
// or not to accept an <enter> or <esc> character
extern volatile uint8_t machine_current_state;

// turn_on_the_machine is a flag indicating
// whether or not to get ambient light level
extern volatile uint8_t turn_on_the_machine;

#define F_CPU 8000000

#endif /* UART_H_ */