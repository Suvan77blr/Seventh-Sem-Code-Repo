%{
#include <stdio.h>
#include "y.tab.h"
%}

%%

"="     { printf("\nOperator is EQUAL"); return EQUAL; }
"+"     { printf("\nOperator is PLUS"); return PLUS; }
"-"     { printf("\nOperator is MINUS"); return MINUS; }
"/"     { printf("\nOperator is DIVISION"); return DIV; }
"*"     { printf("\nOperator is MULTIPLICATION"); return MUL; }

[a-zA-Z][a-zA-Z0-9]* {
        printf("\nIdentifier is %s", yytext);
        return ID;
}

[ \t\n] ;      /* ignore whitespace */

.       return yytext[0];

%%

int yywrap() {
    return 1;
}
