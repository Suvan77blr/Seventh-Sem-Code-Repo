/*
    Pthreads Program to compute PI using Monte-Carlo estimation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthreads.h>

#define MAX_THREADS 512
#define TOTAL_POINTS 1000000

void* compute_pi(void *);
int hits[MAX_THREADS];
// ...

int main(void) {
    // ...

    pthread_t threads[MAX_THREADS];
    int ids[MAX_THREADS];
    double pi_estimate = 0.0;
    int total_hits = 0;
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // Creation of the threads.
    for(int i=0; i<MAX_THREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], &attr, compute_pi, (void*)&ids[i]);
    }

    // Waiting and Joining the threads.
    for(int i=0; i<MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_hits += hits[i];
    }

    pi_estimate = 4.0 * total_hits / TOTAL_POINTS;
    printf("Estimated PI value: %.9f\n", pi_estimate);

    return 0;
}

void* compute_pi(void *args) {
    int thread_id = *( (int*)args );
    int local_hits = 0;

    unsigned int seed = thread_id + 1;

    int points_per_th = TOTAL_POINTS / MAX_THREADS;

    // Assigning leftover points to thread 0 to account for TOTAL_POINTS not divisible by MAX_THREADS
    if (thread_id == 0)
        points_per_th += TOTAL_POINTS % MAX_THREADS;

    for(int i=0; i<points_per_th; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;

        if(( (x-0.5)*(x-0.5) + (y-0.5)*(y-0.5) ) < 0.25) {
            local_hits++;
        }
    }

    hits[thread_id] = local_hits;
    pthread_exit(NULL);
}