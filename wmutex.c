// This program helps to count up to 500000

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COUNT 500000
#define MAX_THREADS 12 /* number of threads */

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long long i = 0;

void * start_count (void *arg)
{

    for (; ;) // create infinite loop
	{

     if (i >= COUNT) // to check if maximum count is reached
	 {
		     return NULL;
	 }
	 i++;
	 printf ("i = %lld \n", i);
    }
}

 int main(void)
{

	int i = 0;
 // create a thread group as the size of MAX_THREADS
    pthread_t *thread_group = malloc(sizeof(pthread_t) * MAX_THREADS);
	// The threads start to work
	for (i=0; i<MAX_THREADS; i++)
	{
		pthread_create(&thread_group[i], NULL, start_count, NULL);
	}
	// Wating for the threads to terminate
	for (i=0; i<MAX_THREADS; i++)
	{
		pthread_join(thread_group[i], NULL);
	}
	return EXIT_SUCCESS;
}
