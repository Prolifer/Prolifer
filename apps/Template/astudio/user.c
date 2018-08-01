/*
 * user.c
 *
 * Created: 7/26/2018 3:51:29 PM
 *  Author: antho
 */ 

#include "user.h"
#include "sys.h"
#include "phy.h"
#include "Timer.h"
#include <string.h>
#include "dummies.h"

#define Longueur_Paquet 200
#define Longueur_Entete 11

char Paquet[Longueur_Paquet];
int Nombre_Info = 0;
int Numero_Paquet = 0;

void Ecris_UART(char data)
{
	UDR1 = data;
	while(!(UCSR1A & (0x01 << UDRE1)));
}

//User ID
bool identifyUser(char* username, char* password){
	printString("\n\r\n\rIDENTIFYING USER...");
	//TODO : Implement logic with dummy
	return false;
}

Credential readSelfCredential(){
	return AUTHORITARIAN;
}

void readSelfData(int Type)
{
	Nombre_Info = 0;
	
	if (Type == CIVILIAN)
	{
		Access[0] = PRENOM;
		Access[1] = NOM;
		Access[2] = DATE_NAISSANCE;
		Access[3] = ADRESSE;
		Access[4] = APPARTEMENT;
		Access[5] = VILLE;
		Access[6] = PAYS;
		Access[7] = CODE_POSTAL;
		Access[8] = END;
		Nombre_Info = 8;
	}
	else if (Type == PROFESSIONAL || Type == AUTHORITARIAN )
	{
		Access[0] = PRENOM;
		Access[1] = NOM;
		Access[2] = DATE_NAISSANCE;
		Access[3] = ADRESSE;
		Access[4] = APPARTEMENT;
		Access[5] = VILLE;
		Access[6] = PAYS;
		Access[7] = CODE_POSTAL;
		Access[8] = SOIN_PARTICULIER;
		Access[9] = MEDICAMENT;
		Access[10] = MALADIE;
		Access[11] = COMMENTAIRE;
		Access[12] = GROUPE_SANGUIN;
		Access[13] = END;
		Nombre_Info = 13;
	}
	else
	{
		Access[0] = ERROR;
		Access[1] = END;
		Nombre_Info = 1;
	}
	
	size_t N_Elements = 0;
	
	for(int i=0;i<=Nombre_Info;i++)
	{
		Numero_Paquet = 0;
		memset(Paquet, '\0', Longueur_Paquet);
		Paquet[0] = 'P';
		Paquet[1] = '3';
		Paquet[2] = Access[i]/10;
		Paquet[3] = Access[i]%10;
		switch(Access[i])
		{
			case PRENOM :
			N_Elements = sizeof(Prenom) / sizeof(Prenom[0]);
			Creer_Paquet(Prenom,N_Elements);
			break;
			
			case NOM :
			N_Elements = sizeof(Nom) / sizeof(Nom[0]);
			Creer_Paquet(Nom,N_Elements);
			break;
			
			case DATE_NAISSANCE :
			N_Elements = sizeof(Date_Naissance) / sizeof(Date_Naissance[0]);
			Creer_Paquet(Date_Naissance,N_Elements);
			break;
			
			case ADRESSE :
			N_Elements = sizeof(Adresse) / sizeof(Adresse[0]);
			Creer_Paquet(Adresse,N_Elements);
			break;
			
			case APPARTEMENT :
			N_Elements = sizeof(Appartement) / sizeof(Appartement[0]);
			Creer_Paquet(Appartement,N_Elements);
			break;
			
			case VILLE :
			N_Elements = sizeof(Ville) / sizeof(Ville[0]);
			Creer_Paquet(Ville,N_Elements);
			break;
			
			case PAYS :
			N_Elements = sizeof(Pays) / sizeof(Pays[0]);
			Creer_Paquet(Pays,N_Elements);
			break;
			
			case PROVINCE :
			N_Elements = sizeof(Province) / sizeof(Province[0]);
			Creer_Paquet(Province,N_Elements);
			break;
			
			case CODE_POSTAL :
			N_Elements = sizeof(Code_Postale) / sizeof(Code_Postale[0]);
			Creer_Paquet(Code_Postale,N_Elements);
			break;
			
			case SOIN_PARTICULIER :
			N_Elements = sizeof(Soin_Particulier) / sizeof(Soin_Particulier[0]);
			Creer_Paquet(Soin_Particulier,N_Elements);
			break;
			
			case MEDICAMENT :
			N_Elements = sizeof(Medicament) / sizeof(Medicament[0]);
			Creer_Paquet(Medicament,N_Elements);
			break;
			
			case MALADIE :
			N_Elements = sizeof(Maladie) / sizeof(Maladie[0]);
			Creer_Paquet(Maladie,N_Elements);
			break;
			
			case COMMENTAIRE :
			N_Elements = sizeof(Commentaire) / sizeof(Commentaire[0]);
			Creer_Paquet(Commentaire,N_Elements);
			break;
			
			case GROUPE_SANGUIN :
			N_Elements = sizeof(Groupe_Sanguin) / sizeof(Groupe_Sanguin[0]);
			Creer_Paquet(Groupe_Sanguin,N_Elements);
			break;
			
			case ERROR :
			N_Elements = sizeof(Error) / sizeof(Error[0]);
			Creer_Paquet(Error,N_Elements);
			break;
		
			case END :
			Creer_Paquet("",0);
			break;
			
			default :
			break;
		}
	}
}

