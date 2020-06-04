#include <cstdio>
#include <vector>
#include <sys/epoll.h>
#include "tcpsocket.hpp"

#define MAX_TIMEOUT 3000
class Epoll
{
    public:
        Epoll():_epfd(-1){
            _epfd = epoll_create(1);
            if (_epfd < 0) {
                perror("epoll create error\n");
                exit(-1);
            }
        }
        bool Add(TcpSocket &sock) {
            //1. 获取TcpSocket对象的描述符
            int fd = sock.GetFd();
            //2. 为描述符定义事件结构体信息
            struct epoll_event ev;
            ev.events = EPOLLIN | EPOLLET;//EPOLLIN-可读事件；EPOLLET-边缘触发模式
            ev.data.fd = fd;
            //3. 添加监控
            int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev);
            if (ret < 0) {
                perror("epoll ctl add error");
                return false;
            }
            return true;
        }
        bool Del(TcpSocket &sock) {
            int fd = sock.GetFd();
            bool ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, NULL);
            if (ret < 0) {
                perror("epoll ctl del error");
                return false;
            }
            return true;
        }
        bool Wait(std::vector<TcpSocket> *list, int timeout = MAX_TIMEOUT) {
            //epoll_wait(epoll句柄， 事件数组，数组节点个数，超时时间)
            struct epoll_event evs[10];
            int nfds = epoll_wait(_epfd, evs, 10, timeout);
            if (nfds < 0) {
                perror("epoll wait error");
                return false;
            }else if (nfds == 0) {
                printf("timeout\n");
                list->clear();
                return true;
            }
            for (int i = 0; i < nfds; i++) {
                if (evs[i].events & EPOLLIN){//就绪了可读事件
                    TcpSocket sock;
                    sock.SetFd(evs[i].data.fd);
                    list->push_back(sock);
                }
            }
            return true;
        }
    private:
        int _epfd;//epoll的操作句柄
};
