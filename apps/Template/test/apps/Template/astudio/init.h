/*
 * init.h
 *
 * Created: 7/15/2018 4:14:08 PM
 *  Author: antho
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "Uart.h"

#ifndef INIT_H_
#define INIT_H_

void init(void);
void Board_Init(void);

#endif /* INIT_H_ */