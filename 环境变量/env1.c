#include<stdio.h>
#include<stdlib.h>
//argc,程序运行参数的个数
//argv[],存放程序运行参数
int main(int argc,char *argv[],char *env[])//存放程序运行参数都是以NULL结尾的，argv[]和env[]都是
{
   int i = 0;
   for (i; i < argc; i++)
   {
      printf("argv[%d] = %s\n",i,argv[i]);
   }



   for(i = 0; env[i] != NULL ;i++)//存放程序运行参数是以NULL结尾的
   {
      printf("env[%d] = [%s]\n",i,env[i]);
   }


   /*extern char **environ;
   for(i = 0; environ[i] != NULL ;i++)
   {
      printf("environ[%d] = [%s]\n",i,environ[i]);
   }



   //char *getenv(const char *name)
   //通过环境变量名称获取内容
   char* ptr = getenv("MYSET");
   if(ptr == NULL)
   {
      printf("have no MYSET\n");
      return -1;
   } 
   printf("MYSET=%s\n",ptr);*/
   return 0;
} 
