#ifndef __ASSEMBLEUR_H__
#define __ASSEMBLEUR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm_codops.h"


#define MAX_LABELS_SIZE 100
#define MAX_IDENTS_SIZE 100

/*
#define I_ADD 0
#define I_SUB 1
#define I_MULT 2
#define I_DIV 3

#define I_NEG 11
#define I_AND 13
#define I_OR 14
#define I_NOT 15
#define I_EQ 12

#define I_LS 20
#define I_GT 21

#define I_PUSHI 100
#define I_PUSH 101
#define I_POP 102

#define I_J 200
#define I_JF 201

#define I_HALT 400*/

struct label {
char *label;
char name;
int addr;
} tabLabels[MAX_LABELS_SIZE];

struct instructionName {
char *name;	// Le nom de l'instruction
int opcode;	// son codop, extrait de vm_codops.h
int type;	// son type
char *format;	// son format
int nbops;	// le nombre d'operandes de l'inst
} tabInstructionNames[MAX_IDENTS_SIZE];

struct ref {
char *label;
int addrInCode;
} tabReferences[MAX_LABELS_SIZE];

//int currentRef;

void addLabel(char *line, int addrCodeSeg);
void decodeInstruction(char *line);
void parseAsm(FILE *fin);
void addInstructionName(char *name, int opcode, int type, char *format, int nbops);
void resolveReference();

#endif
