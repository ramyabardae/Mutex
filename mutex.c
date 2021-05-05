#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define COUNT  500000
#define MAX_THREADS 12 /* number of threads */

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long long i = 0;

void *start_count(void *arg) {
    for (;;) {
        // To start mutex lock and acquire it 
        pthread_mutex_lock(&mutex);
        /* critical section of the code */
		
		
        // To check if maximum count is reached
        if (i >= COUNT) {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }

        ++i;
        /* Critical secion ends */
		
		
		
        // release the mutex lock
        pthread_mutex_unlock(&mutex);

        printf("i = %lld\n", i);
    }
}

int main(void) {
    int i = 0;

    // create a thread group as the size of MAX_THREADS
    pthread_t *thread_group = malloc(sizeof(pthread_t) * MAX_THREADS);

    // The threads start to work
    for (i = 0; i < MAX_THREADS; ++i) {
        pthread_create(&thread_group[i], NULL, start_count, NULL);
    }

    // Waiting for the threads to terminate
    for (i = 0; i < MAX_THREADS; ++i) {
        pthread_join(thread_group[i], NULL);
    }

    return EXIT_SUCCESS;
}