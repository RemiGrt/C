/**
* \file 
*			VM_MCC.h
* \author 
*			Jeanne Baumier & Thomas Broussard
* \date 
*			10 fevrier 2017
* \brief  
*			Librairie contenant les fonctions du fichier VM_MCC.c
*/

#ifndef __VM_MCC_H__
#define __VM_MCC_H__

#define SIZE_BIN 1000


/** \fn void Run_VM(int *PC , int *SP , int Code[SIZE_BIN] , int Variable[SIZE_BIN] , int Stack[SIZE_BIN])
 * \brief 
 * 			Lance la machine virtuelle sur le microcontroleur \n \b Avoir defini les entrees sorties dans le fichier Mapping.h
 * \param[in] 
 *			*PC			compteur PC
 * \param[in] 
 *			*SP			compteur de pile SP
 * \param[in] 
 *			Code[SIZE_BIN]			Tableau Code
 * \param[in] 
 *			Variable[SIZE_BIN] 		Tableau Variable
 * \param[in] 
 *			Stack[SIZE_BIN] 		Tableau Stack (pile)
 */
void Run_VM(int *PC , int *SP , int Code[SIZE_BIN] , int Variable[SIZE_BIN] , int Stack[SIZE_BIN]);


#endif
