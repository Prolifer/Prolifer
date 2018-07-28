/*
 * user.h
 *
 * Created: 7/26/2018 3:51:18 PM
 *  Author: antho
 */ 


#ifndef USER_H_
#define USER_H_

enum Credential{CIVILIAN,PROFESSIONAL,AUTHORITARIAN};
enum IDType{PUBLIC,PRIVATE,HEALTH,FINANCIAL,ALL};
enum Information{PRENOM,NOM,AGE,END};

//Target:	Person or entity which we try to obtain infos from.
//			Target's functions usually cannot be used by normal
//			civilians, but more by professional and authoritarian.

//Read  
void readTargetPublicID();
void readTargetPrivateID();
void readTargetHealthID();
void readTargetFinancialID();
void readTargetAllID();

//Write (Reserved to Professional and Authoritarian)
void writeTargetPublicID();
void writeTargetPrivateID();
void writeTargetHealthID();
void writeTargetFinancialID();
void writeTargetAllID();

#endif /* USER_H_ */