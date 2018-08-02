/*
 * Timer.h
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "stdint-gcc.h"

// APP_DELAY defines the delay between ADC readings
#define APP_DELAY 1 //ms

void Timer_Init(void);
void Delay(uint16_t us);

extern volatile uint8_t timer_flag;

#endif /* TIMER_H_ */