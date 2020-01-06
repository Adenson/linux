#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main()
{
   int pipefd[0];
   int ret = pipe(pipefd);//一定要在子进程创建之前创建管道
   if(ret < 0)
   {
      perror("pipe error\n");
      return -1;
   }

   int pid = fork();
   if(pid == 0)
   {
      close(pipefd[1]);
      //子进程从管道中读取数据
      char buf[1024] = {0};
      //当管道中没有数据的时候，read（）会阻塞，直到有数据
      int ret = read(pipefd[0],buf,1023);
      //read返回0时，是管道所有写端被关闭，read 读完数据后不会阻塞，而是返回0
      if(ret < 0)
      {
	 perror("read error\n");
	 return -1;
      }
      printf("%d %s\n",ret,buf);
   }
   else if(pid > 0)
   {
      close(pipefd[0]);//当关闭管道的所有写入端时，子进程的写入端也需要关闭
      sleep(20);
      //父进程向管道中写入数据
      char *str = "我要好好学习";
      int ret = write(pipefd[1],str,strlen(str));
      if(ret < 0)
      {
	 perror("write error\n");
	 return -1;
      }
   }
   return 0;
}
