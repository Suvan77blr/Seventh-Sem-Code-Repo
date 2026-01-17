/*
    OpenMP Program to compute the value of the sum of two arrays 
        - And store the result in corresponding elements of 3rd array.

    Compilation:
    gcc -fopenmp 02-OMP-Two-Array-Sum.c -o sum_arrays
    ./sum_arrays

*/

#include <stdio.h>
#include <omp.h>
#define N 10
void displayElements(int* arr, int n);

int main() {
    int n = N;
    int A[N], B[N], C[N];

    // Array Initialization.
    for(int i = 0; i<n; i++) {
        A[i] = i + 1;       // 1, 2, 3, ..
        B[i] = (i+1) * 2;   // 2, 4, 6, ..
    }

    printf("Array A: ");
    displayElements(A, n);
    printf("Array B: ");
    displayElements(B, n);

    // Parallel addition and storing in C.
    #pragma omp parallel for \
            default(none) \
            shared(A, B, C, n) \
            schedule(static)
    for(int i = 0; i<n; i++) {
        int tid = omp_get_thread_num();
        C[i] = A[i] + B[i];
        printf("Thread %d computed C[%d]\n", tid, i);
    }

    printf("Array C (A+B): ");
    displayElements(C, n);

    return 0;
}

void displayElements(int* arr, int n) {
    printf("[ ");
    for(int i=0; i<n; i++) 
        printf("%d ", arr[i]);
    printf("]\n");
}