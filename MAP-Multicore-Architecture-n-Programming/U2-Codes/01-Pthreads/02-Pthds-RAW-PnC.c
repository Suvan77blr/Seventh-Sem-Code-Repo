/*
    Pthreads program for basic version of Producer-Consumer code.

    1. This version uses a single-task flag (`task_available = 0/1`):
        - Only one task can be in the queue at a time.
        - Multiple producers/consumers or multiple tasks require a proper queue.

    2. Busy-waiting is used for simplicity:
        - Threads spin while waiting for the task flag to change.
        - Future improvement: replace with pthread_cond_t to sleep/wake threads.

    3. Thread termination / done() condition is user-defined in this code & it is just a placeholder.

    4. Focus here:
        - To understand the core logic of producer-consumer.
        - Learn mutex locking/unlocking and coordination.

    // TB Version.
*/

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t task_queue_lock;
int task_available;

// Producer Logic:
void *producer(void* producer_thread_data) 
{
    int inserted;
    struct task my_task;

    while( !done() ) {
        inserted = 0;
        create_task(&my_task);

        while( !inserted ) {
            pthread_mutex_lock( &task_queue_lock );

            if(!task_available)   // == 0
            {
                insert_into_queue( &my_task );
                task_available = inserted = 1;
            }

            pthread_mutex_unlock( &task_queue_lock );
        }
    }
    return NULL;
}

void *consumer(void* consumer_thread_data) 
{
    int extracted = 0;
    struct task my_task;

    while( !done() ) {
        extracted = 0;
        while( !extracted ) {
            pthread_mutex_lock( &task_queue_lock );

            if(task_available)  // == 1
            {
                extract_from_queue( &my_task );
                task_available = 0;
                extracted = 1;
            }
            pthread_mutex_unlock( &task_queue_lock );
        }

        process_task( &my_task );
    }
    return NULL;
}