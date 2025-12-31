/*
    This Grammars accepts assignments like:
    x = a + b
    abc = x * y
*/

%{
#include <stdio.h>
%}

%token ID
%token PLUS MINUS MUL DIV
%token EQUAL

%%

statement:
      ID EQUAL expr {
            printf("\nValid arithmetic expression\n");
      }
;

expr:
      expr PLUS ID
    | expr MINUS ID
    | expr MUL ID
    | expr DIV ID
    | ID
;

%%

extern FILE *yyin;

int main() {
    printf("\nEnter expression (e.g., x = a + b):\n\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    printf("\nSyntax Error: %s\n", s);
}
