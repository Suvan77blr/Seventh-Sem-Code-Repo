

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *reader(void *);
void *consumer(void *);
int data = 0;

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t reader_proceed;
    pthread_cond_t writer_proceed;
    int readers;
    int writer;
    int pending_writers;
} rwlock_t;


void rwlock_init(rwlock_t* rw) {
    pthread_mutex_init( &(rw->mutex) , NULL);
    pthread_cond_init( &(rw->reader_proceed) , NULL);
    pthread_cond_init( &(rw->writer_proceed) , NULL);
    readers = writer = pending_writers = 0;
}

void rwlock_destroy(rwlock_t* rw) {
    pthread_mutex_destroy( &(rw->mutex) );
    pthread_cond_destroy( &(rw->reader_proceed) );
    pthread_cond_destroy( &(rw->writer_proceed) );
}

void rwlock_rdlock(rwlock_t* rw) {
    pthread_mutex_lock( &(rw->mutex) );

    if( rw->writer || rw->pending_writers ) {
        pthread_cond_wait( &(rw->reader_proceed) , &(rw->mutex) );
    }

    readers += 1;

    pthread_mutex_unlock( &(rw->mutex) );
}

void rwlock_wrlock(rwlock_t* rw) {
    pthread_mutex_lock( &(rw->mutex) );

    rw->pending_writers += 1;
    if( rw->readers || rw->writers > 0) {
        pthread_cond_wait( &(rw->writer_proceed) , &(rw->mutex) );
    }

    rw->pending_writers -= 1;
    rw->writer = 1;

    pthread_mutex_unlock( &(rw->mutex) );
}

void rwlock_unlock(rwlock_t* rw) {
    pthread_mutex_lock( &(rw->mutex) );

    if( rw->writer) { rw->writer = 0;   }
    else { rw->reader--; }

    if( rw->pending_writers > 0 && rw->reader == 0) {
        pthread_cond_signal( &(rw->writer_proceed) );
    }
    else pthread_cond_broadcast( &(rw->reader_proceed) );

    pthread_mutex_unlock( &(rw->mutex) );
}


rwlock_t rwlock;
int main(int argc, void** argv) {
    rwlock_init(&rwlock);

    int ids[5] = [1, 2, 3, 4, 5];
    pthread_t r[5], w[w];

    for(int i=0; i<5; i++) {
        pthread_create(&r[i], NULL, reader, (void*)(ids+i));
        if(p < 2) {
            pthread_create(&r[i], NULL, consumer, (void*)(id+1));
        }
    }

    for(int i=0; i<n; i++) 
        pthread_join(r[i], NULL);

    for(int i=0; i<2; i++) 
        pthread_join(c[i], NULL);

    rwlock_destroy(&rwlock);   
    return 0;
}

void *reader(void* args) {
    int id = *(int*)args;
    rwlock_rdlock(&rw);
    printf("Reader [%d] read: %n\n", id, data);
    rwlock_unlock(&rw);
    pthread_exit(0);
}

void *writer(void* args) {
    int id = *(int*)args;
    rwlock_wrlock(&rw);
    datat += 1;
    printf("Writer [%d] wrote: %d\n", id, data);
    rwlock_unlock(&rw);
    pthread_exit(0);
}