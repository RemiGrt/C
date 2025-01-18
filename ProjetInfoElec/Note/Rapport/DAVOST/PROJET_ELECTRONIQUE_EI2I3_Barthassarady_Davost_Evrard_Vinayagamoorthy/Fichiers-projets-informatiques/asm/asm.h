#ifndef ASM
#define ASM

# define MAX_CODESEGEMENT_SIZE 1001
# define MAX_LABELS_SIZE  1002
# define MAX_IDENTS_SIZE 1003

#define commentaire 0
#define instruction 1
#define etiquette 2
int currentLabel;

struct label {
    char *label;
    int addr;
} tabLabels[MAX_LABELS_SIZE];



struct ref {
char *label;
int addrInCode;
} tabReferences[MAX_LABELS_SIZE];
int currentRef;

struct instructionName {
char *name; // Le nom de l'instruction
int opcod; // son codop, extrait de vm_codops.h
int type; // son type
char *format; // son format
int nbops; // le nombre d'operandes de l'inst
} tabInstructionNames[MAX_IDENTS_SIZE];


void addInstructionName(char *instname, int opcod, int type, char *format, int nbops);
int findLabel(char *labelname); // 2
void addLabel(char *labelname, int addr);  // 3


void parseAsm(char* fichier);  //1

#endif 
