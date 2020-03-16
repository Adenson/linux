#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX_THR 4
int tickets = 100;
sem_t sem;
void* buyTickets(void* arg)
{
  while(1)
  {
    sem_wait(&sem);
    if(tickets > 0){
      usleep(1000);
      printf("have bought a ticket---%d\n",tickets--);
      sem_post(&sem);
    }
    else{
      sem_post(&sem);//此处一定不要忘记
      pthread_exit(NULL);
    }
  }
  return NULL;
}
int main()
{
  pthread_t tid[MAX_THR];
  int i = 0;
  sem_init(&sem,0,1);
  for(i = 0; i < MAX_THR; i++)
  {
    int ret = pthread_create(&tid[i],NULL,buyTickets,NULL);
    if(ret != 0)
    {
      perror("pthread_create error");
      return -1;
    }
  }
  for(i = 0; i < MAX_THR; i++)
  {
    pthread_join(tid[i],NULL);
  }
}
