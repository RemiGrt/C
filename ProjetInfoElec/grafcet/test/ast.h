#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "canon_serial.h"

#define KEY_BUTTON 0
#define KEY_ANA 1
#define KEY_PWM 2
#define KEY_TOR 3
#define KEY_IDENT 4

// Cet enum contient tous les types possibles pour un noeud "operator"
typedef enum { OPER_ADD, OPER_SUB, OPER_MULT, OPER_DIV,
	       OPER_SEQUENCE, OPER_TRANSITION, OPER_STEP,
	       OPER_INF, OPER_SUP, OPER_GE, OPER_LE, OPER_NE, OPER_EQ,
               OPER_NOT, OPER_AND, OPER_OR, OPER_NEG, OPER_ASSIGN,
	       OPER_RESERVE_SPACE, OPER_MAIN } nodeOper;

// Les deux types de noeuds possibles, "numeric" ou "operator"
typedef enum { typeNumeric, typeOperator, typeIdentifier } nodeEnum;

/* un noeud numeric (float) permet de stocker une valeur reelle */
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
	int key;
	int flag;
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

struct _etape;
struct _listeEtapeElement;
struct _transition;
struct _listeTransitionElement;

typedef struct _listeEtapeElement
{
        struct _etape *e;
        struct _listeEtapeElement *next;
} listeEtapeElement;

typedef struct _listeTransitionElement
{
        struct _transition *t;
        struct _listeTransitionElement *next;
} listeTransitionElement;

typedef struct _etape
{
        char *nom;
        char active;
        int pcAction;
	int ident;
	nodeType *actionNode;
        listeTransitionElement *transitionsAmont;
        listeTransitionElement *transitionsAval;
} etape;

typedef struct _transition
{
        char *nom;
        char active;
        int pcReceptivite;
	int ident;
	nodeType *receptiviteNode;
        listeEtapeElement *etapesAmont;
        listeEtapeElement *etapesAval;
} transition;

extern nodeType *createNumericNode(float v);
extern nodeType *createIdentifierNode(char *id, int flag);
extern nodeType *createOperatorNode(int oper, int nOperands, ...);
extern void generateAsmRec(nodeType *n, FILE *fout);
void generateAsmExpression(nodeType *n, FILE *fout);
extern void generateAsm(nodeType *n, char *filename);
extern void generateDigraphEdges(nodeType *n,FILE *fout);
extern void generateDigraph(nodeType *n);
extern int findIdent(char *s);
extern void printEtapes();
extern void printTransitions();
extern void emptyStack();
extern void pushStack(etape *e);
extern etape* popStack();
extern void grafcet_interpreter();
