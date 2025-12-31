#include <stdio.h>
#include <string.h>
#define MAX 30

int n, t, nt;
char prods[MAX][MAX];
char firstSet[20][20], followSet[20][20];
char Ts[20][20], nonTs[20][20];
int table[20][20];

int findNT(char c) {
    for(int i=0; i<nt; i++) {
        if(nonTs[i] == c) return i;
    }
    return -1;
}

int findT(char c) {
    for(int i=0; i<t; i++) {
        if(Ts[i] == c) return i;
    }
    return -1;
}

void input() {
    printf("Enter the number of productions: ");
    scanf("%d", &n);
    
    printf("Enter the productions, one by one: \n");
    for(int i=0; i<n; i++) {
        scanf("%s", prods[i]);
    }
    
    nt = t = 0;
}

void process() {
    int i, j;

    for(i=0; i<n; i++) {
        if(findNT(prods[i][0]) == -1) {
            nonTs[nt++] = prods[0][i];           
        }
    }

    for(i = 0; i<n; i++) {
        for(j = 3; j<strlen(prods[i]); j++) {
            char ch = prods[i][j];
            if(ch != 'e' && findNT(ch) == -1 && findT(ch) == -1) {
                Ts[t++] = ch;                
            }
        }
    }

    Ts[t++] = '$';

    for(i=0; i<nt; i++) {
        for(j=0; j<t; j++) {
            table[i][j] = -1;
        }
    }

    for(i=0; i<nt; i++) {
        for(j=0; j<t; j++) {
            printf("Enter FIRST(%c): ", nonTs[i]);
            scanf("%s", firstSet[i]);
        }
    }

    for(i=0; i<nt; i++) {
        for(j=0; j<t; j++) {
            printf("Enter FOLLOW(%c): ", nonTs[i]);
            scanf("%s", followSet[i]);
        }
    }

    for(i=0; i<nt; i++) {
        int ntIndex = findNT(prods[i][0]);
        char rhsFirst = prods[i][3];

        int termIdx = findT(rhsFirst);
        int nonTermIdx = findNT(rhsFirst);

        if(termIdx != -1) 
            table[ntIndex][termIdx] = i;
        
        else if(nonTermIdx != -1) {
            for(j=0; j<strlen(firstSet[nonTermIdx]); j++) {
                int idx = findT(firstSet[nonTermIdx][j]);
                if(idx != -1) {
                    table[ntIndex][idx] = i;
                }   
            }
        }

        else if (rhsFirst == 'e') {
            for(j=0; j<strlen(followSet[ntIndex]); j++) {
                int idx = findT(followSet[ntIndex][j]);
                if(idx != -1) {
                    table[ntIndex][idx] = i;
                }   
            }
        }
    }

    printf("\nLL Parsing Table:\n\t");
    for(i=0; i<t; i++) {
        printf("%c\t", Ts[i]);
    } 
    printf("\n");

    for(i=0; i<nt; i++) {
        printf("%c\t", nonTs[i]);
        for(j=0; j<t; j++) {
            if(table[i][j] == -1) printf("-\t");
            else printf("%s\t", prods[table[i][j]]);
        }
        printf("\n");
    }
}

int main() {
    input();
    process();
    return 0;
}