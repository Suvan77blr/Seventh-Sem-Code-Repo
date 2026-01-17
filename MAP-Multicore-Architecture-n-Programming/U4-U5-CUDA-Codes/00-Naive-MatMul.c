/*
    Program showing the Naive Matrix Multiplication code.
*/

#include <stdio.h>
#include <stdlib.h>
#define N 4

int** alloc2D(int m, int n);
void dealloc2D(int** mat, int m, int n);

int main() {
    int n = N;

    int** A = alloc2D(n, n);
    int** B = alloc2D(n, n);
    int** C = alloc2D(n, n);

    // Assigning A.
    int value = 1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            A[i][j] = value;
            value++;
        }
    }
    
    // Assigning B.
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            B[i][j] = (i == j) ? 1 : 0;
        }
    }

    // Naive matrix multiplication
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Print result
    printf("Matrix C (A x B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    dealloc2D(A, n, n);
    dealloc2D(B, n, n);
    dealloc2D(C, n, n);
}

int** alloc2D(int m, int n) {
    int** mat = (int**)malloc(m * sizeof(int*));
    for(int i=0; i<m; i++) {
        mat[i] = (int*)malloc(n * sizeof(int));   // *(mat+i)
    }

    return mat;
}

void dealloc2D(int** mat, int m, int n) {
    for(int i=0; i<m; i++)
        free(mat[i]);
    free(mat);
}

/*
// NOTE: int** allocation is simple but not cache-friendly;
//       consider contiguous allocation later.
//       => CPU cache lines are under-utilized. (each row is alloced seperately & they maybe far apart in memory.)
*/

void cache_friendly_version() {

    int* A = malloc(n * n * sizeof(int));
    int* B = malloc(n * n * sizeof(int));
    int* C = malloc(n * n * sizeof(int));
    
    // element access:  A[i * n + j]

    // A-assignment.
    int value = 1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            A[i*n + j] = value;     // Change here!
            value = value + 1;
        }
    }

    // B-assignment.
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            B[i*n + j] = (i == j) ? 1 : 0;     // Change here!
        }
    }

    // Naive matrix-multiplication.
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            C[i*n + j] = 0;             // Change here!
            for(int k=0; k<n; k++) {
                C[i*n + j] += A[i*n + k] * B[k*n + j];       // Change here!
            }
        }
    }

    // Print result
    printf("Matrix C (A x B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i * n + j]);    // Change here!
        }
        printf("\n");
    }

    free(A); free(B); free(C);
    return 0;
}

/*
Cache-friendly version 2:
int** A = malloc(n * sizeof(int*));
A[0] = malloc(n * n * sizeof(int));
for (int i = 1; i < n; i++)
    A[i] = A[0] + i * n;

*/
