
#ifndef _ASSEMBLEUR_H_
#define _ASSEMBLEUR_H_

#define nbInstructionType 14


// structures
typedef struct				// structure pour connaitre la valeur des jumps (apres les avoir reférencees)
{
	char name[100];
	int numInstruction;
}t_etiquette;

typedef struct				// structure pour referencer la valeur des jumps
{
	char name[100];
	int addCode;
}t_reference;

typedef struct
{
	char name[100];
	int codop;
	int type;
	/* 0 : pas besoin d'instruction supplémentaire
	   1 : besoin d'une instruction supplémentaire
	   3 : pour les jumps
	*/
}t_instruction;

/*
typedef struct s_code
{
	char line;
	struct s_code* instructionSuivante;
}t_code;
*/

typedef struct
{
	int nbInstruction;
	int nbReference;
	int nbEtiquette;
}t_nbInstructionEtiquetteReference;


// Prototypes
void AddCodOp(t_instruction* tabInstructions, int instructionIndex, char* name, int codop, int type);

void ParseASM(FILE* fichierEntree, t_instruction* tabInstructions, t_etiquette* tabEtiquette, t_reference* tabReference, int* code, t_nbInstructionEtiquetteReference* nbInstructionEtiquetteReference);

char* NomEtiquette(char* etiquette);

void ResolveEtiquette(int* code,  t_etiquette* tabEtiquette, t_reference* tabReference, t_nbInstructionEtiquetteReference* nbInstructionEtiquetteReference);

void WriteBinCode(int* code, FILE* fichierSortie, t_nbInstructionEtiquetteReference* nbInstructionEtiquetteReference);





#endif
