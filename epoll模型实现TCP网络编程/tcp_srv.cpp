#include <iostream>
#include <string>
#include <vector>
#include "epoll.hpp"

int main (int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "Usage: ./tcp_srv ip port\n";
        return -1;
    }
    std::string ip = argv[1];
    uint16_t port = std::stoi(argv[2]);

    TcpSocket lst_sock;
    CHECK_RET(lst_sock.SetNonBlock());
    CHECK_RET(lst_sock.Socket());
    CHECK_RET(lst_sock.Bind(ip, port));
    CHECK_RET(lst_sock.Listen());

    Epoll epoll;
    epoll.Add(lst_sock);
    while(1) {
        std::vector<TcpSocket> list;
        bool ret = epoll.Wait(&list);
        if (ret == false) {continue;}
        for (auto sock : list) {
            if (sock.GetFd() == lst_sock.GetFd()) {//监听套接字的就绪事件
                TcpSocket new_sock;
                bool ret = lst_sock.Accept(&new_sock);
                if (ret == false) { continue;}
                new_sock.SetNonBlock();
                epoll.Add(new_sock);
            }else {
                std::string buf;
                ret = sock.Recv(&buf);
                if (ret == false) {
                    sock.Close();
                    epoll.Del(sock);
                    continue;
                }
                std::cout << "client say: " << buf << std::endl;
                buf.clear();
                std::cout << "server say: ";
                std::cin >> buf;
                ret = sock.Send(buf);
                if (ret == false) {
                    sock.Close();
                    epoll.Del(sock);
                }
            }
        }
    }
    lst_sock.Close();
    return 0;
}
