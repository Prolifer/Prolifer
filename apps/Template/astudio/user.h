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

//TODO: if time , iteration to implement
//enum IDType{PUBLIC,
	//PRIVATE,
	//HEALTH,
	//FINANCIAL,
	//ALL}; 
	
enum Credential{
	NOTHING,
	CIVILIAN,
	PROFESSIONAL,
	AUTHORITARIAN
	} User_Type;
	
enum Information{
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
	CREDENTIAL
} Access[20];

//Definitions of terms :
//Target:	Person or entity which we try to obtain infos from.
//			Target's functions usually cannot be used by normal
//			civilians, but more by professional and authoritarian.

void Ecris_UART(char data);

bool identifyUser();
Credential readSelfCredential();
void readSelfData(int Type);
void Creer_Paquet(char * ptr, size_t n_elements);
void Decortiquer_Paquet(char * Data);

//Read  //TODO: Implement those functions, if time
void requestTargetAllID();
void requestTargetPublicID();
void requestTargetPrivateID();
void requestTargetHealthID();
void requestTargetFinancialID();

//Write (Reserved to Professional and Authoritarian) //TODO: Implement those functions, if time
void writeTargetAllID();
void writeTargetPublicID();
void writeTargetPrivateID();
void writeTargetHealthID();
void writeTargetFinancialID();

#endif /* USER_H_ */