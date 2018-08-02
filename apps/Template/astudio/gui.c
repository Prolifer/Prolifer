/*
 * gui.c
 *
 * Created: 7/26/2018 3:55:46 PM
 *  Author: antho
 */ 

#include "gui.h"

//Definitions
#define READ_STRING_ARRAY_LENGTH 101
	//ASCII CODE
#define ASCII_CARRIAGE_RETURN (char)10
#define ASCII_NULL (char)0

//Global variables
//char s_buffer[READ_STRING_ARRAY_LENGTH] = "\0";

//Repetitive functions
void printString(char* s){
	char* buff = s;
	while( *buff != (char)0){
			UDR1 = *buff++;
			while(!(UCSR1A & (0x01 << UDRE1)));
	}
	s = NULL;
	buff = NULL;
}

void printGuiHeaders(){
	printString("\n\r--------------------P R O J E C T  P R O L I F E R--------------------\n\r");
}

void printSeparator(){
	printString("\n\r**********************************************************************\n\r");
}

char readChar(){
	char c_buffer = ASCII_NULL;
	return parseToCharBuffer(c_buffer);
}

char parseToCharBuffer(char c_buffer){
	while(c_buffer == ASCII_NULL){
		if(UCSR1A & (0x01 << RXC1))	{c_buffer = UDR1;}
	}
	return c_buffer;
}

void readString(char* s_buffer){

	//char c_buffer;
	//memset(s_buffer, 0, sizeof(s_buffer));
	//int i = 0;
	//
	//while(i < (READ_STRING_ARRAY_LENGTH - 1) || (c_buffer != (char)10 && c_buffer != (char)13)){
		//c_buffer = ASCII_NULL;
		//c_buffer = readChar();
		//if(c_buffer != (char)0 && c_buffer != (char)10 && c_buffer != (char)13){ 
			//s_buffer[i] = c_buffer;
			//i++;
		//}
	//}
	//
	//return s_buffer;
	
	
	//memset(s_buffer, 0, sizeof(s_buffer));
	//char  c = '\0';
	//int i = 0;
	//
	////TODO: Probably add something to clear buffers to assure correct buffing
	//
	//while(s_buffer[i] != '\r' && i < (READ_STRING_ARRAY_LENGTH - 1)){
		//if(UCSR1A & (0x01 << RXC1))	{c = UDR1;}
		//if(c != 0){
			//s_buffer[i] = c;
			////TODO: Probably add something to clear buffers to assure correct buffing
			//i++;
		//}
	//}	
	//return s_buffer;
	
	memset(s_buffer, 0, READ_STRING_ARRAY_LENGTH*sizeof(char));
	char temp = 0;
	int i = 0;
	while(i < (READ_STRING_ARRAY_LENGTH - 1) && temp != '\r'){
		temp = readChar();
		if(temp != 0){
			*s_buffer = temp;
			s_buffer++;
			i++;
		}
	}
	*s_buffer = '\0';
	
}


//GUI
bool openingMenu(){
	bool isSessionOpened = false;
	char option = '\0';
	
	while((option != '1' || option != '2') && !isSessionOpened){
		printGuiHeaders();
		printString("\n\r");
		printString("SELECT OPTION: \n\r\t1 - OPEN SESSION \n\r\t2 - EXIT");
		printString("\n\r");
		printString("OPTION : ");
		option = readChar();

		switch (option)
		{
			case '1':
				isSessionOpened = openingSession();
				break;
			case '2':
				printString("\n\r\n\rEXITING ...\n\r\n\r");
				return false;
				break;
			default:
				break;
		}
	}
	return true;
}

bool openingSession(){
		char username[READ_STRING_ARRAY_LENGTH];
		char password[READ_STRING_ARRAY_LENGTH];
		 
		int tries = 3;
		while(tries > 0){
			printSeparator();
			printString("\n\r\t--OPEN SESSION--\n\r");
			printString("\n\r\tENTER USERNAME : ");
			readString(username);
			printString("\n\r");
			printString("\n\r\tENTER PASSWORD : ");
			readString(password);
			printSeparator();
			
			if(identifyUser(username,password)){ 
				printString("\n\r\tUSER IDENTIFIED!\n\r");
				return true;
			}
				
			tries--;
		}
		return false;
}