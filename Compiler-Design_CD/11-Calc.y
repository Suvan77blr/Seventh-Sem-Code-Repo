%{
#include <stdio.h>
int flag = 0;
%}

%token NUMBER

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%

ArithmeticExpression:
      E { 
            printf("\nResult = %d\n", $$);
            return 0;
      }
;

E : E '+' E    { $$ = $1 + $3; }
  | E '-' E    { $$ = $1 - $3; }
  | E '*' E    { $$ = $1 * $3; }
  | E '/' E    { $$ = $1 / $3; }
  | E '%' E    { $$ = $1 % $3; }
  | '(' E ')'  { $$ = $2; }
  | NUMBER     { $$ = $1; }
;

%%

/* driver code */
int main() {
    printf("\nEnter any arithmetic expression (supports + - * / % and parentheses):\n");
    yyparse();

    if (flag == 0)
        printf("\nEntered arithmetic expression is Valid\n\n");

    return 0;
}

void yyerror(const char *s) {
    printf("\nEntered arithmetic expression is Invalid\n\n");
    flag = 1;
}