void Creer_Paquet(char * ptr, size_t n_elements)
{
	Numero_Paquet++;
	
	Paquet[4] = (n_elements + Longueur_Entete)/100;
	Paquet[5] = ((n_elements + Longueur_Entete)%100)/10;
	Paquet[6] = ((n_elements + Longueur_Entete)%100)%10;
	
	Paquet[7] = Numero_Paquet/10;
	Paquet[8] = Numero_Paquet%10;

	Paquet[9] = Nombre_Info/10;
	Paquet[10] = Nombre_Info%10;

	for (int i = 0;i<n_elements;i++)
	{
		Paquet[i+Longueur_Entete] = ptr[i];
	}
	Ecris_Wireless(Paquet,n_elements + Longueur_Entete);
}

void Decortiquer_Paquet(char * Data)
{
	char Entete[Longueur_Entete];
	char Donnee[200];

	for (int i=0;i<Longueur_Entete;i++)
	{
		Entete[i] = *Data++;
	}

	if(Entete[0] == 'P' && Entete[1] == '3')
	{
		int Type_Donnee_Recu = Entete[2]*10 + Entete[3];
		int Taille = Entete[4]*100 + Entete[5]*10 + Entete[6];
		int No_Paquet = Entete[7]*10 + Entete[8];
		int Tot_Paquet = Entete[9]*10 + Entete[10];

		for (int i=0;i<Taille-Longueur_Entete;i++)
		{
			Donnee[i] = *Data++;
		}
		
		if (Type_Donnee_Recu == CREDENTIAL)
		{
			int Demandeur = Donnee[0];
			char ReadorWrite = Donnee[1];
			PORTB &= ~(1 << 4); // Turn on LED
			while(PINE & 0x10); // wait for user to press start button (SW0)
			PORTB |= 0x10; //Turn off LED
			if (ReadorWrite == 'R')
			{
				readSelfData(Demandeur);
			}
			else if (ReadorWrite == 'W' && Donnee[0] == AUTHORITARIAN)
			{
				
			}
			else
			{
				readSelfData(ERROR);
			}
		}
		else
		{
			printString(Donnee);
		}	
	}		
}

void requestTargetAllID(){
	if(readSelfCredential() == CIVILIAN){
		
	}
	else if(readSelfCredential() == PROFESSIONAL || readSelfCredential() == AUTHORITARIAN)
	{
		
	}
	else
		printString("\n\r\tERROR : CRENDENTIAL LEVEL TOO LOW\n\r");
}