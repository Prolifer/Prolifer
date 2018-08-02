/*
 * user.h
 *
 * Created: 7/26/2018 3:51:18 PM
 *  Author: antho
 */ 

#ifndef USER_H_
#define USER_H_

#include <stdbool.h>
#include <stddef.h>
#include "gui.h"



//Definitions
#define READ_STRING_ARRAY_LENGTH 101

//TODO: if time , iteration to implement
//enum IDType{PUBLIC,
	//PRIVATE,
	//HEALTH,
	//FINANCIAL,
	//ALL}; 
	
typedef enum Credentials{
	NOTHING,
	CIVILIAN,
	PROFESSIONAL,
	AUTHORITARIAN
	} Credential;
	
enum DataTypeHeader{
	PRENOM,
	NOM,
	DATE_NAISSANCE,
	ADRESSE,
	APPARTEMENT,
	VILLE,
	PAYS,
	PROVINCE,
	CODE_POSTAL,
	SOIN_PARTICULIER,
	MEDICAMENT,
	MALADIE,
	COMMENTAIRE,
	GROUPE_SANGUIN,
	END,
	CREDENTIAL,
	ERROR,
	ACKNOWLEDGE
} Access[20];

typedef struct UserProfils{
	char username[READ_STRING_ARRAY_LENGTH];
	char password[READ_STRING_ARRAY_LENGTH];
	char credential;
} UserProfil;

//UserProfil profils[1] = {
	//{civ.username,civ.password,civ.credential}
//};


//Global variables
//UserProfil up = {
	//.username = "",
	//.password = "",
	//.credential = NOTHING
//} ;

//Definitions of terms :
//Target:	Person or entity which we try to obtain infos from.
//			Target's functions usually cannot be used by normal
//			civilians, but more by professional and authoritarian.

void Ecris_UART(char data);
bool identifyUser();
void initPossibleProfils();
void readSelfData(int ClientCredential);
void SendPackage(char * ptr, size_t n_elements);
void Decortiquer_Paquet(char * Data);
void Acknowledge_Paquet();

//Definition of terms :
//Target:	Person or entity which we try to obtain infos from.
//			Target's functions usually cannot be used by normal
//			civilians, but more by professional and authoritarian.

//Read  //TODO: Implement those functions, if time
void requestTargetAllID(UserProfil up);
void requestTargetPublicID();
void requestTargetPrivateID();
void requestTargetHealthID();
void requestTargetFinancialID();

//Write (Reserved to Professional and Authoritarian) //TODO: Implement those functions, if time
void writeTargetFirstName(UserProfil up, char* firstName);

void writeTargetAllID();
void writeTargetPublicID();
void writeTargetPrivateID();
void writeTargetHealthID();
void writeTargetFinancialID();

#endif /* USER_H_ */