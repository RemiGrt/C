#define MAX_CODESEGMENT_SIZE 1000
#define MAX_LABELS_SIZE 100
#define MAX_IDENTS_SIZE 100


// Structure tres simple qui va contenir le code
// genere. La seule fonction d'acces a ce tableau est
// la fonction
/*
  void addCode(int v), qui ajoute l'instruction v
  a la position courante dans codeSegment. La position
  courante est contenue dans la variable globale currentInst,
  qui est incrementee apres ajout d'une instruction
*/

unsigned int codeSegment[MAX_CODESEGMENT_SIZE]; //!< Variable globale stockant les OPCODES
int currentInst; //!< Variable globale indiquant le nombre courant de OPCODES dans codeSegment

// Structure permettant de definir les instructions de l'assembleur
// une instruction est definie par son nom, son codop, son type, son format
// et son nombre d'arguments
// Les instructions suivantes sont de type 0 car elles ne demandent pas
// de décodage d'operandes supplementaires. Leur chaine de format est ""
// et leur nombre d'argument est 0
/*
  addInstructionName("add", OP_ADD, 0, "", 0);
  addInstructionName("sub", OP_SUB, 0, "", 0);
  addInstructionName("mult", OP_MULT, 0, "", 0);
  addInstructionName("div", OP_DIV, 0, "", 0);
  addInstructionName("neg", OP_NEG, 0, "", 0);
  addInstructionName("and", OP_AND, 0, "", 0);
  addInstructionName("or", OP_OR, 0, "", 0);
  addInstructionName("not", OP_NOT, 0, "", 0);
  addInstructionName("eq", OP_EQ, 0, "", 0);
  addInstructionName("ls", OP_LS, 0, "", 0);
  addInstructionName("gt", OP_GT, 0, "", 0);
  addInstructionName("halt", OP_HALT, 0, "", 0);
*/
// Les instructions suivantes sont de type 1, ce qui signifie
// que le decodage d'un entier est necessaire. La chaine
// de format est donc "%s %d". Le %s represente l'instruction et le %d
// l'operande. Il y a un operande pour ce genre d'instruction
/*
  addInstructionName("push", OP_PUSH, 1, "%s %d", 1);
  addInstructionName("pop", OP_POP, 1, "%s %d", 1);
  addInstructionName("pushi", OP_PUSHI, 1, "%s %d", 1);
*/
// Les instructions suivantes sont de type 3, ce qui signifie que
// le decodage d'une chaine de caracteres representant une etiquette
// est necessaire. La chaine de format est donc "%s %s" et
// le deuxieme %s represente l'etiquette. Il y a un
// operande pour ce genre d'instructions
/*
  addInstructionName("jp", OP_JP, 3, "%s %s", 1);
  addInstructionName("jf", OP_JF, 3, "%s %s", 1);
*/

struct instructionName {
  char *name;			// Le nom de l'instruction
  int opcod;			// son codop, extrait de vm_codops.h
  int type;			// son type
  char *format;			// son format
  int nbops;			// le nombre d'operandes de l'inst
} tabInstructionNames[MAX_IDENTS_SIZE]; 

int currentInstructionName;

// La structure de donnees suivante permet de manipuler les etiquettes
// (labels en anglais). Chaque entree de ce tableau contient le nom d'une
// etiquette (label) et son adresse correspondante dans codeSegment
// Les fonctions d'acces a ce tableau sont
/*
  int findLabel(char *labelname), qui permet de savoir
  si un label existe dans la table. La fonction rend
  l'indice dans la table si le label existe, -1 sinon
  void addLabel(char *labelname,int addr), qui permet d'ajouter
  un label et son adresse dans la table
  la variable globale entiere currentLabel compte le nombre
  de labels et est incremente pour chaque ajout dans
  dans la table
*/

struct label {
  char *label;
  int addr;
} tabLabels[MAX_LABELS_SIZE]; 
int currentLabel;

// Structure permettant de manipuler les references dans le code, resolues
// ou non. Chaque entree de la table contient un label et une adresse precise
// dans le code representant une case ou on a mis temporairement un -1 et
// qu'il faut remplacer dans la deuxieme passe d'assemblage par la vraie
// reference, que l'on connaitra car tous les labels seront eux-meme connus.
// Les fonctions d'acces a ce tableau sont
/*
  void addReference(char *labelname,int addrInCode), qui permet d'ajouter
  une reference et son adresse dans le code dans la table
  void resolveReferences(), qui permet de resoudre les references
  la variable globale entiere currentRef compte le nombre
  de references et est incremente pour chaque ajout dans
  dans la table
*/

struct ref {
  char *label;
  int addrInCode;
} tabReferences[MAX_LABELS_SIZE]; 
int currentRef;


void addCode(int v);
void addInstructionName(char *instname, int opcod, int type, char *format, int nbops);
int findLabel(char *labelname);
void addLabel(char *labelname,int addr);
void addReference(char *labelname,int addrInCode);
void resolveReferences();
void decodeInstruction(char *line);
int parseAsm(FILE *fin);
void printLabels();
void dumpBinaryCode();
void generateBinary(FILE *fout);


