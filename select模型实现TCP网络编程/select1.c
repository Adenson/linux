/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：通过简单的对标准输入进行监控，来体会select的基本使用 
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>


int main()
{
    fd_set rfds;
    while(1) {
        struct timeval tv;
        tv.tv_sec = 3;
        tv.tv_usec = 0;
        FD_ZERO(&rfds);//清空监控集合
        FD_SET(0, &rfds);//将标准输入描述符添加到集合中
        int maxfd = 1;
        int ret = select(maxfd + 1, &rfds, NULL, NULL, &tv);
        if (ret < 0) {
            perror("select error");
            continue;
        }else if (ret == 0) {
            printf("select timeout\n");
            continue;
        }
        for (int i = 0; i < maxfd+1; i++) {
            if (FD_ISSET(i, &rfds)) {
                char buf[1024] = {0};
                read(i, buf, 1023);
                printf("buf:[%s]\n", buf);
            }
        }
    }
    return 0;
}
