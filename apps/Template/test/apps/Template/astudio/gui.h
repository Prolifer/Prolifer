/*
 * gui.h
 *
 * Created: 7/26/2018 3:55:38 PM
 *  Author: antho
 */ 


#ifndef GUI_H_
#define GUI_H_

#include <stdbool.h>
#include "sys.h"
#include "phy.h"
#include "user.h"

#define NULL 0

//Repetitive functions
void printString(char* s);
void printGuiHeaders();
void printSeparator();

//GUI
bool openingMenu();
bool openingSession();




#endif /* GUI_H_ */