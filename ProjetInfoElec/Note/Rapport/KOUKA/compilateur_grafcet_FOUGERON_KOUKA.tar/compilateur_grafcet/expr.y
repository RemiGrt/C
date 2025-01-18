%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "ast.h"

int yylex(void);
void yyerror(char *s);
nodeType *exprRoot;

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

%token T_NUMERIC T_VARIABLE

%type <i> T_NUMERIC
%type <s> T_VARIABLE 
%type <np> program_expr
%type <np> expr 

%%

program_expr: expr { exprRoot=$1; }
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
	| T_VARIABLE { $$=createIdentifierNode($1); }
        ;
%%

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(void) {
    	yyparse();
        generateAsm(exprRoot,"res.asm");
    	return 0;
}
