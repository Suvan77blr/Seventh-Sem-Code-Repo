/* Program to simulate a Lexical Analyzer in C to:
    - Validate AND
    - Identify the type of a given operator.
*/

#include <stdio.h>
#include <string.h>

enum bool {
    false, true
};

int main() {
    char arithmetic[5] = { '+', '-', '*', '/', '%' };
    char relational[4] = { '<', '>', '!', '=' };
    char bitwise[5] = { '&', '^', '~', '|', '\0' };
    char str[3] = { ' ', ' ', '\0'};

    printf("Enter value to be identified: ");
    scanf("%s", str);       // to store input string (1 or 2 chars)

    int i;
    enum bool valid = false;     // EXTRA.
    
    if(str[0] == '=' && str[1] == '\0') {
        printf("\nIt is an Assignment operator");
        valid = true;
    }

    // Logical Operators.
    if(((str[0] == '&' || str[0] == '|') && str[0] == str[1] || str[0] == '!' && str[1] == '\0')) {
        printf("\nIt is a Logical Operator");
        valid = true;
    }

    // // Relational Operators.
    if ((str[0] == '<' && str[1] == '\0') || (str[0] == '>' && str[1] == '\0')) {
        printf("\nIt is a Relational operator");
        valid = true;
    }
    else if ((str[0] == '<' && str[1] == '=') || (str[0] == '>' && str[1] == '=') ||
             (str[0] == '=' && str[1] == '=') || (str[0] == '!' && str[1] == '=')
            ) {
                printf("\nIt is a Relational operator");
                valid = true;
            }

    // for(i = 0; i<4; i++) {
    //     // if(str[0] == relational[i] && str[1] == '=') {
    //     if ((str[0] == relational[i] && str[1] == '=') && str[0] != '=') {
    //         printf("\nIt is a Relational operator");
    //         break;
    //     }
    // }


    // Bitwise Operators.
    for(i = 0; i<4; i++) {
        if((str[0] == bitwise[i] && str[1] == '\0') || ((str[0] == '<' || str[0] == '>') && str[1] == str[0] )) {
            printf("\nIt is a Bitwise operator");
            valid = true;
            break;
        }
    }

    // Ternary operators. (?:)
    if( str[0]=='?' && str[1]==':') {
        printf("\nIt is a Ternary operator");
        valid = true;    
    }

    // Unary, Assignment and Arithmetic operators.
    for(i=0; i<5; i++) {
        if((str[0] == '+' || str[0] == '-') && str[0] == str[1]) {
            printf("\nIt is a Unary operator");
            valid = true;
            break;
        }

        else if ((str[0] == arithmetic[i] && str[1] == '=') || (str[0] == '=' && str[1] == ' ') ) {
            printf("\nIt is an Assignment operator");
            valid = true;
            break;
        }

        else if (str[0] == arithmetic[i] && str[1] == '\0') {
            printf("\nIt is an Arithmetic operator");
            valid = true;
            break;
        }
    }

    if(!valid) {
        printf("%s is an Invalid operator");
    }

    return 0;
}