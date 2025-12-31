/* program name : lexp.l */
/* program to recognize elements of a C program */

%{
#include <stdio.h>
#include <stdlib.h>

int COMMENT = 0;
int cnt = 0;
%}

identifier [a-zA-Z_][a-zA-Z0-9_]*

%%

#.*                        { printf("\n%s is a PREPROCESSOR DIRECTIVE", yytext); }

int|float|char|double|
while|for|do|if|break|continue|
void|switch|case|long|struct|const|
typedef|return|else|goto
                            { if (!COMMENT) printf("\n\t%s is a KEYWORD", yytext); }

"/*"                        { COMMENT = 1; }
"*/"                        { COMMENT = 0; cnt++; }

{identifier}\(              { if (!COMMENT) printf("\n\nFUNCTION\n\t%s", yytext); }

"{"                         { if (!COMMENT) printf("\n BLOCK BEGINS"); }
"}"                         { if (!COMMENT) printf("\n BLOCK ENDS"); }

{identifier}(\[[0-9]*\])?   { if (!COMMENT) printf("\n %s IDENTIFIER", yytext); }

\"[^\"]*\"                  { if (!COMMENT) printf("\n\t%s is a STRING", yytext); }

[0-9]+                      { if (!COMMENT) printf("\n\t%s is a NUMBER", yytext); }

"="                         { if (!COMMENT) printf("\n\t%s is an ASSIGNMENT OPERATOR", yytext); }

"<="|">="|"=="|"!="|"<"|">" { if (!COMMENT) printf("\n\t%s is a RELATIONAL OPERATOR", yytext); }

[();]                       { if (!COMMENT) ECHO; }

[ \t\n]+                    ;   /* ignore whitespace */

.                           ;   /* ignore everything else */

%%

int main(int argc, char **argv)
{
    FILE *file;
    if (argc > 1)
    {
        file = fopen(argv[1], "r");
        if (!file)
        {
            printf("Could not open %s\n", argv[1]);
            exit(0);
        }
        yyin = file;
    }

    yylex();
    printf("\n\nTotal number of comments: %d\n", cnt);
    return 0;
}

int yywrap()
{
    return 1;
}


/*
TEST CASE:
    Input:
        #include <stdio.h>
        int main() {
            int x = 10;
            printf("Hello, world!\n");
            return 0;
        }

    Output:
        #include is a PREPROCESSOR DIRECTIVE
        int is a KEYWORD
        main is a FUNCTION
        BLOCK BEGINS
        int is a KEYWORD
        x IDENTIFIER
        = is an ASSIGNMENT OPERATOR
        10 is a NUMBER
        ; 
        printf is a FUNCTION
        "Hello, world!" is a STRING
        ; 
        return is a KEYWORD
        0 is a NUMBER
        ; 
        BLOCK ENDS

        Total number of comments: 0
*/