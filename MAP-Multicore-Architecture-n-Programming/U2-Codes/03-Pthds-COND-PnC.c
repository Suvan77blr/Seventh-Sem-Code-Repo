// Producer-Consumer Code using Condition-Variables.
// TB-Version.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t task_q_lock;
pthread_cond_t task_q_full, task_q_empty;
int task_available;

void *producer(void* producer_thread_data) {
    while( !done() )
    {
        struct task my_task = create_task();

        pthread_mutex_lock(&task_q_lock);
        while(task_available) {
            pthread_cond_wait(&task_q_empty, &task_q_lock);
        }
        
        insert_into_queue(&my_task);
        task_available = 1;
        
        pthread_cond_signal(&task_q_full);
        pthread_mutex_unlock(&task_q_lock);
    }
    return NULL;
}

void *consumer(void* consumer_thread_data) {
    while( !done() ) 
    {
        pthread_mutex_lock(&task_q_lock);

        while( !task_available ) {
            pthread_cond_wait(&task_q_full, &task_q_lock);
        }

        struct task my_task = extract_from_queue();
        task_available = 0;

        pthread_cond_signal(&task_q_empty);
        pthread_mutex_unlock(&task_q_lock);

        process_task(my_task);
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    task_available = 0;
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    pthread_create(&pTh, &attr, producer, NULL);
    pthread_create(&cTh, &attr, consumer, NULL);

    pthread_cond_init(&task_q_empty, NULL);
    pthread_cond_init(&task_q_full, NULL);
    pthread_mutex_init(&task_q_lock, NULL);

    /* ... */

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&task_q_lock);
    pthread_cond_destroy(&task_q_empty);
    pthread_cond_destroy(&task_q_full);

    return 0;
}