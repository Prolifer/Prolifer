/*
 * Profiler.h
 *
 * Created: 7/4/2018 10:59:47 AM
 *  Author: antho
 */ 


#ifndef PROFILER_H_
#define PROFILER_H_

#include "credentials.h"
#include "definitions.h"

bool writeData(void);
bool eraseData(void);
bool readData(void);
bool symbolToData(void);
bool isCredentialSufficient(enum credential c);
bool encryption(void);
bool decryption(void);
bool writingLED_ON(void);
bool readingLED_ON(void);
bool writingLED_OFF(void);
bool readingLED_OFF(void); 

#endif /* PROFILER_H_ */