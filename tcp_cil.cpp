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
  
  TcpSocket cli_sock;
  CHECK_RET(cli_sock.Socket());
  CHECK_RET(cli_sock.Connect(ip,port));

  while(1){
    std::cout << "client say:";
    fflush(stdout);
    std::string buf;
    std::cin >> buf;
    CHECK_RET(cli_sock.Recv(buf));

    buf.clear();
    CHECK_RET(cli_sock.Recv(buf));
    std::cout << "server say:" << buf << std::endl;
  }
  cli_sock.Close();
  return 0;
}
