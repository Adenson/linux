#include <cstdio>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <sys/select.h>
#include "tcpsocket.hpp"

class Select 
{
    public:
        Select() : _maxfd(-1){
            FD_ZERO(&_rfds);
        }
        bool Add(TcpSocket &sock) {
            int fd = sock.GetFd();
            FD_SET(fd, &_rfds);
            _maxfd = _maxfd > fd ? _maxfd : fd;
            return true;
        }
        bool Del(TcpSocket &sock) {
            int fd = sock.GetFd();
            FD_CLR(fd, &_rfds);
            for (int i = _maxfd ; i >= 0; i--) {
                if (FD_ISSET(i, &_rfds)) {
                    _maxfd = i;
                    break;
                }
            }
            return true;
        }
        //向用户返回就绪的套接字，让用户可以直接操作
        bool Wait(std::vector<TcpSocket> *list, int time_sec = 3) {
            struct timeval tv;
            tv.tv_sec = time_sec;
            tv.tv_usec = 0;
            fd_set set = _rfds;//防止修改_rfds
            int ret = select(_maxfd+1, &set, NULL, NULL, &tv);
            if (ret < 0) {
                perror("select error");
                return false;
            }else if (ret == 0) {
                printf("select timeout\n");
                return false;
            }
            for (int i = 0; i < _maxfd+1; i++) {
                if (FD_ISSET(i, &set)) {
                    TcpSocket sock;
                    sock.SetFd(i);
                    list->push_back(sock);
                }
            }
            return true;
        }
    private:
        fd_set _rfds;//原始可读事件监控集合,做一个所有描述符备份
        int _maxfd;
};


