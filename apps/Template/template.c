/**
 * \file template.c
 *
 * \brief Empty application template
 *
 * Copyright (C) 2012-2014, Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 * Modification and other use of this code is subject to Atmel's Limited
 * License Agreement (license.txt).
 *
 * $Id: template.c 9267 2014-03-18 21:46:19Z ataradov $
 *
 */

/*- Includes ---------------------------------------------------------------*/
#include "sys.h"
#include "phy.h"
#include "user.h"
#include "gui.h"
#include "Timer.h"
#include <stdio.h>

/*- Definitions ------------------------------------------------------------*/
// Put your preprocessor definitions here

	
/*- Types ------------------------------------------------------------------*/
// Put your type definitions here
typedef struct UserProfils{
	char username[READ_STRING_ARRAY_LENGTH];
	char password[READ_STRING_ARRAY_LENGTH];
	char credential;
} UserProfil;

/*- Prototypes -------------------------------------------------------------*/
// Put your function prototypes here
char Lis_UART(void);
void Ecris_UART(char data);
void init_UART(void);
void SYS_Init(void);
void Board_Init(void);

/*- Variables --------------------------------------------------------------*/
// Put your variables here
uint8_t receivedWireless;	//cette variable deviendra 1 lorsqu'un nouveau paquet aura été recu via wireless (et copié dans "PHY_DataInd_t ind"
							//il faut la mettre a 0 apres avoir géré le paquet; tout message recu via wireless pendant que cette variable est a 1 sera jeté

PHY_DataInd_t ind; //cet objet contiendra les informations concernant le dernier paquet qui vient de rentrer

//Use with timer flag and interrupt
int seconds = 0;

/*- Implementations --------------------------------------------------------*/

// Put your function implementations here

/*************************************************************************//**
*****************************************************************************/
static void APP_TaskHandler(void)
{
  //char receivedUart = 'O';

  //receivedUart = Lis_UART();  
  /*if(receivedUart)		//est-ce qu'un caractere a été recu par l'UART?
  {
	  Ecris_UART(receivedUart);	//envoie l'echo du caractere recu par l'UART

	  if(receivedUart == 'a')	//est-ce que le caractere recu est 'a'? 
		{
		uint8_t demonstration_string[128] = "123456789A"; //data packet bidon
		Ecris_Wireless(demonstration_string, 10); //envoie le data packet; nombre d'éléments utiles du paquet à envoyer
		}
  }*/
  

  UserProfil up = {
	  .username = "",
	  .password = "",
	  .credential = AUTHORITARIAN
  } ;
  
  
	if(timer_flag == 1)
		seconds++;
	
	if(seconds > 2)
		writeTargetFirstName("Erdnaxela");
		//requestTargetAllID(up);
  
	if(seconds > 2){
		seconds = 0;
		timer_flag = 0;
	}
  
  
  
  if(receivedWireless == 1) //est-ce qu'un paquet a été recu sur le wireless? 
  {
	 Decortiquer_Paquet(ind.data);
	
	 receivedWireless = 0; 
  }
}

/*************************************************************************//**
*****************************************************************************/
int main(void)
{
	SYS_Init();
	Timer_Init();
	Board_Init();
	
	//openingMenu();
	
	while (1)
	{
		PHY_TaskHandler(); //stack wireless: va vérifier s'il y a un paquet recu
		APP_TaskHandler(); //l'application principale roule ici
	}
  
    return 0;
}

//FONCTION D'INITIALISATION
/*************************************************************************//**
*****************************************************************************/
void SYS_Init(void)
{
	receivedWireless = 0;
	wdt_disable(); 
	init_UART();
	PHY_Init(); //initialise le wireless
	PHY_SetRxState(1); //TRX_CMD_RX_ON
}
//

void Board_Init(void)
{
	sei();
	
	// Configure LED pin
	DDRB = 0x10; //PB4 output
	PORTB |= 0x10; //Turn off LED
	
	// Configure "Start Button" pin
	DDRE &= ~0x10; //PE4 input
	PORTE |= 0x10; //Enable pull-up resistor
}

//FONCTIONS POUR L'UART

char Lis_UART(void)
{

char data = 0; 

	if(UCSR1A & (0x01 << RXC1))
	{
		data = UDR1;
	}
	
return data;
}

void init_UART(void)
{
	//baud rate register = Fcpu / (16*baud rate - 1)
	//baudrate = 9600bps //s'assurer que la fuse CLKDIV8 n'est pas activée dans les Fuses, sinon ca donne 1200bps
	UBRR1H = 0x00;
	UBRR1L = 53;
	
	UCSR1A = 0x00;
	UCSR1B = 0x18; //receiver, transmitter enable, no parity
	UCSR1C = 0x06; //8-bits per character, 1 stop bit
}