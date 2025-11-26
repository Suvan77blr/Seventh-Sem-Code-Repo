#include <stdio.h>
#include <string.h>

/* Grammar and FIRST/FOLLOW sets */
char prol[7][10]   = { "S", "A", "A", "B", "B", "C", "C" };
char pror[7][10]   = { "A", "Bb", "Cd", "aB", "@", "Cc", "@" };
char prod[7][10]   = { "S->A", "A->Bb", "A->Cd", "B->aB", "B->@", "C->Cc", "C->@" };
char first[7][10]  = { "abcd", "ab", "cd", "a@", "@", "c@", "@" };
char follow[7][10] = { "$", "$", "$", "a$", "b$", "c$", "d$" };

/* Predictive parsing table */
char table[5][6][10];

/* Map non-terminal or terminal to row/column number */
int numr(char c) {
    switch (c) {
        case 'S': return 0;
        case 'A': return 1;
        case 'B': return 2;
        case 'C': return 3;
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case '$': return 4;
        default: return -1;
    }
}

int main() {
    int i, j;

    /* Initialize table with blanks */
    for (i = 0; i < 5; i++)
        for (j = 0; j < 6; j++)
            strcpy(table[i][j], " ");

    /* Display grammar */
    printf("The following grammar is used for Parsing Table:\n");
    for (i = 0; i < 7; i++)
        printf("%s\n", prod[i]);

    /* Fill table using FIRST sets */
    for (i = 0; i < 7; i++) {
        for (j = 0; first[i][j] != '\0'; j++) {
            if (first[i][j] != '@') {
                int r = numr(prol[i][0]) + 1;
                int c = numr(first[i][j]) + 1;
                strcpy(table[r][c], prod[i]);
            }
        }
    }

    /* Fill table for epsilon productions using FOLLOW sets */
    for (i = 0; i < 7; i++) {
        if (pror[i][0] == '@' && strlen(pror[i]) == 1) {
            int r = numr(prol[i][0]) + 1;
            for (j = 0; follow[i][j] != '\0'; j++) {
                int c = numr(follow[i][j]) + 1;
                strcpy(table[r][c], prod[i]);
            }
        }
    }

    /* Set table headers */
    char *colHeader[6] = { " ", "a", "b", "c", "d", "$" };
    char *rowHeader[4] = { "S", "A", "B", "C" };

    for (j = 0; j < 6; j++)
        strcpy(table[0][j], colHeader[j]);
    for (i = 1; i < 5; i++)
        strcpy(table[i][0], rowHeader[i - 1]);

    /* Print parsing table */
    printf("\nPredictive Parsing Table:\n");
    printf("--------------------------------------------------------\n");

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++)
            printf("%-10s", table[i][j]);

        printf("\n--------------------------------------------------------\n");
    }

    return 0;
}
