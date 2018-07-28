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
	bool isSessionOpened = false;
	char option = '0';
	
	while((option != '1' || option != '2') && isSessionOpened){
		printGuiHeaders();
		printString("\n\r");
		printString("SELECT OPTION: \n\r\t1 - OPEN SESSION \n\r\t2 - EXIT");
		printString("\n\r");
		printString("OPTION : ");
		
		option = getchar();
		
		switch (option)
		{
			case '1':
				isSessionOpened = openingSession();
				break;
			case '2':
				return false;
				break;
			default:
				break;
		}
	}
	return false;
}

bool openingSession(){
		char username[100];
		char password[100];
		 
		int tries = 3;
		while(tries > 0){
			printSeparator();
			printString("\n\rOPEN SESSION\n\r");
			printString("\n\r\tENTER USERNAME : ");
			gets(username);
			printString("\n\r");
			printString("\n\r\tENTER PASSWORD : ");
			gets(password);
			printSeparator();
			if(isUserExisting(username,password)){ return true;}
				
			tries--;
		}
		return false;
}