#include <stdio.h>
#include <string.h>

char op[5], arg1[10], arg2[10], result[10];

int main() {
    FILE *fp1, *fp2;

    fp1 = fopen("14-input.txt", "r");
    fp2 = fopen("14-output.txt", "w");

    if (!fp1 || !fp2) {
        printf("Error opening file.\n");
        return 1;
    }

    /* Read four strings per line safely */
    while (fscanf(fp1, "%s %s %s %s", op, arg1, arg2, result) == 4) {

        if (strcmp(op, "+") == 0) {
            fprintf(fp2, "MOV R0,%s\n", arg1);
            fprintf(fp2, "ADD R0,%s\n", arg2);
            fprintf(fp2, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "*") == 0) {
            fprintf(fp2, "MOV R0,%s\n", arg1);
            fprintf(fp2, "MUL R0,%s\n", arg2);
            fprintf(fp2, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "-") == 0) {
            fprintf(fp2, "MOV R0,%s\n", arg1);
            fprintf(fp2, "SUB R0,%s\n", arg2);
            fprintf(fp2, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "/") == 0) {
            fprintf(fp2, "MOV R0,%s\n", arg1);
            fprintf(fp2, "DIV R0,%s\n", arg2);
            fprintf(fp2, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "=") == 0) {
            fprintf(fp2, "MOV R0,%s\n", arg1);
            fprintf(fp2, "MOV %s,R0\n", result);
        }
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
