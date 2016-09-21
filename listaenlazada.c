#include <stdlib.h>
#include <stdio.h>
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

int  Member(int value, struct list_node_s* head_p) 
{
   struct list_node_s* curr_p;

   curr_p = head_p;
   while (curr_p != NULL && curr_p->data < value)
      curr_p = curr_p->next;

   if (curr_p == NULL || curr_p->data > value) 
   {
      printf("%d is not in the list\n", value);
      return 0;
   } 
   else 
   {
      printf("%d is in the list\n", value);
      return 1;
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


/*struct list_node_s 
{
	int data;
	struct list_node_s* next;
	pthread_mutex_t mutex;
}

int Member(int value) 
{
	struct list_node_s* temp_p;
	
	pthread_mutex_lock(&head_p_mutex);
	temp_p = head_p;

	while (temp_p != NULL && temp_p ->data < value) 
	{
		if (temp_p ->next != NULL)
			pthread_mutex_lock(&(temp_p ->next ->mutex));
		if (temp_p == head_p)
			pthread_mutex_unlock(&head_p_mutex);
		pthread_mutex_unlock(&(temp_p ->mutex));
		temp_p = temp_p ->next;
	}

	if (temp_p == NULL || temp_p ->data > value) 
	{
		if (temp_p == head_p)
			pthread_mutex_unlock(&head_p_mutex);
		if (temp_p != NULL)
			pthread_mutex_unlock(&(temp_p ->mutex));
		return 0;
	} 
	else 
	{
		if (temp_p == head_p)
			pthread_mutex_unlock(&head_p_mutex);
		pthread_mutex_unlock(&(temp_p ->mutex));
		return 1;
	}
}*/


int main(int argc, char const *argv[])
{
	/*pthread_t *thread_handles;

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc (thread_count*sizeof(pthread_t));

	for (int i = 0; i < thread_count; ++i)
		pthread_create(&thread_handles[i], NULL, Pth_mat_vect, (void*) i);
	
	for (int i = 0; i < thread_count; ++i)
		pthread_join(thread_handles[i], NULL);

	free(thread_handles);*/

	struct list_node_s* lista=NULL;

	Insert(10,&lista);
	Insert(2,&lista);


	return 0;
}