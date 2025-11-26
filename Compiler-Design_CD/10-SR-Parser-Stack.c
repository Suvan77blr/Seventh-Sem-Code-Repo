#include <stdio.h>
#include <string.h>

#define MAX 50

char stack[MAX], input[MAX];
int top = -1;

/* Push to stack */
void push(char c) {
    stack[++top] = c;
}

/* Pop from stack */
void pop() {
    if (top >= 0) top--;
}

/* Try to reduce the stack contents based on grammar */
int reduce() {
    // Rule: E->id
    if (top >= 1 && stack[top] == 'd' && stack[top - 1] == 'i') {
        pop();  // pop 'd'
        pop();  // pop 'i'
        push('E');
        printf("REDUCE: E->id\n");
        return 1;
    }

    // Rule: E->E+E
    if (top >= 2 &&
        stack[top] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top - 2] == 'E') {
        pop(); pop(); pop();
        push('E');
        printf("REDUCE: E->E+E\n");
        return 1;
    }

    // Rule: E->E*E
    if (top >= 2 &&
        stack[top] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top - 2] == 'E') {
        pop(); pop(); pop();
        push('E');
        printf("REDUCE: E->E*E\n");
        return 1;
    }

    // Rule: E->(E)
    if (top >= 2 &&
        stack[top] == ')' &&
        stack[top - 1] == 'E' &&
        stack[top - 2] == '(') {
        pop(); pop(); pop();
        push('E');
        printf("REDUCE: E->(E)\n");
        return 1;
    }

    return 0; // no reduction performed
}

int main() {
    printf("Enter input string: ");
    scanf("%s", input);

    int i = 0, len = strlen(input);

    printf("\nSHIFT-REDUCE PARSER TRACE:\n\n");

    while (i < len) {
        printf("SHIFT: %c\n", input[i]);
        push(input[i]);
        i++;

        // Try reducing as long as possible
        while (reduce());
    }

    // Final reductions
    while (reduce());

    printf("\nFinal Stack: ");
    for (int j = 0; j <= top; j++) {
        printf("%c", stack[j]);
    }
    printf("\n");

    if (top == 0 && stack[0] == 'E')
        printf("\nINPUT ACCEPTED\n");
    else
        printf("\nINPUT REJECTED\n");

    return 0;
}
