//#############################################################
// Auteur : Thomas Broussard
// Date : 19/06/17
// Titre : Liaison_Serie.c
//------------------------------------------------------------
// Description  :
//	Contient les fonctions permettant de communiquer avec le PC

//#############################################################
#include "stm32f0xx.h"  
#include "string.h"
#include "InitPins.h" 
#include "Mapping.h"

// Librairies du pc
#include <stdio.h>


/*###############################################################################
							FONCTIONS LIAISON SERIE
###############################################################################*/

/*===============================================================================
FONCTION:     Send_Text() : 
Envoi une chaîne de caractère vers le PC
===============================================================================*/
void Send_Text(char *Message)
{
	int i;
	USART2->CR1 |=(1<<3); // Début de la transmission
	for (i = 0; i < strlen(Message); i++)
	{ 
		USART2->TDR = Message[i]; 			// ecriture du caractere dans le registre de transmission 
		while(!(USART2->ISR & 1 << 7)){} 
	}
	USART2->CR1 &=~(1<<3); // Fin de la transmission
}

/*===============================================================================
FONCTION:     Reception_Programme_UART2() : 
Réception de plusieurs caractères (octets) par la liaison série pour la réception du programme
===============================================================================*/
void Reception_Programme_UART2(int *Num_Instruction,int *Instruction)
{
	char Octets[20];
	int fin_Octet = 0, i=0;
	while (fin_Octet == 0)
	{
		
		// Attente du prochain octet
		while (!(USART2->ISR & (1 << 5)))
		{}
			
		// Sauvegarde de l'octet dans la case i
		Octets[i] = USART2->RDR;
			
		// Si la trame est finie, alors on arrête la fonction, sinon on passe à la case suivante
		if (Octets[i] == '@')
				fin_Octet = 1;
		i++;
	}
	
	// Decodage de l'instruction reçue
	sscanf(Octets,"%d:%d@",Num_Instruction,Instruction);
}

/*===============================================================================
FONCTION:     Reception_Nb_Instr_UART2() : 
Réception du nombre d'instruction d'un programme en chargement par la liaison série
===============================================================================*/
void Reception_Nb_Instr_UART2(int *Nb_Instruction)
{
	char Octets[20];
	int fin_Octet = 0, i=0;
	while (fin_Octet == 0)
	{
		// Attente du prochain octet
		while (!(USART2->ISR & (1 << 5)))
		{}
			
		// Sauvegarde de l'octet dans la case i
		Octets[i] = USART2->RDR;
			
		// Si la trame est finie, alors on arrête la fonction, sinon on passe à l'octet suivant
		if (Octets[i] == '@')
				fin_Octet = 1;
		
		i++;
	}
	
	// Decodage de l'instruction reçue
	sscanf(Octets,"%d@",Nb_Instruction);

	Send_Text("START");
}



