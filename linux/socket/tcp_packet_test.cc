#include "sockets.cc"

const char* gHost = "0.0.0.0";
int gPort = 8080;

struct Server
{
  Server()
    : fd_(sockets::createFd()),
      addr_()
  {
    sockets::setAddr(addr_, gHost, gPort);
    sockets::bind(fd_, addr_);
    sockets::listen(fd_);
  }

  send()
  {
    sockets::write(fd_, "h", 1);
  }

  int fd_;
  struct sockaddr_in addr_;
};



struct Client
{
  Client()
    : fd_(sockets::createFd()),
      addr_()
  {
    sockets::setAddr(addr_, gHost, gPort);
  }

  void connect()
  {
    sockets::connect(fd_, addr_);
  }

  int fd_;
  struct sockaddr_in addr_;
};

int main()
{

}