/*
    Pthreads Program to simulate DAXPY Loop.
        => Double-precision A-X-Plus-Y
    : for( i = 0->n ) {
        y[i] = a * X[i] + Y[i];
      }
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 4
double *x, *y, a;
int n;

// Thread Function.
void *daxpy(void* args) {
    int id = *(int*)args + 1;
    for(int i=0; i<n; i++) {
        y[i] = a * x[i] + y[i];
    }
    return NULL;
}

int main(void) {
    printf("Enter \'n\' : ");
    scanf("%d", &n);

    x = (double*) malloc(n * sizeof(double));
    y = (double*) malloc(n * sizeof(double));

    printf("Enter values of x[]: ");
    for(int i=0; i<n; i++) {
        scanf("%lf", (x+i));
    }

    printf("Enter values of y[]: ");
    for(int i=0; i<n; i++) {
        scanf("%lf", (y+i));
    }

    printf("Enter value of Scalar a: ");
    scanf("%lf", &a);

    // Creating the threads.
    pthread_t threads[THREAD_COUNT];

    for(int i=0; i<THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, daxpy, (int*) &i);
    }

    // Joining the created threads.
    for(int i=0; i<n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Resulting y[]:\n");
    for (i = 0; i < n; i++)
        printf("%lf ", y[i]);
    printf("\n");

    free(x);
    free(y);
    return 0;
}