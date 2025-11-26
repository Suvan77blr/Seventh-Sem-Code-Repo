#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD 10
#define MAX_LEN 20
#define MAX_STACK 50

// Structure to hold a production
typedef struct {
    char lhs;       // Left-hand side
    char rhs[10];   // Right-hand side
} Production;

Production prods[MAX_PROD];
int numProd;

// Stack for parsing
char stack[MAX_STACK];
int top = -1;

// Function to push a symbol onto stack
void push(char c) {
    stack[++top] = c;
    stack[top+1] = '\0';
}

// Function to pop n symbols from stack
void pop(int n) {
    if (n > top + 1) n = top + 1;
    top -= n;
    stack[top+1] = '\0';
}

// Function to print current stack and input
void printAction(const char *action, char *input) {
    printf("$%s\t\t%s$\t\t%s\n", stack, input, action);
}

// Function to try reducing the stack with any production
int reduceStack() {
    int changed = 0;
    for (int i = 0; i < numProd; i++) {
        int rhs_len = strlen(prods[i].rhs);
        if (rhs_len > top + 1) continue; // RHS longer than stack
        // Compare stack top with RHS
        if (strncmp(&stack[top - rhs_len + 1], prods[i].rhs, rhs_len) == 0) {
            char action[MAX_LEN];
            sprintf(action, "REDUCE TO %c -> %s", prods[i].lhs, prods[i].rhs);
            printAction(action, "");
            pop(rhs_len);
            push(prods[i].lhs);
            changed = 1;
            break; // Only one reduction at a time, then recheck
        }
    }
    return changed;
}

int main() {
    char input[MAX_LEN];
    printf("Enter number of productions: ");
    scanf("%d", &numProd);
    getchar(); // consume newline

    printf("Enter productions (e.g., E->2E2):\n");
    for (int i = 0; i < numProd; i++) {
        char temp[20];
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = 0; // remove newline
        prods[i].lhs = temp[0];
        strcpy(prods[i].rhs, temp + 3); // skip "E->"
    }

    printf("Enter input string to parse: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    printf("\nstack\t\tinput\t\taction\n");

    // Initialize stack
    top = -1;
    stack[0] = '\0';

    int i = 0;
    while (input[i] != '\0') {
        // SHIFT
        char action[MAX_LEN];
        sprintf(action, "SHIFT");
        push(input[i]);
        input[i] = ' '; // remove shifted symbol
        printAction(action, input);

        // Keep reducing as long as possible
        while (reduceStack());
        i++;
    }

    // Final reductions after all shifts
    while (reduceStack());

    // Accept if stack has only start symbol (assume prods[0].lhs is start)
    if (top == 0 && stack[0] == prods[0].lhs) {
        printf("Accept\n");
    } else {
        printf("Reject\n");
    }

    return 0;
}
