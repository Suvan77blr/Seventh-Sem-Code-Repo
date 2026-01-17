/*
    Pthreads Program to simulate Barrier-Synchronization.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 4

typedef struct {
    int count;
    int num_threads;
    pthread_cond_t ok_to_proceed;
    pthread_mutex_t mutex;
    // int generation;  // NOTE: Add for robust barrier to handle spurious wakeups
} my_barrier_t;

void my_barrier(my_barrier_t* b) {
    pthread_mutex_lock( &(b->mutex) );
    
    b->count++;         // Increases the number of threads at the barrier.
    if( b-> count == b->num_threads) {
        b->count = 0;
        pthread_cond_broadcast( &(b->ok_to_proceed) );
    }
    else {
        while( b->count != 0) {
            pthread_cond_wait( &(b->ok_to_proceed), &(b->mutex));
        }
    }

    pthread_mutex_unlock( &(b->mutex) );

    // NOTE: For future upgrade, add a `generation` counter to handle spurious wakeups
    //       and ensure barrier works correctly if reused quickly by threads.
}

void my_barrier_init(my_barrier_t* b) {
    b->count = 0;
    b->num_threads = NUM_THREADS;
    pthread_cond_init( &(b->ok_to_proceed), NULL);
    pthread_mutex_init( &(b->mutex), NULL);
}

void my_barrier_destroy(my_barrier_t* b) {
    pthread_cond_destroy( &(b->ok_to_proceed) );
    pthread_mutex_destroy( &(b->mutex) );
}

// BigBro given filler code:
my_barrier_t barrier;

void* thread_func(void *arg) {
    int tid = *(int*)arg;

    printf("Thread %d: Step 1\n", tid);
    sleep(1);   // Simulating thread-work.

    my_barrier(&barrier);
    printf("Thread %d: Passed barrier 1\n", tid);

    sleep(1);   // more work.

    my_barrier(&barrier);   // Barrier is re-used.
    printf("Thread %d: Passed barrier 2\n", tid);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    my_barrier_init(&barrier);

    for(int i=0; i<NUM_THREADS; i++) {
        ids[i] = i+1;
        pthread_create( &threads[i], &NULL, thread_func, (void*)&ids[i]);
    }

    for(int i=0; i<NUM_THREADS; i++) {
        pthread_join( threads[i], NULL);
    }

    my_barrier_destroy(&barrier);
    return 0;
}