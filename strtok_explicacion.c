#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 16

int thread_count;

sem_t *sems;

void* Tokenize(void* rank) 
{
	long my_rank = (long) rank;
	int count;
	int next = (my_rank + 1) % thread_count;
	char *fg_rv;
	char my_line[MAX];
	char *my_string;

	sem_wait(&sems[my_rank]);
	fg_rv = fgets(my_line, MAX, stdin);
	sem_post(&sems[next]);
	while (fg_rv != NULL) 
	{
		printf("Thread %ld > my_line = %s", my_rank, my_line);

		count = 0;
		my_string = strtok(my_line, " \t\n");
		//my_string = strtok_r(my_line, " \t\n", &saveptr);
		while ( my_string != NULL ) 
		{
			count++;
			printf("Thread %ld > string %d = %s\n", my_rank, count,my_string);
			my_string = strtok(NULL, " \t\n");
			//my_string = strtok_r(NULL, " \t\n", &saveptr);
		}
		sem_wait(&sems[my_rank]);
		fg_rv = fgets(my_line, MAX, stdin);
		sem_post(&sems[next]);
	}
	return NULL;
}


int main(int argc, char const *argv[])
{
	pthread_t *thread_handles;

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc (thread_count*sizeof(pthread_t));
	sems = malloc (thread_count*sizeof(sem_t));

	for (int i = 0; i < thread_count; ++i)
		sem_init(&sems[i], 0, 0);

	for (int i = 0; i < thread_count; ++i)
		pthread_create(&thread_handles[i], NULL, Tokenize, (void*) i);

	for (int i = 0; i < thread_count; ++i)
		pthread_join(thread_handles[i], NULL);


	free(thread_handles);

	return 0;
}