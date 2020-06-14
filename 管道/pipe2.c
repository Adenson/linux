//通过匿名管道实现管道符   
//ps -ef | grep ssh
//ps和grep进程是兄弟进程，ps进程将结果交给grep进程使用进程间通信（匿名管道）
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
int main()
{
   int pipefd[2]={0};
   int ret = pipe(pipefd);
   if(ret < 0)
   {
      perror("pipe error\n");
      exit(-1);
   }


   //pid1实现ps
   int pid1 = fork();
   if(pid1  == 0)
   {
      close(pipefd[0]);//管道哪一端不用就把哪一端关闭
      //将标准输出定位到管道的写入端
      dup2(pipefd[1],1);
      execlp("ps","ps","-ef",NULL);
      if(execlp < 0)
      {
	 perror("pid1 execlp error\n");
	 exit(-1);
      }
      exit(0);
   }
   else if(pid1 < 0)
   {
      perror("fork pid1 error\n");
      exit(-1);
   }

   
   //pid2实现grep
   int pid2 = fork();
   if(pid2 == 0)
   {
      close(pipefd[1]);
      //将标准输入定位到管道的读取端
      dup2(pipefd[0],0);
      execlp("grep","grep","ssh",NULL);
      //grep从管道中读数据进行过滤，不知道读多少，他就会一直读数据，如果管道中没有数据了，读就会阻塞，所以要关闭所有写端
      if(execlp < 0)
      {
	 perror("pid2 execlp error\n");
	 exit(-1);
      }
      exit(0);
   }
   else if(pid2 < 0)
   {
        perror("fork pid2 error\n");
        exit(-1);
    }
  

   close(pipefd[0]);
   close(pipefd[1]);
   waitpid(pid1,NULL,-1);
   waitpid(pid2,NULL,-1);
   return 0;
}
