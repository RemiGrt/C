%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "ast.h"
#include "canon_serial.h"

int yylex(void);
void yyerror(char *s);
nodeType *grafcetRoot;
int active;

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
%type <np> program_grafcet
%type <np> liste_definitions
%type <np> definition
%type <np> definition_etape 
%type <np> active 
%type <np> liste_actions 
%type <np> action 
%type <np> definition_transition 
%type <np> liste_etapes 
%type <np> liste_etapes1
%type <np> etape1
%type <np> expr 

%%

program_grafcet: liste_definitions { grafcetRoot=$1; }
	; 

liste_definitions :  liste_definitions definition { $$=createOperatorNode(OPER_SEQUENCE, 2, $1, $2); }
	| definition
	;
	
definition : definition_etape
	| definition_transition
	;

definition_etape : T_STEP T_VARIABLE '(' liste_actions ')' active 
	{ 	nodeType *n=createIdentifierNode($2,0);
		$$=createOperatorNode(OPER_STEP, 3, n, $4, $6);
	}
	;

active : T_ACTIVE { $$=createNumericNode(1) ; }
	| { $$=createNumericNode(0); }
	;

liste_actions : liste_actions ',' action { $$=createOperatorNode(OPER_SEQUENCE, 2, $1, $3); }
	| action
	;

action : T_VARIABLE '=' expr 
	{ 	nodeType *n=createIdentifierNode($1,0);
		$$=createOperatorNode(OPER_ASSIGN, 2, n, $3);
	}
	;

definition_transition : T_TRANSITION T_VARIABLE '(' liste_etapes ',' liste_etapes ',' expr ')' 
	{ 	nodeType *n=createIdentifierNode($2,0);
		$$=createOperatorNode(OPER_TRANSITION, 4, n, $4, $6, $8);
	} 
	;

liste_etapes : '{' liste_etapes1 '}' { $$=$2; }
        ;

liste_etapes1 : liste_etapes1 ',' etape1 { $$=createOperatorNode(OPER_SEQUENCE, 2, $1, $3); }
	| etape1
	;

etape1: T_VARIABLE { $$=createIdentifierNode($1,0); }
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
    	yyparse();
        generateAsm(grafcetRoot,"res.asm");
	printEtapes();
	printTransitions();
	initserial();
	grafcet_interpreter();
    	return 0;
}
