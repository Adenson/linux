#include"tcpSocket.hpp"
#include<stdlib.h>
#include<stdio.h>
int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    printf("./tcp_src.cpp ip port\n");
    return 0;
  }

  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);

  TcpSocket lst_sock;
  CHECK_RET(lst_sock.Socket());
  CHECK_RET(lst_sock.Bind(ip,port));
  CHECK_RET(lst_sock.Listen());
  while(1){
    TcpSocket cli_sock;
    std::string cli_ip;
    uint16_t cli_port;
    if(lst_sock.Accept(&cli_sock,&cli_ip,&cli_port) == false)
    {
      continue;//不能直接返回，应为还有其他的客户端
    }
    //cli_sock用于与指定的客户端进行通信
    //lst_sock只用于获取新连接
    std::cout << "new connect:" << cli_ip << ":" << cli_port << std::endl;
    std::string buf;
    bool ret = cli_sock.Recv(buf);
    if(ret == false)
    {
      cli_sock.Close();
      continue;
    }
    std::cout << "clien say:" << buf << std::endl;
    std::cout << "server say:";
    fflush(stdout);
    buf.clear();
    std::cin >> buf;
    cli_sock.Send(buf);
    if(ret == false)
    {
      cli_sock.Close();
      continue; 
    }
  }
  lst_sock.Close();
  return 0;
}
