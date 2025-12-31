#include <stdio.h>
#include <ctype.h>
#include <string.h>

void followfirst(char, int, int);
void follow(char c);
void findfirst(char, int, int);

int count, n = 0, m = 0;
char calc_first[10][100];
char calc_follow[10][100];
char production[10][10];
char f[10], first[10];
char ck;
int e, k;

int main() {
    int i, j, choice;
    char c;
    count = 8;

    // Input Grammar
    strcpy(production[0], "E=TR");
    strcpy(production[1], "R=+TR");
    strcpy(production[2], "R=#");
    strcpy(production[3], "T=FY");
    strcpy(production[4], "Y=*FY");
    strcpy(production[5], "Y=#");
    strcpy(production[6], "F=(E)");
    strcpy(production[7], "F=i");

    char done[count];
    int ptr = -1;
    int jm = 0;

    // Initialize calc_first
    for (k = 0; k < count; k++)
        for (j = 0; j < 100; j++)
            calc_first[k][j] = '!';

    printf("\nFIRST sets:\n");
    for (k = 0; k < count; k++) {
        c = production[k][0];
        int flag = 0;
        for (j = 0; j <= ptr; j++)
            if (c == done[j])
                flag = 1;
        if (flag) continue;

        findfirst(c, 0, 0);
        ptr++;
        done[ptr] = c;

        printf("FIRST(%c) = { ", c);
        for (i = jm; i < n; i++) {
            printf("\'%c\', ", first[i]);
            calc_first[ptr][i - jm + 1] = first[i];
        }
        printf("}\n");
        jm = n;
        calc_first[ptr][0] = c;
    }

    printf("\n--------------------------------------\n\n");

    // FOLLOW computation
    char donee[count];
    ptr = -1;
    int km = 0;
    printf("FOLLOW sets:\n");

    for (e = 0; e < count; e++) {
        ck = production[e][0];
        int flag = 0;
        for (j = 0; j <= ptr; j++)
            if (ck == donee[j])
                flag = 1;
        if (flag) continue;

        follow(ck);
        ptr++;
        donee[ptr] = ck;

        printf("FOLLOW(%c) = { ", ck);
        for (i = km; i < m; i++)
            printf("\'%c\', ", f[i]);
        printf("}\n");
        km = m;
    }
    return 0;
}

// FOLLOW of non-terminal
void follow(char c) {
    int i, j;
    if (production[0][0] == c)
        f[m++] = '$';

    for (i = 0; i < count; i++) {
        for (j = 2; j < strlen(production[i]); j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0')
                    followfirst(production[i][j + 1], i, j + 2);

                if (production[i][j + 1] == '\0' && c != production[i][0])
                    follow(production[i][0]);
            }
        }
    }
}

// FIRST of symbol
void findfirst(char c, int q1, int q2) {
    int j;
    if (!isupper(c)) {
        first[n++] = c;
        return;
    }

    for (j = 0; j < count; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                if (production[q1][q2] == '\0')
                    first[n++] = '#';
                else if (production[q1][q2] != '\0')
                    findfirst(production[q1][q2], q1, q2 + 1);
            } else if (!isupper(production[j][2])) {
                first[n++] = production[j][2];
            } else {
                findfirst(production[j][2], j, 3);
            }
        }
    }
}

// Helper to include FIRST of next symbol into FOLLOW
void followfirst(char c, int c1, int c2) {
    int i, j;
    if (!isupper(c))
        f[m++] = c;
    else {
        for (i = 0; i < count; i++)
            if (calc_first[i][0] == c)
                break;
        j = 1;
        while (calc_first[i][j] != '!') {
            if (calc_first[i][j] != '#')
                f[m++] = calc_first[i][j];
            else {
                if (production[c1][c2] == '\0')
                    follow(production[c1][0]);
                else
                    followfirst(production[c1][c2], c1, c2 + 1);
            }
            j++;
        }
    }
}

/*
I have a few compiler design questions which needs C/Lex programs .. i shal also give the sample io if available .. can you give me minimalist, easy to write & copyable code which can be written easily
*/