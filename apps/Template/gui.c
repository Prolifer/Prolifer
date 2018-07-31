/*
 * gui.c
 *
 * Created: 7/26/2018 3:55:46 PM
 *  Author: antho
 */ 

#include "gui.h"

//Global variables
char c_buffer = '\0';
char s_buffer[READ_STRING_ARRAY_LENGTH] = "\0";

//Repetitive functions
void printString(char* s){
	char* buff = s;
	while( *buff != (char)0 || *buff != '\0' ){
			UDR1 = *buff++;
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

void readChar(){
	c_buffer = '\0';
	parseToCharBuffer(c_buffer);
}

//TODO: Correct the function to make it act as a scanf(), gets(), etc.
void parseToCharBuffer(char c_buffer){
	char s[READ_CHAR_ARRAY_LENGTH] = "\0";
	int i = 0;
	
	//TODO: Probably add something to clear buffers to assure correct buffing
	
	while(s[READ_CHAR_ARRAY_LENGTH - 1] != '\r'){
		if(UCSR1A & (0x01 << RXC1))	{c_buffer = UDR1;}
		if(c_buffer != 0){
			s[i] = c_buffer;
			//TODO: Probably add something to clear buffers to assure correct buffing
			i++;
			if(i >= READ_CHAR_ARRAY_LENGTH){ i = 0;}
		}
	}
}

void readString(){
		memset(s_buffer, 0, sizeof(s_buffer));
		parseToStringBuffer(s_buffer);
}

//TODO: Correct the function to make it act as a scanf(), gets(), etc.
void parseToStringBuffer(char* s_buffer){
	char  c = '\0';
	int i = 0;
	
	//TODO: Probably add something to clear buffers to assure correct buffing
	
	while(s_buffer[READ_STRING_ARRAY_LENGTH - 1] != '\r'){
		if(UCSR1A & (0x01 << RXC1))	{c = UDR1;}
		if(c != 0){
			s_buffer[i] = c;
			//TODO: Probably add something to clear buffers to assure correct buffing
			i++;
			if(i >= READ_STRING_ARRAY_LENGTH){ i = 0;}
		}
	}
	s_buffer[READ_STRING_ARRAY_LENGTH - 1] = '\0';
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
		readChar();
		option = c_buffer;
		
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
		char* username;
		char* password;
		 
		int tries = 3;
		while(tries > 0){
			printSeparator();
			printString("\n\rOPEN SESSION\n\r");
			printString("\n\r\tENTER USERNAME : ");
			readString();
			username = s_buffer;
			printString("\n\r");
			printString("\n\r\tENTER PASSWORD : ");
			readString();
			password = s_buffer;
			printSeparator();
			if(isUserExisting(username,password)){ return true;}
				
			tries--;
		}
		return false;
}