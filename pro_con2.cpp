#include<iostream>
#include<stdio.h>
#include<vector>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX_QUE 10

class RingQueue
{
  private:
    std::vector<int> _queue;//使用数组实现环形队列
    int _capacity;//初始化环形队列的结点数量
    int _step_read;//当前读位置的数组下标
    int _step_write;//当前写位置的数组下标
    sem_t _sem_lock;//用于实现互斥的锁
    sem_t _sem_con;//消费者等待队列，计数器对有数据的空间进行计数
    sem_t _sem_pro;//生产者等待队列，计数器对空闲的空间进行计数
  public:
    RingQueue(int max_que = MAX_QUE)
      :_capacity(max_que)
      ,_queue(max_que)
      ,_step_read(0)
      ,_step_write(0)
    {
      sem_init(&_sem_lock,0,1);
      sem_init(&_sem_con,0,0);
      sem_init(&_sem_pro,0,max_que);
    }

    ~RingQueue()
    {
      sem_destroy(&_sem_lock);
      sem_destroy(&_sem_con);
      sem_destroy(&_sem_pro);
    }
    
    bool QueuePush(int &data)
    {
      //1、判断是否能够访问临界资源，判断空闲空间计数是否大于0
      sem_wait(&_sem_pro);
      //2、加锁
      sem_wait(&_sem_lock);
      //3、数据的入队操作
      _queue[_step_write] = data;
      _step_write = (_step_write + 1) % _capacity;
      //4、解锁
      sem_post(&_sem_lock);
      //5、数据资源的空间计数+1，唤醒消费者
      sem_post(&_sem_con);
      return true;
    }

    bool QueuePop(int &data)
    {
      sem_wait(&_sem_con);
      sem_wait(&_sem_lock);
      data = _queue[_step_read];
      _step_read = (_step_read + 1) % _capacity;
      sem_post(&_sem_lock);
      sem_post(&_sem_pro);
      return true;
    }
};
void *productor(void* arg)
{
  RingQueue* queue = (RingQueue*)arg;
  int data = 0;
  while(1){
    queue->QueuePush(data);
    printf("productor push a data : %d\n",data++);
  }
  return NULL;
}
void *consumer(void* arg)
{
  RingQueue* queue = (RingQueue*)arg;
  while(1){  
    int data = 0;
    queue->QueuePop(data);
    printf("consumer get a data : %d\n",data);
  }
  return NULL;
}
#define MAX_THR 4
int main()
{
  pthread_t ctid[MAX_THR];
  pthread_t ptid[MAX_THR];
  RingQueue queue;
  int i = 0;
  int ret = 0;
  for(i = 0; i < MAX_THR; i++)
  {
    ret = pthread_create(&ptid[i],NULL,consumer,(void*)&queue);
    if (ret != 0)
    {
      std::cerr << "pthread_create consumer error\n";
      return -1;
    }
  }
  for(i = 0; i < MAX_THR; i++)
  {
    ret = pthread_create(&ctid[i],NULL,productor,(void*)&queue);
    if (ret != 0)
    {
      std::cerr << "pthread_create productor error\n";
      return -1;
    }
  }
  for(i = 0 ; i < MAX_THR; i++)
  {
    pthread_join(ptid[i],NULL);
    pthread_join(ctid[i],NULL);
  }
  return 0;
}
