//体会共享内存的基本操作
//int shmget(key_t, size_t size, int shmflg)
//功能：创建共享内存

//key:共享内存在内核中的标识，其他进程通过相同的标识打开同一个内存
//key值可以自己设置，也有一种计算方式:key_t ftok(const char *pthname,int proj_id)
//因为ftok返回值是key_t


//size:共享内存大小
//shmflg:IPC_CREAT|IPC_EXCL|mode    IPC_CREAT:如果这个共享内存不存在则创建它    IPC_EXCL：若不存在则创建，存在则报错    mode:权限设置
//返回值：成功返回共享内存对的句柄，失败返回-1


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/ipc.h>

#define IPC_KEY 0x99999999
#define SHM_SIZE 4096
int main()
{
   //创建共享内存——————其中的 shmid 是操作句柄
   int shmid = shmget(IPC_KEY,SHM_SIZE,IPC_CREAT|0444);
   if(shmid < 0)
   {
      perror("shmget error");
      exit(-1);
   }

   //建立映射
   void *shm_start = shmat(shmid,NULL,0);// 0是任何操作
   if(shm_start == (void*)-1)
   {
      perror("shamet error");
      exit(-1);
   }

   int i = 0;
   while(1)
   {
      printf("%s",(char*)shm_start);
      sleep(1);
   }

   //解除映射关系
   shmdt(shm_start);

   shmctl(shmid,IPC_RMID,NULL);

   return 0;
}
