// Three-Address-Code for a given expr/statement.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pm();
void plus_op();
void div_op();
void str_reverse(char *s);

int i, ch, j, l, addr = 100;
char ex[20], exp[20], exp1[20], exp2[20], id1[10], op[10], id2[10];

int main() {
    while (1) {

        printf("\n1. Assignment\n2. Arithmetic\n3. Relational\n4. Exit\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {

        case 1: {
            printf("\nEnter the expression with assignment operator: ");
            scanf("%s", exp);

            l = strlen(exp);
            exp2[0] = '\0';
            i = 0;

            while (exp[i] != '=')
                i++;

            strncat(exp2, exp, i);

            str_reverse(exp);
            exp1[0] = '\0';
            strncat(exp1, exp, l - (i + 1));
            str_reverse(exp1);

            printf("Three Address Code:\ntemp = %s\n%s = temp\n", exp1, exp2);
            break;
        }

        case 2: {
            printf("\nEnter the expression with arithmetic operator: ");
            scanf("%s", ex);

            strcpy(exp, ex);
            l = strlen(exp);
            exp1[0] = '\0';

            for (i = 0; i < l; i++) {
                if (exp[i] == '+' || exp[i] == '-') {
                    if (exp[i + 2] == '/' || exp[i + 2] == '*')
                        pm();
                    else
                        plus_op();
                    break;
                } else if (exp[i] == '/' || exp[i] == '*') {
                    div_op();
                    break;
                }
            }
            break;
        }

        case 3: {
            printf("Enter the expression with relational operator (a < b): ");
            scanf("%s %s %s", id1, op, id2);

            if (!(
                strcmp(op, "<") == 0 || strcmp(op, ">") == 0 ||
                strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0 ||
                strcmp(op, "==") == 0 || strcmp(op, "!=") == 0
            )) {
                printf("Expression error\n");
            } else {
                printf("\n%d\tif %s %s %s goto %d", addr, id1, op, id2, addr + 3);
                addr++;
                printf("\n%d\tT := 0", addr++);
                printf("\n%d\tgoto %d", addr, addr + 2);
                addr++;
                printf("\n%d\tT := 1\n", addr);
            }
            break;
        }

        case 4:
            exit(0);
        }
    }

    return 0;
}

/* Reverse a string (standard C replacement for strrev) */
void str_reverse(char *s) {
    int len = strlen(s);
    for (int a = 0, b = len - 1; a < b; a++, b--) {
        char tmp = s[a];
        s[a] = s[b];
        s[b] = tmp;
    }
}

void pm() {
    str_reverse(exp);
    j = l - i - 1;

    exp1[0] = '\0';
    strncat(exp1, exp, j);
    str_reverse(exp1);

    printf("Three Address Code:\ntemp = %s\ntemp1 = %c %c temp\n",
           exp1, exp[j + 1], exp[j]);
}

void div_op() {
    exp1[0] = '\0';
    strncat(exp1, exp, i + 2);

    printf("Three Address Code:\ntemp = %s\ntemp1 = temp %c %c\n",
           exp1, exp[i + 2], exp[i + 3]);
}

void plus_op() {
    exp1[0] = '\0';
    strncat(exp1, exp, i + 2);

    printf("Three Address Code:\ntemp = %s\ntemp1 = temp %c %c\n",
           exp1, exp[i + 2], exp[i + 3]);
}
