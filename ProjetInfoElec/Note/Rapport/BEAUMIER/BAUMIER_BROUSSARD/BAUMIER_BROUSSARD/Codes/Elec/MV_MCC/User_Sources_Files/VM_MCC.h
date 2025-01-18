//#############################################################
// Auteur : Thomas Broussard
// Date : 10/02/17
// Titre : Init.pins.h
//------------------------------------------------------------
// Description  :
//	Contient les fonctions du fichier UART.c
//	
//
//
//
//
//#############################################################

#ifndef __VM_MCC_H__
#define __VM_MCC_H__

#define SIZE_BIN 1000


/*===============================================================================
  FUNCTION: run_VM 
  DESCRIPTION: lance la machine virtuelle sur le microcontroleur
  PARAMETERS: aucun
	RETURNS: aucun
  REQUIREMENTS: avoir défini les entrées/sorties dans le fichier Mapping.h
===============================================================================*/
/** \fn void Run_VM()
 * \brief Lis le tableau \b Code[] afin d'effectuer les opérations dans la pile d'exécution \b Stack[]
 */
void Run_VM(int *PC , int *SP , int Code[SIZE_BIN] , int Variable[SIZE_BIN] , int Stack[SIZE_BIN]);


#endif
