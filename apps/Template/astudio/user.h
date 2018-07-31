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

//enum IDType{PUBLIC,PRIVATE,HEALTH,FINANCIAL,ALL}; TODO: if time , iteration to implement
enum Credential{NOTHING,CIVILIAN,PROFESSIONAL,AUTHORITARIAN} User_Type;
enum Information{PRENOM,NOM,DATE_NAISSANCE,ADRESSE,APPARTEMENT,VILLE,PAYS,PROVINCE,CODE_POSTAL,SOIN_PARTICULIER,MEDICAMENT,MALADIE,COMMENTAIRE,GROUPE_SANGUIN,END,CREDENTIAL} Access[20];

//Definitions of terms :
//Target:	Person or entity which we try to obtain infos from.
//			Target's functions usually cannot be used by normal
//			civilians, but more by professional and authoritarian.

//Write to UART
void Ecris_UART(char data);

//User ID
bool identifyUser();

void Creer_Paquet(char * ptr, size_t n_elements);
void Decortiquer_Paquet(char * Data);
void readData(int Type);

//Read  //TODO: Implement those functions, if time
void readTargetPublicID();
void readTargetPrivateID();
void readTargetHealthID();
void readTargetFinancialID();
void readTargetAllID();

//Write (Reserved to Professional and Authoritarian) //TODO: Implement those functions, if time
void writeTargetPublicID();
void writeTargetPrivateID();
void writeTargetHealthID();
void writeTargetFinancialID();
void writeTargetAllID();

#endif /* USER_H_ */