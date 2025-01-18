%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "ast.h"

int yylex(void);
void yyerror(char *s);
nodeType *grafcetRoot;
etapeRefNode *listeRefEtapes;
etapeRefNode *listeRefEtapesAmont;
etapeRefNode *listeRefEtapesAval;
etapeNode *listeEtapes;
transitionNode *listeTransitions;
actionNode *listeActions;
int active;
int etapeId;
int transactionId;

%}

%union {
	int i;
	char *s;
	nodeType *np;
};

%left T_GE T_LE T_EQ T_NE '>' '<'
%left '+' '-' '|' 
%left '*' '/' '.' 
%nonassoc T_UMINUS
%nonassoc T_NNOT

%token T_NUMERIC T_VARIABLE T_STEP T_TRANSITION T_ACTIVE T_RISE T_FALL

%type <i> T_NUMERIC
%type <s> T_VARIABLE 
%type <np> expr 

%%

program_grafcet: { 
		listeEtapes=NULL; 
		listeTransitions=NULL; 
		etapeId=0;
		transactionId=0;
		} 
	liste_definitions 
	; 

liste_definitions :  liste_definitions definition 
	| definition
	;
	
definition : definition_etape
	| definition_transition
	;

definition_etape : active T_STEP T_VARIABLE '(' { listeActions=NULL; } liste_actions ')'
	{ 	
		etapeNode* etape=(etapeNode*)malloc(sizeof(etapeNode));
		etape->active=active;
		etape->id=etapeId++;
		etape->name=$3;
		etape->actions=listeActions;
		etape->transitionsAmont=NULL;
		etape->nbTransitionsAmont=0;
		etape->transitionsAval=NULL;
		etape->nbTransitionsAval=0;
		etape->next=NULL; 

		pushEtape(&listeEtapes, etape);
	}
	;

active : T_ACTIVE { active=1 ; }
	| { active=0; }
	;

liste_actions : liste_actions ',' action
	| action
	;

action : T_VARIABLE '=' expr 
	{ 	
		actionNode *action=(actionNode *)malloc(sizeof(actionNode));
		action->name=$1;
		action->expr=$3;
		action->next=NULL;

		pushAction(&listeActions,action);
	}
	;

definition_transition : 
	T_TRANSITION T_VARIABLE '(' 
	liste_etapes { listeRefEtapesAmont=listeRefEtapes; } ',' 
	liste_etapes { listeRefEtapesAval=listeRefEtapes; } ',' expr ')' 
	{ 	

		transitionNode *trans=(transitionNode *)malloc(sizeof(transitionNode));
		trans->name=$2;
		trans->id=transactionId++;
		trans->etapesAmont=listeRefEtapesAmont;
		trans->nbEtapesAmont=0;
		trans->etapesAval=listeRefEtapesAval;
		trans->nbEtapesAval=0;
		trans->receptivite=$10;
		trans->next=NULL;

		pushTransition(&listeTransitions,trans);
	} 
	;

liste_etapes : '{' { listeRefEtapes=NULL; } liste_etapes1 '}'
        ;

liste_etapes1 : liste_etapes1 ',' etape1
	| etape1
	;

etape1: T_VARIABLE { pushRefEtape(&listeRefEtapes,$1); }
	;

expr: T_NUMERIC { $$ = createNumericNode($1); }
    	| expr '+' expr { $$ = createOperatorNode(OPER_ADD,2,$1,$3); }
        | expr '-' expr { $$ = createOperatorNode(OPER_SUB,2,$1,$3); }
        | expr '*' expr { $$ = createOperatorNode(OPER_MULT,2,$1,$3); }
        | expr '/' expr { $$ = createOperatorNode(OPER_DIV,2,$1,$3); }
        | '(' expr ')' { $$ = $2 ; }
        | expr '<' expr { $$ = createOperatorNode(OPER_INF,2,$1,$3); }
        | expr '>' expr { $$ = createOperatorNode(OPER_SUP,2,$1,$3); }
        | expr T_GE expr { $$ = createOperatorNode(OPER_GE,2,$1,$3); }
        | expr T_LE expr { $$ = createOperatorNode(OPER_LE,2,$1,$3); }
        | expr T_NE expr { $$ = createOperatorNode(OPER_NE,2,$1,$3); }
        | expr T_EQ expr { $$ = createOperatorNode(OPER_EQ,2,$1,$3); }
        | '!' expr %prec T_NNOT { $$ = createOperatorNode(OPER_NOT,1,$2); }
        | expr '.' expr { $$ = createOperatorNode(OPER_AND,2,$1,$3); }
        | expr '|' expr { $$ = createOperatorNode(OPER_OR,2,$1,$3); }
        | '-' expr %prec T_UMINUS { $$ = createOperatorNode(OPER_NEG,1,$2); }
	| T_VARIABLE { $$=createIdentifierNode($1,0); }
	| T_VARIABLE '\'' T_RISE { $$=createIdentifierNode($1,1); }
	| T_VARIABLE '\'' T_FALL { $$=createIdentifierNode($1,2); }
        ;
%%

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(void) {
  yyparse(); // fait pr yak
	//printEtapes(listeEtapes); 
	//printTransitions(listeTransitions);
	makeDual(listeEtapes,listeTransitions);
	generateCode(listeEtapes,listeTransitions);
/*
        generateAsm(grafcetRoot,"res.asm");
	printEtapes();
	printTransitions();
*/
    	return 0;
}
