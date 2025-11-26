#include <stdio.h>
#include <string.h>

/* Global variables */
char input[16], stack[15], action[20];
int i = 0, j = 0, len;

/* Function to check and perform reductions */
void check() {
    int z;
    strcpy(action, "REDUCE TO E -> ");

    /* Check for E -> 4 */
    for (z = 0; z < len; z++) {
        if (stack[z] == '4') {
            printf("%s4", action);
            stack[z] = 'E';
            stack[z + 1] = '\0';
            printf("\n$%s\t%s$\t", stack, input);
        }
    }

    /* Check for E -> 2E2 */
    for (z = 0; z < len - 2; z++) {
        if (stack[z] == '2' && stack[z + 1] == 'E' && stack[z + 2] == '2') {
            printf("%s2E2", action);
            stack[z] = 'E';
            stack[z + 1] = '\0';
            stack[z + 2] = '\0';
            printf("\n$%s\t%s$\t", stack, input);
            i -= 2;
        }
    }

    /* Check for E -> 3E3 */
    for (z = 0; z < len - 2; z++) {
        if (stack[z] == '3' && stack[z + 1] == 'E' && stack[z + 2] == '3') {
            printf("%s3E3", action);
            stack[z] = 'E';
            stack[z + 1] = '\0';
            stack[z + 2] = '\0';
            printf("\n$%s\t%s$\t", stack, input);
            i -= 2;
        }
    }
}

int main() {
    /* Display grammar */
    printf("GRAMMAR is -\nE->2E2 \nE->3E3 \nE->4\n");

    /* Initialize input string */
    strcpy(input, "32423");
    len = strlen(input);
    strcpy(action, "SHIFT");

    /* Print table header */
    printf("\nstack \t input \t action");
    printf("\n$\t%s$\t", input);

    /* Shift and reduce loop */
    for (i = 0, j = 0; j < len; i++, j++) {
        printf("%s", action);
        stack[i] = input[j];
        stack[i + 1] = '\0';
        input[j] = ' ';
        printf("\n$%s\t%s$\t", stack, input);

        check();  // check stack for possible reductions
    }

    /* Final check for any remaining reductions */
    check();

    /* Accept or reject */
    if (stack[0] == 'E' && stack[1] == '\0')
        printf("Accept\n");
    else
        printf("Reject\n");

    return 0;
}
