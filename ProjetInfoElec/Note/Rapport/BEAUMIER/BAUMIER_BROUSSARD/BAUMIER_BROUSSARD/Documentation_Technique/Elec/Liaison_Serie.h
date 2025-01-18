/**
* \file 
*			Liaison_Serie.h
* \author 
*			Thomas Broussard
* \date 
*			19 juin 2017
* \brief  
*			Contient les fonctions permettant de communiquer avec le PC
*/


#ifndef __LIAISON_SERIE_H__
#define __LIAISON_SERIE_H__

/** 
 * \fn  void Send_Text(char *Message)
 * \brief 
 *			Envoi une chaîne de caractère vers le PC
 * \param[in] 
 *			Message		Message a transmettre
 */
void Send_Text(char * Message);

/** 
 * \fn  void Reception_Programme_UART2(int *Num_Instruction,int *Instruction)
 * \brief 
 *			Reception de plusieurs caractères (octets) par la liaison serie pour la reception du programme
 * \param[in] 
 *			Num_Instruction		Numero de l'instruction
 * \param[in] 
 *			Instruction		Instruction
 */
void Reception_Programme_UART2(int *Num_Instruction,int *Instruction);

/** 
 * \fn  void Reception_Nb_Instr_UART2(int *Nb_Instruction)
 * \brief 
 *			Reception du nombre d'instruction d'un programme en chargement par la liaison serie
 * \param[in] 
 *			*Nb_Instruction		Nombre d'instruction
 */
void Reception_Nb_Instr_UART2(int *Nb_Instruction);



#endif
