//命名管道的基本操作
//int mkfifo(const char *pathname,mode_t mode);
//pathname:管道文件路径名称   mode:管道文件的操作权限
//成功返回 0，失败返回 1

#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>//mkfifo的头文件
#include<errno.h>//errno的头文件
#include<fcntl.h>//O_RDONLY的头文件

int main()
{
   char *file = "./test.fifo";
   int ret = mkfifo(file,777);//创建一个管道文件
   if(ret < 0)
   {
      if(errno != EEXIST)
      {
	 perror("mkfifo error\n");
	 exit(-1);
      }
   }

   int fd = open(file,O_RDONLY);
   if(fd < 0)
   {
      perror("open error\n");
      exit(-1);
   }
   printf("open success\n");

   while(1)
   {
      char buf[1024] = {0};
      int ret = read(fd,buf,1023);
      if(ret == 0)
      {
	 printf("管道没有人写了，所有写端被关闭\n");
	 exit(-1);
      }
      else if(ret < 0)
      {
	 perror("read error\n");
	 exit(-1);
      }
      printf("%s\n",buf);
   }
   return 0;
}
