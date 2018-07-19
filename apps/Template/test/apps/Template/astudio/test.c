/*
 * test.c
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "Uart.h"
#include "init.h"

// Function Prototypes
uint8_t conv_digit_to_ascii(uint16_t val);

// Header strings
uint8_t message[] = "CONSOLE CONTROL WORKS\n\n";

// Formatting Variable
uint8_t indent = 5;

int main(void)
{
	uint8_t i;
	
	init();
	
	while(1){
		//Test
		for(i=0; i<(sizeof(message)); i++){
			UartWriteByte(message[i]);
		}

		while(!tx_fifo_empty){
			// Transmit characters until buffer is empty
			Uart_Tx_data();
		}
	}
}

// This function is used to convert the character to its ASCII value.
uint8_t conv_digit_to_ascii(uint16_t val) {
	if (val<= 0x09) {
		val = val + 0x30;
	}
	if ((val >= 0x0A) && (val<= 0x0F)) {
		val = val + 0x37;
	}
	return val;
}