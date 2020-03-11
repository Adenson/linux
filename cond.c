//体会临界资源访问的时序合理性以及条件变量的基本使用

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
  
int noodles = 0;
pthread_cond_t cond_cooker;//定义一个cooker条件变量
pthread_cond_t cond_custmer;//定义一个custmer条件变量
pthread_mutex_t mutex;//定义一个互斥锁
void* custmer(void *arg)//顾客就餐
{
  while(1){
    pthread_mutex_lock(&mutex);
    while(noodles == 0)
    {
      pthread_cond_wait(&cond_custmer,&mutex);
    }
    printf("eat a bowl of noodles\n");
    noodles--;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond_cooker);
  }
  return NULL;
}

void* cooker(void *arg)//厨师做餐
{
  while(1){
    pthread_mutex_lock(&mutex);
    while(noodles == 1)
    {
      pthread_cond_wait(&cond_cooker,&mutex);
    }
    printf("cook a bowl of noodle\n");
    noodles++;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond_custmer);
    //sleep(0);
  }
  return NULL;
}

#define MAX_CUSTMER 4
int main()
{
  pthread_t custmer_tid,cooker_tid;
  pthread_cond_init(&cond_custmer,NULL);//初始化custmer条件变量
  pthread_cond_init(&cond_cooker,NULL);//初始化cooker条件变量
  pthread_mutex_init(&mutex,NULL);//初始化互斥锁
  int i = 0;
  int ret = 0;
  for(i; i < MAX_CUSTMER; i++)
  {
    ret = pthread_create(&custmer_tid,NULL,custmer,NULL);
    if(ret != 0)
    {
      perror("pthread_create custmer error");
      return -1;
    }
  }
  ret = pthread_create(&cooker_tid,NULL,cooker,NULL);
  if(ret != 0)
  {
    perror("pthread_t create cooker error");
    return -1;
  }
  pthread_join(custmer_tid,NULL);
  pthread_join(cooker_tid,NULL);
  pthread_cond_destroy(&cond_custmer);//销毁条件变量
  pthread_cond_destroy(&cond_cooker);//销毁条件变量
  pthread_mutex_destroy(&mutex);//销毁互斥锁
  return 0;
}
