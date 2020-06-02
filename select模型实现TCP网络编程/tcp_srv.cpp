#include "tcpsocket.hpp"
#include "select.hpp"

int main(int argc, char *argv[])
{
    TcpSocket lst_sock;

    CHECK_RET(lst_sock.Socket());
    CHECK_RET(lst_sock.Bind("0.0.0.0", 9000));
    CHECK_RET(lst_sock.Listen());

    Select s;
    s.Add(lst_sock);
    while(1) {
        std::vector<TcpSocket> list;
        bool ret = s.Wait(&list);
        if (ret == false) {
            continue;
        }
        //有描述就绪了，Select返回就绪的套接字列表
        for (auto sock : list) {
            //判断就绪的套接字是哪一种套接字
            //若就绪的套接字是监听套接字,则获取新连接
            if (sock.GetFd() == lst_sock.GetFd()) {
                TcpSocket cli_sock;
                bool ret = lst_sock.Accept(&cli_sock);
                if (ret == false) {
                    continue;
                }
                s.Add(cli_sock);
            }else {//反之，若就绪的套接字是通信套接字则进行正常通信
                std::string buf;
                ret = sock.Recv(buf);
                if (ret == false) {
                    sock.Close();
                    //将不再监控的描述符从集合中移除
                    s.Del(sock);
                    continue;
                }
                std::cout << "client say: " << buf << std::endl;
                buf.clear();
                printf("server say:");
                fflush(stdout);
                std::cin >> buf;
                sock.Send(buf);
                if (ret == false) {
                    sock.Close();
                    s.Del(sock);
                }
            }
        }
    }
    lst_sock.Close();
    return 0;
}
