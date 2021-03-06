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

//Repetitive functions
void printString(char* s);
void printGuiHeaders();
void printSeparator();

char readChar();
char parseToCharBuffer(char c);
void readString(char* s_buffer);

//GUI
int openingMenu();
int openingSession();

#endif /* GUI_H_ */