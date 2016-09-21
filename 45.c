#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct list_node_s {
   int    data;
   struct list_node_s* next;
};

int Insert(int value, struct list_node_s** head_pp) 
{
   struct list_node_s* curr_p = *head_pp;
   struct list_node_s* pred_p = NULL;
   struct list_node_s* temp_p;
   
   while (curr_p != NULL && curr_p->data < value) 
   {
      pred_p = curr_p;
      curr_p = curr_p->next;
   }

   if (curr_p == NULL || curr_p->data > value) 
   {
      temp_p = malloc(sizeof(struct list_node_s));
      temp_p->data = value;
      temp_p->next = curr_p;
      if (pred_p == NULL)
         *head_pp = temp_p;
      else
         pred_p->next = temp_p;
      return 1;
   } 
   else 
   { 
      printf("%d is already in the list\n", value);
      return 0;
   }
}   

int Delete(int value, struct list_node_s** head_pp) {
   struct list_node_s* curr_p = *head_pp;
   struct list_node_s* pred_p = NULL;

   while (curr_p != NULL && curr_p->data < value) {
      pred_p = curr_p;
      curr_p = curr_p->next;
   }
   
   if (curr_p != NULL && curr_p->data == value) {
      if (pred_p == NULL) 
      { 
         *head_pp = curr_p->next;
         free(curr_p);
      } 
      else 
      { 
         pred_p->next = curr_p->next;
         free(curr_p);
      }
      return 1;
   } 
   else 
      return 0;
}  

struct list_node_s* lista = NULL;
sem_t *sems;

void* fun(void *rank)
{
	long my_rank = (long) rank;
	if(my_rank==0)
	{
		for (int i = 0; i < 1000; ++i)
		{
			Insert(i,&lista);
			int dest=(i%(thread_count-1))+1;
			sem_post(&sem[dest]);
			sem_wait(&sem[0]);
		}
	}
	else
	{
		while(1)
		{
			sem_wait(&sem[my_rank]); //bloqueo
			Delete(lista->data,&lista);
			sem_post(&sem[0]); //desbloqueo
		}
	}
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
		pthread_create(&thread_handles[i], NULL, fun, (void*) i);

	for (int i = 0; i < thread_count; ++i)
		pthread_join(thread_handles[i], NULL);

	free(thread_handles);
	

	return 0;
}