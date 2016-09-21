#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define TAM 8000

int thread_count;

struct timeval t0, t1;
double media = 0.0;
double *times;

int A[TAM][TAM], x[TAM], y[TAM];

void llenar()
{
	srand(time(NULL));
	for (int i = 0; i < TAM; ++i)
	{
		x[i]=rand()%100;
		for (int j = 0; j < TAM; ++j)
		{
			A[i][j]=rand()%100;
			//printf("%d\t", A[i][j]);
		}
		//printf("|\t%d\n\n",x[i]);
	}
}

void printres()
{
	printf("Resultante: \n");
	for (int i = 0; i < TAM; ++i)
	{
		printf("%d\t", y[i]);
	}
	printf("\n");
}

void* Pth_mat_vect(void* rank) 
{
	long my_rank = (long) rank;
	int local_m = TAM/thread_count;
	int my_first_row = my_rank*local_m;
	int my_last_row = (my_rank+1)*local_m - 1;

	for (int i = my_first_row; i <= my_last_row; i++) 
	{
		y[i] = 0;
		for (int j = 0; j < TAM; j++)
			y[i] += A[i][j]*x[j];
	}

	gettimeofday(&t1, NULL);
	double ut1 = t1.tv_sec *1000000+ t1.tv_usec ;
	double ut0 = t0.tv_sec *1000000+ t0.tv_usec ;
	times[my_rank] = (ut1 -ut0 );

	return NULL;
}

int main(int argc, char const *argv[])
{
	llenar();

	pthread_t *thread_handles;

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc (thread_count*sizeof(pthread_t));
	times = malloc (thread_count*sizeof(double));

	for (int i = 0; i < thread_count; ++i)
		pthread_create(&thread_handles[i], NULL, Pth_mat_vect, (void*) i);
	
	for (int i = 0; i < thread_count; ++i)
	{
		gettimeofday(&t0 , NULL);
		pthread_join(thread_handles[i], NULL);
	}

	free(thread_handles);

	for (int i = 0; i < thread_count; ++i)
		media+=times[i];

	media=media/(double)thread_count;
	printf("Tiempo promedio con %d thread: %f\n",thread_count, media/100000.0);

	//printres();

	return 0;
}

//gcc -lpthread multiplicacion.c