#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc,char *margv[],char *env[])
{
   //execl("/bin/ls","ls","-a","-l",NULL);//以空结尾

   //execlp("ls","ls","-a","-l",NULL);

   if(execle("./env1","ls","-a","-l",NULL,env) < 0)
   {
      perror("execle error");
      return -1;
   }
  

  /* char *argv[15] = {NULL};
   argv[0] = "ls";
   argv[1] = "-a";
   argv[2] = "-l";
   argv[3] = NULL;
   execv("/bin/ls",argv);*///得指定路径

   
  /* char *argv[15] = {NULL};
   argv[0] = "ls";
   argv[1] = "-a";
   argv[2] = "-l";
   argv[3] = NULL;
   execvp("ls",argv);//或者execvp("/bin/ls",argv)，带p之后系统的给不给路径都可以 */
  
   
  /* char *argv[15] = {NULL};
   argv[0] = "ls";
   argv[1] = "-a";
   argv[2] = "-l";
   argv[3] = NULL;
    // extern char **environ;//试了一下也可以
   if (execve("./env1",argv,env) < 0)
   {
      perror("execve error");
      return -1;
   }*/
 

   printf("hello world\n");//不会输出
   return 0;
}
