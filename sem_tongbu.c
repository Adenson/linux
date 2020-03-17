#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t sem_cooker;
sem_t sem_diner;
void* cooker(void* arg)
{
  while(1){
    sem_wait(&sem_cooker);
    printf("cook a noole\n");
    sem_post(&sem_diner);
    sleep(1);
  }
  return NULL;
}
void* diner(void* arg)
{
  while(1){
    sem_wait(&sem_diner);
    printf("eat a noodle\n");
    sem_post(&sem_cooker);
  }
  return NULL;
}
int main()
{
  sem_init(&sem_cooker,0,1);
  sem_init(&sem_diner,0,0);
  pthread_t cooker_tid;
  pthread_t diner_tid;
  int ret = 0;
  ret = pthread_create(&cooker_tid,NULL,cooker,NULL);
  if(ret != 0){
    perror("pthred_create cooker error");
    return -1;
  }
  ret = pthread_create(&diner_tid,NULL,diner,NULL);
  {
    if(ret != 0)
    {
      perror("pthread_create diner error");
      return -1;
    }
  }
  pthread_join(cooker_tid,NULL);
  pthread_join(diner_tid,NULL);
  sem_destroy(&sem_cooker);
  sem_destroy(&sem_diner);
  return 0;
}
