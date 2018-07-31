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

#define Longueur_Paquet 200
#define Longueur_Entete 6

char Nom[] = "Sylvain-Cameron";
char Prenom[] = "Alexandre";
char Date_Naissance[] = "1994-04-06";
char Adresse[] = "2145 Rue Galt Ouest";
char Appartement[] = "211";
char Ville[] = "Sherbrooke";
char Pays[] = "Canada";
char Province[] = "Québec";
char Code_Postale[] = "J1K1K3";
char Soin_Particulier[] = "";
char Medicament[] = "";
char Maladie[] = "";
char Commentaire[] = "";
char Groupe_Sanguin[] = "";
char End[] = "End";
char Paquet[Longueur_Paquet];
int Nombre_Info = 0;
int Numero_Paquet = 0;

void Ecris_UART(char data)
{
	UDR1 = data;
	while(!(UCSR1A & (0x01 << UDRE1)));
}

//User ID
bool isUserExisting(char* username, char* password){
	//TODO : Implement logic with dummy
	return false;
}


void Creer_Paquet(char * ptr, size_t n_elements)
{
	Numero_Paquet++;
	if (Numero_Paquet < 10)
	{
		Paquet[2] = 0;
		Paquet[3] = Numero_Paquet;
	}
	else
	{
		Paquet[2] = Numero_Paquet/10;
		Paquet[3] = Numero_Paquet%10;
	}
	if (Nombre_Info < 10)
	{
		Paquet[4] = 0;
		Paquet[5] = Nombre_Info;
	}
	else
	{
		Paquet[4] = Nombre_Info/10;
		Paquet[5] = Nombre_Info%10;
	}
	for (int i = 0;i<n_elements;i++)
	{
		Paquet[i+Longueur_Entete] = ptr[i];
		Ecris_UART(ptr[i]);
	}
}

void readData(int Type)
{
	Nombre_Info = 0;
	User_Type = Type;
	
	if (User_Type == CIVILIAN)
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
	else if (User_Type == PROFESSIONAL || User_Type == AUTHORITARIAN )
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
		Access[0] = END;
	}
	
	size_t N_Elements = 0;
	
	for(int i=0;i<sizeof(Access)/sizeof(Access[0]);i++)
	{
		memset(Paquet, '\0', Longueur_Paquet);
		Paquet[0] = Access[i]/10;
		Paquet[1] = Access[i]%10;
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
			
			case END :
			N_Elements = sizeof(End) / sizeof(End[0]);
			Creer_Paquet(End,N_Elements);
			i = sizeof(Access)/sizeof(Access[0]);
			
			default :
			break;
		}
	}
}