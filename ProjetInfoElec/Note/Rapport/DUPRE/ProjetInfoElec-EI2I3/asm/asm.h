#define TAILLE_MAX_CODESEG 1000
#define TAILLE_MAX_LAB 100
#define TAILLE_MAX_ID 100

unsigned int codeSegment[MAX_CODESEGMENT_SIZE]; 
int currentInst; 

struct Nom_instruction {
  char *name;			// Le nom de l'instruction
  int opcod;			// son codop, extrait de vm_codops.h
  int type;			// son type
  char *format;			// son format
  int nbops;			// le nombre d'operandes de l'inst
} tab_nom_instruction[MAX_IDENTS_SIZE]; 

int instruction_actuelle;

struct label {
  char *label;
  int addr;
} tabLabels[MAX_LABELS_SIZE]; 
int currentLabel;

struct ref {
  char *label;
  int addrInCode;
} tabReferences[MAX_LABELS_SIZE]; 
int currentRef;


void addCode(int v);
void ajouter_instruction(char *instname, int opcod, int type, char *format, int nbops);
int recherche_label(char *labelname);
void ajouter_label(char *labelname,int addr);
void addReference(char *labelname,int addrInCode);
void resolveReferences();
void decode_Instruction(char *line);
int parseAsm(FILE *fin);
void Afficher_labels();
void dumpBinaryCode();
void generateBinary(FILE *fout);


