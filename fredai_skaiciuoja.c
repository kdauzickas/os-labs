#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#define THREADS 4

int Ego()
{
	int return_val;

	return_val = (int)pthread_self();

	return(return_val);
}

void *printme(void *arg)
{
	int ego = Ego();
	int i, fakt = 1;

	for (i = 1; i <= ego; i++) {
			fakt *= i;
	}
	printf("Hi.  I'm thread %d, faktorialas: %d\n", ego, fakt);
	return NULL;

}

int main()
{
	int i;
	int *vals;
	pthread_t *tid_array;
	void *retval;
	int err;

	vals = (int *)malloc(THREADS*sizeof(int));
	if(vals == NULL)
	{
		exit(1);
	}

	tid_array = (pthread_t *)malloc(THREADS*sizeof(pthread_t));
	if(tid_array == NULL)
	{
		exit(1);
	}

	for (i = 0; i < THREADS; i++)
	{
		err = pthread_create(&(tid_array[i]),
					 NULL,
					 printme,
					 NULL);

		if(err != 0)
		{
			fprintf(stderr,"thread %d ",i);
			perror("on create");
			exit(1);
		}

	}

	printf("main thread -- ");
  	printme(NULL);	/* main thread */


	for (i = 0; i < THREADS; i++)
	{
		printf("I'm %d Trying to join with thread %d\n", Ego(),(int)tid_array[i]);
		pthread_join(tid_array[i], &retval);
		printf("%d Joined with thread %d\n", Ego(),(int)tid_array[i]);
  	}

	free(tid_array);

	return(0);
}
