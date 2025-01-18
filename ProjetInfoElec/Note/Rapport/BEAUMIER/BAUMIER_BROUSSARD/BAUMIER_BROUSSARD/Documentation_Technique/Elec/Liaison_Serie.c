/**
* \file 
*			Liaison_Serie.c
* \author 
*			Thomas Broussard
* \date 
*			19 juin 2017
* \brief  
*			Contient les fonctions permettant de communiquer avec le PC
*/

#include "stm32f0xx.h"  
#include "string.h"
#include "InitPins.h" 
#include "Mapping.h"

// Librairies du pc
#include <stdio.h>


/*###############################################################################
							FONCTIONS LIAISON SERIE
###############################################################################*/


/** 
 * \fn  void Send_Text(char *Message)
 * \brief 
 *			Envoi une chaine de caractere vers le PC
 * \param[in] 
 *			Message		Message a transmettre
 */
void Send_Text(char *Message)
{
	int i;
	USART2->CR1 |=(1<<3); // Debut de la transmission
	for (i = 0; i < strlen(Message); i++)
	{ 
		USART2->TDR = Message[i]; 			// ecriture du caractere dans le registre de transmission 
		while(!(USART2->ISR & 1 << 7)){} 
	}
	USART2->CR1 &=~(1<<3); // Fin de la transmission
}

/** 
 * \fn  void Reception_Programme_UART2(int *Num_Instruction,int *Instruction)
 * \brief 
 *			Reception de plusieurs caracteres (octets) par la liaison serie pour la reception du programme
 * \param[in] 
 *			Num_Instruction		Numero de l'instruction
 * \param[in] 
 *			Instruction		Instruction
 */
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
			
		// Si la trame est finie, alors on arrete la fonction, sinon on passe a la case suivante
		if (Octets[i] == '@')
				fin_Octet = 1;
		i++;
	}
	
	// Decodage de l'instruction reçue
	sscanf(Octets,"%d:%d@",Num_Instruction,Instruction);
}

/** 
 * \fn  void Reception_Nb_Instr_UART2(int *Nb_Instruction)
 * \brief 
 *			Reception du nombre d'instruction d'un programme en chargement par la liaison serie
 * \param[in] 
 *			*Nb_Instruction		Nombre d'instruction
 */
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
			
		// Si la trame est finie, alors on arrete la fonction, sinon on passe a l'octet suivant
		if (Octets[i] == '@')
				fin_Octet = 1;
		
		i++;
	}
	
	// Decodage de l'instruction reçue
	sscanf(Octets,"%d@",Nb_Instruction);

	Send_Text("START");
}



