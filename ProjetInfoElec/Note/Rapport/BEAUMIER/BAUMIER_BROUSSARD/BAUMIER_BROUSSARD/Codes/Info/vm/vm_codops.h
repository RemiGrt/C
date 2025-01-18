/**
* \file 
* 			vm_codops.h
* \author
* 			Jeanne Baumier & Thomas Broussard
* \date 
* 			6 février 2017
* \brief 
* 			Librairie liée aux fichiers \b MachineVirtuelle.c et \b main.c
* 			 
*/

#ifndef __VM_CODOPS_H__
#define __VM_CODOPS_H__


/** \fn 
 * 		int ReadBin(char *src) 
 * \brief 
 * 		Lis un fichier bytecode (extension \b .bin) et stocke les instructions dans le tableau \b Code[]
 * \param[in] 
 * 		*src Ici, notre fichier \b .bin
 * \return 
 *			\b 1 : si les fichiers ont pu être ouverts
 * \return 
 *			\b 0 : si les fichiers n'ont pu être ouverts
 */
int ReadBin(char *src);

/** \fn 
 * 		void Run_VM()
 * \brief 
 * 		Lis le tableau \b Code[] afin d'effectuer les opérations dans la pile d'exécution \b Stack[]
 */
void Run_VM();

#endif
