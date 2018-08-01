/*
 * user.c
 *
 * Created: 7/26/2018 3:51:29 PM
 * Author: antho
 */ 

#include "user.h"
#include "sys.h"
#include "phy.h"
#include "Timer.h"
#include <string.h>
#include "dummies.h"

#define Longueur_Paquet 200
#define Longueur_Entete 11

//Global variables
Credential ClientCredential;

char Paquet[Longueur_Paquet];
int Nombre_Info = 0;
int Numero_Paquet = 0;
bool Ack_Ok = false;

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

void readSelfData(int ClientCredential)
{
	Nombre_Info = 0;
	
	if (ClientCredential == CIVILIAN)
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
	else if (ClientCredential == PROFESSIONAL || ClientCredential == AUTHORITARIAN )
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
		Paquet[2] = Access[i]/10;
		Paquet[3] = Access[i]%10;
		switch(Access[i])
		{
			case PRENOM :
			N_Elements = sizeof(Prenom) / sizeof(Prenom[0]);
			SendPackage(Prenom,N_Elements);
			break;
			
			case NOM :
			N_Elements = sizeof(Nom) / sizeof(Nom[0]);
			SendPackage(Nom,N_Elements);
			break;
			
			case DATE_NAISSANCE :
			N_Elements = sizeof(Date_Naissance) / sizeof(Date_Naissance[0]);
			SendPackage(Date_Naissance,N_Elements);
			break;
			
			case ADRESSE :
			N_Elements = sizeof(Adresse) / sizeof(Adresse[0]);
			SendPackage(Adresse,N_Elements);
			break;
			
			case APPARTEMENT :
			N_Elements = sizeof(Appartement) / sizeof(Appartement[0]);
			SendPackage(Appartement,N_Elements);
			break;
			
			case VILLE :
			N_Elements = sizeof(Ville) / sizeof(Ville[0]);
			SendPackage(Ville,N_Elements);
			break;
			
			case PAYS :
			N_Elements = sizeof(Pays) / sizeof(Pays[0]);
			SendPackage(Pays,N_Elements);
			break;
			
			case PROVINCE :
			N_Elements = sizeof(Province) / sizeof(Province[0]);
			SendPackage(Province,N_Elements);
			break;
			
			case CODE_POSTAL :
			N_Elements = sizeof(Code_Postale) / sizeof(Code_Postale[0]);
			SendPackage(Code_Postale,N_Elements);
			break;
			
			case SOIN_PARTICULIER :
			N_Elements = sizeof(Soin_Particulier) / sizeof(Soin_Particulier[0]);
			SendPackage(Soin_Particulier,N_Elements);
			break;
			
			case MEDICAMENT :
			N_Elements = sizeof(Medicament) / sizeof(Medicament[0]);
			SendPackage(Medicament,N_Elements);
			break;
			
			case MALADIE :
			N_Elements = sizeof(Maladie) / sizeof(Maladie[0]);
			SendPackage(Maladie,N_Elements);
			break;
			
			case COMMENTAIRE :
			N_Elements = sizeof(Commentaire) / sizeof(Commentaire[0]);
			SendPackage(Commentaire,N_Elements);
			break;
			
			case GROUPE_SANGUIN :
			N_Elements = sizeof(Groupe_Sanguin) / sizeof(Groupe_Sanguin[0]);
			SendPackage(Groupe_Sanguin,N_Elements);
			break;
			
			case ERROR :
			N_Elements = sizeof(Error) / sizeof(Error[0]);
			SendPackage(Error,N_Elements);
			break;
		
			case END :
			SendPackage("",0);
			break;

			default :
			break;
		}
		Acknowledge_Paquet();
	}
}

void SendPackage(char * ptr, size_t n_elements)
{
	Numero_Paquet++;
	Paquet[0] = 'P';
	Paquet[1] = '3';
	
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
	
	printString("\n\rPACKAGE SENT...\n\r");
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
		else if (Type_Donnee_Recu == ACKNOWLEDGE)
		{
			if (Donnee[0] == 'F')
			{
				Ecris_Wireless(Paquet,sizeof(Paquet));
			}
			else if (Donnee[0] == 'T')
			{
				Ack_Ok = true;
			}
		}
		else
		{
			Numero_Paquet = 0;
			memset(Paquet, '\0', Longueur_Paquet);
			Paquet[2] = ACKNOWLEDGE/10;
			Paquet[3] = ACKNOWLEDGE%10;
			char Ack = 'T';
			Nombre_Info = 1;
			SendPackage(Ack,sizeof(Ack));
			printString(Donnee);
		}
	}
}

void requestTargetAllID(UserProfil up){
	if(up.credential == CIVILIAN || up.credential == PROFESSIONAL || up.credential == AUTHORITARIAN){
		Numero_Paquet = 0;
		memset(Paquet, '\0', Longueur_Paquet);
		Paquet[2] = CREDENTIAL/10;
		Paquet[3] = CREDENTIAL%10;		
		Nombre_Info = 1;
		char buffer_data[2] = {up.credential, 'R'};		
		SendPackage(buffer_data, sizeof(buffer_data));
	}
	else
		printString("\n\r\tERROR : CRENDENTIAL LEVEL TOO LOW TO REQUEST\n\r");
}

void Acknowledge_Paquet()
{
	while(Ack_Ok == false)
	{
		while (receivedWireless != 1)
		{
			PHY_TaskHandler();
		}
		Decortiquer_Paquet(ind.data);
	}
	Ack_Ok = false;
}