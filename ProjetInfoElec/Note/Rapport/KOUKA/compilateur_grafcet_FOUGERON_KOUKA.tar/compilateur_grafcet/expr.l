%{
#include <stdlib.h>
#include "ast.h"
#include "y.tab.h"

%}

%%

[a-z][a-z0-9]* { yylval.s = strdup(yytext); return T_VARIABLE; }
[0-9]* 		{ yylval.i = atoi(yytext); return T_NUMERIC; }

">="            {return T_GE;}
"<="            {return T_LE;}
"=="            {return T_EQ;}
"!="            {return T_NE;}

[ \t\n]+
.               { return *yytext; }

%%
int yywrap(void) {
    return 1;
}
