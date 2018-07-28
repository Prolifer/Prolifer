/*
 * gui.c
 *
 * Created: 7/26/2018 3:55:46 PM
 *  Author: antho
 */ 
#include "gui.h"

//Defines
#define NULL 0

void printString(char* s){
	while( *s != (char)0 ){
			UDR1 = *s++;
			while(!(UCSR1A & (0x01 << UDRE1)));
	}
	s = NULL;
}

void startGUI(){
	printString("\n\r--------------------P R O J E C T  P R O L I F E R--------------------\n\r");
}


