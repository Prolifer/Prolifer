/*
 * init.c
 *
 * Created: 7/15/2018 4:16:43 PM
 *  Author: antho
 */ 
#include "init.h"

void init(void){
		// Running off 16MHz Crystal
		// Change System Clock to 8MHz
		// Note: this overrides CKDIV8 fuse setting
		CLKPR = 0x80; // enable CLKPR change
		CLKPR = 0x01; // set division factor to /2
		
		Board_Init(); // Initialize LED pin, Start Button, ADC pin, and embedded state machine
		Timer_Init(); // Initialize 16-bit Timer
		UartInit(38400); // Initialize UART at 38400 baud
		
		// Start Button/Wait LED
		// This allows user to plug-in board, setup terminal window, and wait for
		// button press before the welcome and instruction strings are printed
		PORTB &= ~(1 << 4); // Turn on LED
		while(PINE & 0x10); // wait for user to press start button (SW0)
		PORTB |= (1 << 4); // Turn off LED
		
		sei(); // enable global interrupts
}

void Board_Init(void) {
	cli(); // Disable interrupts
	
	// Disable watchdog timer
	asm("wdr");
	MCUSR = 0;
	WDTCSR |= (1 << WDCE) | (1 << WDE);
	WDTCSR = 0x00;
	
	// Configure LED pin
	DDRB = 0x10; //PB4 output
	PORTB |= 0x10; //Turn off LED
	
	// Configure "Start Button" pin
	DDRE &= ~0x10; //PE4 input
	PORTE |= 0x10; //Enable pull-up resistor
	
	// Configure ADC pin
	// Interface with Light sensor on I/O expansion card
	DDRF &= ~0x01; //PF0 input
	
	// Initialize state machine
	machine_current_state = 0; // off
	turn_on_the_machine = 0; // no start signal
}