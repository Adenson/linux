#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define MAX_thread 5
int tickets = 100;
pthread_mutex_t mutex;

void* buyTickets(void *arg)
{
  while(1){
    pthread_mutex_lock(&mutex);//加锁
    if(tickets > 0)
    {
      usleep(1000);
      printf("%d---%d\n",pthread_self(),tickets);
      tickets--;
      pthread_mutex_unlock(&mutex);//解锁
    }
    else
    { 
      printf("have no tickets!!\n");
      //加锁之后，需要在任意有可能退出线程的地方都要进行解锁
      pthread_mutex_unlock(&mutex);//解锁
      pthread_exit(NULL);
    }
  }
  return NULL;
}

int main()
{
  pthread_t tid[MAX_thread];
  int i = 0;
  pthread_mutex_init(&mutex,NULL);//初始化
  for(i; i < MAX_thread; i++)
  {
    int ret = pthread_create(&tid[i],NULL,buyTickets,NULL);
    if(ret != 0)
    {
      perror("pthread_create error");
      return -1;
    }
  }
  for(i = 0; i < MAX_thread; i++)
  {
    pthread_join(tid[i],NULL);
  }
  pthread_mutex_destroy(&mutex);//销毁
  return 0;
}
