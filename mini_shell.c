//（1）获取命令行
//（2）解析命令行
//（3）建立一个子进程（fork（））---让子进程背锅，如果替换自己的话运行完命令之后shell就退出了
//（4）替换子进程（execvp（））
//（5）父进程等待子进程退出（wait（））


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
int main()
{
   while(1)
   {
      printf("[wzf@localhost ~]$ ");
      fflush(stdout);
      char buf[100] = { 0 };
      fgets(buf,99,stdin);//从标准输入获取用户敲击的命令
      buf[strlen(buf)-1] = '\0';
      printf("cmd:[%s]\n",buf);


      int argc = 0;
      char *argv[100]={NULL};
      char *ptr = buf;
      while(*ptr != '\0')
      {
	 if(!isspace(*ptr))
	 {
	    argv[argc++] = ptr;
	    while(!isspace(*ptr) && *ptr != '\0')
	    {
	       ptr++;
	    }
	    *ptr = '\0';
	 }
	 ptr++;
      }

      argv[argc] = NULL;//这一步非常重要不能忘记写！！！
      
      int i = 0;
      for(i; i < argc; i++)
      {
	 printf("[%s]\n",argv[i]);
      }


     int pid = fork();
     if(pid == 0)
    {
       execvp(argv[0],argv);
       exit(-1);
    }
    waitpid(-1,NULL,0);

   }
   return 0;
}
