/*
 * Prolifer.c
 *
 * Created: 2018-06-15 16:12:05
 *  Author: para2709
 */ 

#include <avr/io.h>
#include "Profiler.h"

bool writeData(void){
	return FALSE;
}

bool isInteracted(void){
	return FALSE;
}

void profiler(void){
	while(1){
		//Wait for interaction
		isInteracted();
	}
}