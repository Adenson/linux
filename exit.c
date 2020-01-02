#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
   printf("hello world");//加上\n也会刷新缓冲区
   sleep(3);

   _exit(0);//退出时候直接释放所有资源，不会刷新缓冲区----系统调用接口与
   exit(0);//退出前会刷新缓冲区---库函数接口
   return 0;//退出前会刷新缓冲区
}

