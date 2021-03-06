/*
 * Timer.h
 */ 


#ifndef TIMER_H_
#define TIMER_H_

// APP_DELAY defines the delay between ADC readings
#define APP_DELAY 1000 //ms

void Timer_Init(void);
void Delay(uint16_t us);

extern volatile uint8_t timer_flag;

#endif /* TIMER_H_ */