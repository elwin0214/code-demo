#include "sockets.cpp"
#include <stdio.h>
#include <string>
#include <thread>
#include <functional>

using namespace std;

/*
udp 
对一个fd，使用dup后分发给多个线程 recvfrom ，不会同时被多个线程读取，猜测按包来分发。
因为memcached UDP 协议是这样处理的，所以写了类似的程序验证，不确认如果一个数据包应用层拆包后，由UDP分发后怎么处理。

本质上理解：
1、UDP是有边界的，你可以简单的认为他的单位是“个”。
2、UDP包大小有上限，即64K。（MTU会根据情况进行分包，但你不用管这些）
3、当你提供的接收Buf小于实际包大小时，你会收到WSAEMSGSIZE。意思就是说，你提供的容器太小，只能装下部分数据，装不下的那部分已经被扔掉了。

所以，申请个大点儿的Buffer，传递给recvfrom函数就好了。

*/
struct UDPServer
{
  int fd_;
  struct sockaddr_in addr_;

  UDPServer(const char* ip, int port)
  {

    sockets::setAddr(addr_, ip, port);
    fd_ = sockets::createUdpFd();

    fprintf(stdout, "server fd-%d\n", fd_);
    sockets::setReuseAddr(fd_);
    sockets::bind(fd_, addr_);
  }

  void start()
  {
    fprintf(stdout, "server start\n");
    struct sockaddr_in peer_addr;
    socklen_t len = sizeof(peer_addr);
    char buf[1024];
    bzero(buf, 1024);
    ssize_t r = recvfrom(fd_, buf, 1024, 0, (struct sockaddr *)(&peer_addr), &len);
    if (r >= 0)
    {
      fprintf(stdout, "server recv = %s\n", buf);
      return;
    }  
    
    char str[128];
    bzero(str, 128);
    strerror_r(errno, str, 128);
    fprintf(stdout, "server errno = %d, err = %s\n", errno, str);
  }

  ~UDPServer()
  {
    fprintf(stdout, "server close: %d\n", fd_);
    close(fd_);
  }
};

struct UDPClient
{
  int fd_;
  struct sockaddr_in addr_;

  UDPClient(const char* ip, int port)
    : fd_(sockets::createUdpFd()),
      addr_()
  {
    sockets::setAddr(addr_, ip, port);
  }

  ~UDPClient()
  {
    close(fd_);
  }

  void start()
  {
    fprintf(stdout, "client start\n");
    socklen_t len = sizeof(addr_);
    char buf[8];
    bzero(buf, 8);
    buf[0] = 'a';
    ssize_t r = sendto(fd_, buf, 1, 0, (struct sockaddr *)(&addr_), len);
    if (r >= 0)
    {
      fprintf(stdout, "client send finished\n");
      return;
    }  
    
    char str[128];
    bzero(str, 128);
    strerror_r(errno, str, 128);
    fprintf(stdout, "client errno = %d, err = %s\n", errno, str);
  }

};
 


int main()
{
  const char* host = "0.0.0.0";
  int port = 9991;
  UDPServer server(host, port);
  UDPClient client(host, port);
  fprintf(stdout, "%s\n", "start");
  thread s(std::bind(&UDPServer::start, &server));
  sleep(1);
  thread c1(std::bind(&UDPClient::start, &client));

  s.join();
  c1.join();

  return 0;
}