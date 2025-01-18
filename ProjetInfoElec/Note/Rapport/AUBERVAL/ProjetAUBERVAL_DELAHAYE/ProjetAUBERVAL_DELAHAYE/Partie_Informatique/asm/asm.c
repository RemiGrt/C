/*! \file asm.c
// \author Anaïs AUBERVAL
// \version finale
// \date 30/06/2017
// \brief Programme permettant de passer d'un fichier assembleur à un fichier binaire 
// 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm_codops.h" // a enlever
#include "asm.h"

/*! \mainpage Assembleur
 *
 * \section intro_sec Introduction
 *
 * 
 * 
 * Ce programme permet d'assembler un fichier assembleur en bytecode
 * Utilisation en console: : ./asm fichierIn.asm fichierOut.bin
 *
 * \section Compilation
 * Lancement du script bash : ./compil.sh 
 * gcc -o asm.o -c asm.c
 * gcc -o asm asm.o
 * \subsection 
 *  
 * 
 */

int main(int argc, char **argv)
{
	if (DEBUG) printf("HELLO !\n");
	if (DEBUG) printf("%d\n",argc);
	if (DEBUG) printf("%s\n",argv[0]);
	if (DEBUG) printf("%s\n",argv[1]);
	char *s;
	int i=0;
	
	// Ouverture du fichier dans parseAsm

	// Construction du dictionnaire d’instruction 
	// Type 0 : pas d'argument
	// Type 1 : un argument
	// Type 3 : jump
	addInstructionName("add", I_ADD, 0, "", 0); //ADD opérande +
  	addInstructionName("mult", I_MULT, 0, "", 0); //MULT *
	addInstructionName("ls", I_LS, 0, "", 0); // <
	addInstructionName("gt", I_GT, 0, "", 0); // >
	addInstructionName("eq", I_EQ, 0, "", 0); // ==
	
	addInstructionName("pushi", I_PUSHI, 1, "%s %d", 1);
	addInstructionName("push", I_PUSH, 1, "%s %d", 1);
	addInstructionName("pop", I_POP, 1, "%s %d", 1);

	addInstructionName("jf", I_JF, 3, "%s %s", 1);
	addInstructionName("jp", I_J, 3, "%s %s", 1);  
	
	addInstructionName("and", I_AND, 0, "", 0);	    
	addInstructionName("end", I_HALT, 0, "", 0);

	if (DEBUG) printf("instr =%d\n",currentInst);

	// Parseur phase 1
	parseAsm(argv[1]);
	
	//if (DEBUG){
	printf("Le nombre de References = %d et de Label=%d\n", currentRef, currentLabel);
	
	i=0;
	printf("\nAffichage des Labels :\n");
	while (i<currentLabel){
		printf("tabLabels[%d].name=%s\ntabLabels[%d].addr=%d\n",i, tabLabels[i].name,i,tabLabels[i].addr);
		i++;
	}
	printf("\n");
	//}
	printf("Affichage des références avec currentRef=%d : \n",currentRef);
	i=0;
	while (i<currentRef){
		printf("tabReferences[%d].name=%s\ntabReferences[%d].addrInCode=%d\n",i, tabReferences[i].name,i,tabReferences[i].addrInCode);
		i++;
	}
	
	// Parseur phase 2
	resolveReferences();

	
	// VERIF CodeSegment 
	//if (DEBUG) 
	//printf("segment dans le main :%d\n",segment);
	for(i=0;i<=segment;i++){
		printf("CodeSegment[%d]=%d\n",i,codeSegment[i]);
	}
	
	// Génération du code
	generateBinaryCode(argv[2]);
	if (DEBUG) printf("HELLO !\n");

	// Vérification
	//dumpBinaryCode("check.txt");
	
	return 0;

}

