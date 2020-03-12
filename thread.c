#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
void* print(void* arg)
{
  //情况1，通过return终止
  //int *p = (int*)malloc(sizeof(int));
  //*p = 2;
  //return (void*)p;
  
  //情况2，通过pthread_exit();终止
  //printf("this is a child thread\n");
  //char *ptr = "hello world";
  //pthread_exit(ptr);
  
  //情况3，通过pthrea_cancel();终止。在主线程里调用退出
  while(1)
  { 
     printf("this is a child thread\n");
     sleep(1);
  }
  return NULL;
}

int main()
{
  pthread_t tid;
  char *ptr = "hello world";
  int ret = pthread_create(&tid,NULL,print,(void*)ptr);
  if(ret != 0)
  {
    perror("pthread_create error");
    return 0;
  }
  //情况1
  //int* p;
  //pthread_join(tid,(void**)&p);
  //printf("retval:%d\n",*p);
  
  //情况2
  //char *p;
  //pthread_join(tid,(void**)&p);
  //printf("retval:%s\n",p);
  
  //情况3,，通过pthrea_cancel();终止。
  void *p;
  pthread_cancel(tid);
  pthread_join(tid,(void**)&p);
  if(p == PTHREAD_CANCELED)
  {
    printf("retval:%s\n","PTHREAD_CANCELED");
  }

  while(1)
  {
    printf("this is main thread---%d\n",tid);
    sleep(1);
  }
  return 0;
}
