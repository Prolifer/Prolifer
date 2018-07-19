/*
 * Timer.c
 */ 

#include <avr/interrupt.h>
#include "Timer.h"

volatile uint16_t ms; // keep track of the number of ms that have passed
volatile uint8_t timer_flag; // used to flag when APP_DELAY has been reached

void Timer_Init(void) {
	ms = 0;
	TIMSK1 = 0x00;	//Disable timer interrupts
	TCCR1A = 0x00;	//Timer not connected to any pins
	TCNT1 = 0x0000; //Clear timer
	OCR1A = 1000;	//Set interrupt period to 1000us
	TCCR1B = 0x0A;	//CTC mode; Timer_Rate = System_CLK/8 = 1MHz
	// 1 tick = 1 us
	TIMSK1 = 0x02;	//Enable OCIE1A Interrupt
	
}

ISR(TIMER1_COMPA_vect) {
	ms++; // 1000us have passed
	
	// if APP_DELAY has been reached
	if(ms == APP_DELAY) {
		ms = 0; // reset ms
		timer_flag = 1; // set flag
	}
}