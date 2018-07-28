/*
 * gui.c
 *
 * Created: 7/26/2018 3:55:46 PM
 *  Author: antho
 */ 
#include "gui.h"

//Repetitive functions
void printString(char* s){
	while( *s != (char)0 ){
			UDR1 = *s++;
			while(!(UCSR1A & (0x01 << UDRE1)));
	}
	s = NULL;
}

void printGuiHeaders(){
	printString("\n\r--------------------P R O J E C T  P R O L I F E R--------------------\n\r");
}

void printSeparator(){
	printString("\n\r**********************************************************************\n\r");
}


//GUI
bool openingMenu(){
	printGuiHeaders();
	
	
	while(1){
		printString("\n\rENTER USERNAME :");
	
	}
	
	return false;
}