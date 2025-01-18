#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define KEY_BUTTON 0
#define KEY_ANA 1
#define KEY_PWM 2
#define KEY_TOR 3
#define KEY_IDENT 4

/** Cet enum contient tous les types possibles pour un noeud "operator"*/
typedef enum { OPER_ADD, OPER_SUB, OPER_MULT, OPER_DIV,
	       OPER_SEQUENCE, OPER_TRANSITION, OPER_STEP,
	       OPER_INF, OPER_SUP, OPER_GE, OPER_LE, OPER_NE, OPER_EQ,
               OPER_NOT, OPER_AND, OPER_OR, OPER_NEG, OPER_ASSIGN,
	       OPER_RESERVE_SPACE, OPER_MAIN } nodeOper;

/** Les deux types de noeuds possibles, "numeric" ou "operator"*/
typedef enum { typeNumeric, typeOperator, typeIdentifier } nodeEnum;

/** un noeud numeric (float) permet de stocker une valeur reelle */
typedef struct {
	int valeur;
} numericNodeType;

/** un noeud operator permet de stocker un operateur, le nombre d'operandes et les pointeurs vers les noeuds
*   operande correspondants */
typedef struct {
	int oper;/*!<le type d'operateur de cette structure*/
	int nOperands;/*!<nombre de branche contenant des nodeType*/
	struct nodeTypeTag **op; /*!<tableau de nodetype*/
} operatorNodeType;

/** un noeud identifier fait reference a un identificateur */
typedef struct {
	char *ident;/*!<nom d ela variable*/
	int key;
	int flag;
} identifierNodeType;

/** Cette structure, fondamentale, permet de definir un noeud a geometrie variable. Le type
*   permet de definir le type du noeud (numeric ou operator) et l'union permet, en fonction
*   du type, d'acceder aux bonnes informations */

typedef struct nodeTypeTag {
	nodeEnum type;			/*!<type de neud*/
	int digraphNode;		// Pour generer des beaux graphes avec dot
	union {					/*!<type de neud*/
		numericNodeType t_numeric;
		operatorNodeType t_oper;
		identifierNodeType t_identifier;
	};
} nodeType;

struct _actionNode;
struct _etapeNode;
struct _etapeRefNode;
struct _transitionNode;
struct _transitionRefNode;
/**
* 
*/
typedef struct _actionNode
{
	char *name;
	nodeType *expr;
	
	struct _actionNode *next;
} actionNode;
/**
* 
* \brief permet de gérer la chaine des étapes
*/
typedef struct _etapeRefNode
{
	char *name;
	struct _etapeNode *etape;
	struct _etapeRefNode *next;
} etapeRefNode;
/**
* 
* \brief permet de gérer la chaine des transitions
*/
typedef struct _transitionRefNode
{
	char *name;
	struct _transitionNode *transition;
	struct _transitionRefNode *next;
} transitionRefNode;
/**
* 
* \brief représante une étape
*/
typedef struct _etapeNode
{
	char *name;/*!<nom de l'étape*/
	int id;/*!<nom de l'étape*/
	int active;/*!<nom de l'étape*/
	struct _actionNode *actions;/*!<chaine 
	struct _transitionRefNode *transitionsAmont;/*!<transition avant l'étape*/
	int nbTransitionsAmont;/*!<nombre de transition avant l'étpe*/
	struct _transitionRefNode *transitionsAval;/*!<transition après l'étpe*/
	int nbTransitionsAval;/*!<nombre de transition après l'étpe*/
	
	struct _etapeNode *next;/*!<étape suivante*/
} etapeNode;

typedef struct _transitionNode
{
	char *name;
	int id;
	struct _etapeRefNode *etapesAmont;
	int nbEtapesAmont;
	struct _etapeRefNode *etapesAval;
	int nbEtapesAval;
	nodeType *receptivite;

	struct _transitionNode *next;
} transitionNode;

extern nodeType *createNumericNode(float v);
extern nodeType *createIdentifierNode(char *id, int flag);
extern nodeType *createOperatorNode(int oper, int nOperands, ...);
void generateAsmExpression(nodeType *n, FILE *fout);
extern void grafcet_interpreter();

extern void pushRefEtape(etapeRefNode **head, char *n);
extern void pushRefTransition(transitionRefNode **head, char *n);

extern void pushAction(actionNode **head, actionNode *action);
extern void pushEtape(etapeNode **head, etapeNode *etape);
extern void pushTransition(transitionNode **head, transitionNode *trans);

extern etapeNode *findEtapeByName(etapeNode *head,char *s);

extern void printRefEtapes(etapeRefNode *head);
extern void printRefTransitions(transitionRefNode *head);
extern void printEtapes(etapeNode *head);
extern void printTransitions(transitionNode *head);

extern void makeDual(etapeNode *en, transitionNode *tn);
extern void generateCode(etapeNode *en, transitionNode *tn);
void getOperand(nodeType *nt);