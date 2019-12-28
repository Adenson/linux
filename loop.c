#include<stdio.h>
#include<unistd.h>
#include<stdint.h>
#include<errno.h>
#include<string.h>
int main()
{
   int i = 0;
   for( i =0;i<256;i++)
   {
      printf("errmsg:[%s]\n",strerror(i));//头文件#include<string.h>,打印错误信息
   }

   if (fork() < 0)
   {
      //打印上次系统调用接口所出现的错误信息。头文件#include<errno.h>
      perror("fork error\n");
      return 0;
   }

   int x = 0;
   if(x == 0)
   {
      return -2;
   }
   else
   {
      return 256;
   }


   long long c  = 0;
   while(1)
   {
      c++;
   }
   return 0;
 } 

