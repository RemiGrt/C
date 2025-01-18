#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define KEY_BUTTON 0
#define KEY_ANA 1
#define KEY_PWM 2
#define KEY_TOR 3
#define KEY_IDENT 4

// Cet enum contient tous les types possibles pour un noeud "operator"
typedef enum { OPER_ADD, OPER_SUB, OPER_MULT, OPER_DIV,
	       OPER_INF, OPER_SUP, OPER_GE, OPER_LE, OPER_NE, OPER_EQ,
               OPER_NOT, OPER_AND, OPER_OR, OPER_NEG
	       } nodeOper;

// Les trois types de noeuds possibles, "numeric" ou "operator"
typedef enum { typeNumeric, typeOperator, typeIdentifier } nodeEnum;

/* un noeud numeric (int) permet de stocker une valeur entiere */
typedef struct {
	int valeur;
} numericNodeType;

/* un noeud operator permet de stocker un operateur, le nombre d'operandes et les pointeurs vers les noeuds
   operande correspondants */
typedef struct {
	int oper;
	int nOperands;
	struct nodeTypeTag **op; 
} operatorNodeType;

/* un noeud identifier fait reference a un identificateur */
typedef struct {
	char *ident;
} identifierNodeType;

/* Cette structure, fondamentale, permet de definir un noeud a geometrie variable. Le type
   permet de definir le type du noeud (numeric ou operator) et l'union permet, en fonction
   du type, d'acceder aux bonnes informations */

typedef struct nodeTypeTag {
	nodeEnum type;
	int digraphNode;		// Pour generer des beaux graphes avec dot
	union {
		numericNodeType t_numeric;
		operatorNodeType t_oper;
		identifierNodeType t_identifier;
	};
} nodeType;

extern nodeType *createNumericNode(int v);
extern nodeType *createIdentifierNode(char *id);
extern nodeType *createOperatorNode(int oper, int nOperands, ...);
void generateAsmExpression(nodeType *n, FILE *fout);
extern void generateAsm(nodeType *n, char *filename);
