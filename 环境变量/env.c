#include<stdio.h>
#include<stdlib.h>
int main()
{
   //char *getenv(const char *name)
   //通过环境变量名称然后获取内容
   char* ptr = getenv("MYSET");
   if(ptr == NULL)
   {
      printf("have no MYSET\n");
      return -1;
   } 
   printf("MYSET=%s\n",ptr);
   return 0;
}


//argc ，程序运行参数的个数
//argv[],存放程序运行参数
int main(int argc,char *argv[])
{
   int i = 0;
   for (i; i < argc; i++)
   {
      printf("argv[%d] = %s\n",i,argv[i]);
   }

   //char *getenv(const char *name)
   //通过环境变量名称获取内容
   char* ptr = getenv("MYSET");
   if(ptr == NULL)
   {
      printf("have no MYSET\n");
      return -1;
   } 
   printf("MYSET=%s\n",ptr);
   return 0;
}


int main(int argc,char *argv[],char *env[])
{
   int i = 0;
   for (i; i < argc; i++)
   {
      printf("argv[%d] = %s\n",i,argv[i]);
   }



   for(i = 0; env[i] != NULL ;i++)
   {
      printf("env[%d] = [%s]\n",i,env[i]);
   }



   //char *getenv(const char *name)
   //通过环境变量名称获取内容
   char* ptr = getenv("MYSET");
   if(ptr == NULL)
   {
      printf("have no MYSET\n");
      return -1;
   } 
   printf("MYSET=%s\n",ptr);
   return 0;
} 
