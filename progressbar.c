#include<stdio.h>
#include<unistd.h>
int main()
{
     char arr[11]={ 0 };
     int i = 0;
     for(;i<10;i++)
   {
	arr[i] = '-';
	//\n换行符，数据换行，针对标准输出的时候，还有刷新缓冲区
	//\r回车符，让光标移动到起始位置
	printf("%s\r",arr);
	fflush(stdout);//stdout：标准输出的文件流指针;
	sleep(1);
   }
 return 0;
}
