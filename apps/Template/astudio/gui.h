/*
 * gui.h
 *
 * Created: 7/26/2018 3:55:38 PM
 *  Author: antho
 */ 


#ifndef GUI_H_
#define GUI_H_

#include <stdbool.h>
#include <string.h>
#include "sys.h"
#include "phy.h"
#include "user.h"

#define READ_STRING_ARRAY_LENGTH 101
#define READ_CHAR_ARRAY_LENGTH 2

//Repetitive functions
void printString(char* s);
void printGuiHeaders();
void printSeparator();

void readChar();
void parseToCharBuffer(char c); //TODO: Correct the function to make it act as a scanf(), getchar(), etc.
void readString();
void parseToStringBuffer(char* s);//TODO: Correct the function to make it act as a (f)scanf(), gets(), etc.

//GUI
bool openingMenu();
bool openingSession();




#endif /* GUI_H_ */