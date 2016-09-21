#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int thread_count;
struct timeval t0, t1;
double media = 0.0;
double *times;


void *funcion(void *rank) 
{
	gettimeofday(&t1, NULL);
	double ut1 = t1.tv_sec *1000000+ t1.tv_usec ;
	double ut0 = t0.tv_sec *1000000+ t0.tv_usec ;
	long my_rank = (long) rank;
	times[my_rank] = (ut1 -ut0 );
}

int main(int argc, char const *argv[])
{
	pthread_t *thread_handles;

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc (thread_count*sizeof(pthread_t));
	times = malloc (thread_count*sizeof(double));


	for (int i = 0; i < thread_count; ++i)
	{
		gettimeofday(&t0 , NULL);
		pthread_create(&thread_handles[i], NULL, funcion, (void*) i);
		pthread_join(thread_handles[i], NULL);
	}
	free(thread_handles);

	for (int i = 0; i < thread_count; ++i)
		media+=times[i];

	media=media/(double)thread_count;
	printf("Tiempo promedio: %f\n", media/1000.0);

	return 0;
}