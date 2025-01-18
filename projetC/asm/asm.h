#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "vm_codops.h"

/*! \file asm.h
 * \details
 * \section Présentation
 *
 * 
 * 
 * Ce programme est directement rattaché à asm.c.
 * On y retrouve les prototypes des fonctions utilisées ainsi que les structures.
 *
 *
 *
 * 
 *
 * \section Compilation
 * - Commande de compilation : gcc asm.c -o asm.o     *
 * - Utilisation en console : ./asm
 * \section Liste_des_fonctions:
 *  - void addInstructionName(char *name, int opcod, int type, char *format, int nbops)
 *  - void addCode(char *line, int opcod, char *format, int type)
 *  - void decodeInstruction(char *line)
 *  - void resolveReferences(void)
 *  - void addLabel(char labelname[MAX_LINE_SIZE],int addr)
 *  - void parseAsm(FILE *fin)
 *  - void generateBinary(FILE *fout)
*/

#define MAX_LABELS_SIZE 100
#define MAX_IDENTS_SIZE 100
#define MAX_LINE_SIZE 100
#define MAX_CODESEGMENT_SIZE 300

//structure d'une étiquette
struct label {
    char label[MAX_LINE_SIZE];
    int addr;
}tab_labels[MAX_LABELS_SIZE];

//structure d'une référence
struct ref{
    char label[MAX_LINE_SIZE];
    int addrInCode;
}tabReferences[MAX_LABELS_SIZE];

//structure des instructions
struct instructionName {
    char *name;	//le nom de l'instruction
    int opcod;		//son codop, extrait de vm_codops.h
    int type;		//son type
    char *format;	//son format
    int nbops;		//le nombre d'operandes de l'inst
}tabInstructionNames[MAX_IDENTS_SIZE];

//Protoypes des fonctions
void addInstructionName(char *name, int opcod, int type, char *format, int nbops);
void addCode(char *line, int opcod, char *format, int type);
void decodeInstruction(char *line);
void resolveReferences(void);
void addLabel(char labelname[MAX_LINE_SIZE],int addr);
void parseAsm(FILE *fin);
void generateBinary(FILE *fout);




