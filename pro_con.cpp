#include<iostream>
#include<queue>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#define MAX_NUM 10
class BlockQueue
{
private:
    std::queue<int> _queue;
    int _capacity;
    pthread_cond_t _cond_pro;
    pthread_cond_t _cond_con;
    pthread_mutex_t mutex;
public:
    BlockQueue(int que_Maxcapacity)
      :_capacity(que_Maxcapacity)
    {
      pthread_mutex_init(&mutex,NULL);
      pthread_cond_init(&_cond_pro,NULL);
      pthread_cond_init(&_cond_con,NULL);
    }

    ~BlockQueue()
    {
      pthread_mutex_destroy(&mutex);
      pthread_cond_destroy(&_cond_pro);
      pthread_cond_destroy(&_cond_con);
    }
    
    //提供给生产者的接口（数据入队）
    bool queuePush(int& data)
    {
      //queue是一个临界资源所以需要加锁保护
      pthread_mutex_lock(&mutex);
      //判断队列是否添加满了
      while(_queue.size() == _capacity)
      {
        pthread_cond_wait(&_cond_pro,&mutex);
      }
      _queue.push(data);
      pthread_mutex_unlock(&mutex);
      pthread_cond_signal(&_cond_con);
      return true;
    }
    //提供给消费者的接口（数据出队）
    bool queuePop(int& data)
    {
      pthread_mutex_lock(&mutex);
      //判断队列是否为空
      while(_queue.empty()){
        pthread_cond_wait(&_cond_con,&mutex);
      }
      data = _queue.front();
      _queue.pop();
      pthread_mutex_unlock(&mutex);
      pthread_cond_signal(&_cond_pro);
      return true;
    }
};
int pro = 0;
void* pro_thr(void* arg)
{
  BlockQueue* queue = (BlockQueue*)arg;
  while(1){
    queue->queuePush(pro);
    printf("pro_thr push %d\n",pro++);
  }
  return NULL;
}

void* con_thr(void* arg)
{
  sleep(100);
  BlockQueue* queue = (BlockQueue*)arg;
  while(1){
    int data;
    queue->queuePop(data);
    printf("con_thr get %d\n",data);
  }
  return NULL;
}

#define MAX_THR 5
int main()
{
  BlockQueue queue(MAX_NUM);
  pthread_t pro_tid[MAX_THR];
  pthread_t con_tid[MAX_THR];
  int i = 0;
  int ret = 0;

  for(i = 0 ; i < MAX_THR; i++)
  {
    pthread_create(&pro_tid[i],NULL,pro_thr,(void*)&queue);
    if(ret != 0)
    {
      std::cerr << "pthread_create pro_thr error\n";
      return -1;
    }
  }

  for(i = 0; i < MAX_THR; i++)
  {
    pthread_create(&con_tid[i],NULL,con_thr,(void*)&queue);
    if(ret != 0)
    {
      std::cerr << "pthread_create pro_thr error\n";
      return -1;
    }
  }

  for(i = 0; i < MAX_THR; i++)
  {
    pthread_join(pro_tid[i],NULL);
    pthread_join(con_tid[i],NULL);
  }
  return 0;
}
