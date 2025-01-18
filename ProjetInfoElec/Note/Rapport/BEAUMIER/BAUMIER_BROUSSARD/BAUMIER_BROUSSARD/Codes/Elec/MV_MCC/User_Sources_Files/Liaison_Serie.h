//#############################################################
// Auteur : Thomas Broussard
// Date : 19/06/17
// Titre : Liaison_Serie.h
//------------------------------------------------------------
// Description  :
//	Contient les fonctions permettant de communiquer avec le PC

//#############################################################

#ifndef __LIAISON_SERIE_H__
#define __LIAISON_SERIE_H__

/*===============================================================================
FONCTION:     Send_Text() : 
Envoi une chaîne de caractère vers le PC
===============================================================================*/
void Send_Text(char * Message);

/*===============================================================================
FONCTION:     Reception_Programme_UART2() : 
Réception de plusieurs caractères (octets) par la liaison série pour la réception du programme
===============================================================================*/
void Reception_Programme_UART2(int *Num_Instruction,int *Instruction);

/*===============================================================================
FONCTION:     Reception_Nb_Instr_UART2() : 
Réception du nombre d'instruction d'un programme en chargement par la liaison série
===============================================================================*/
void Reception_Nb_Instr_UART2(int *Nb_Instruction);



#endif
