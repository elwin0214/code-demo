#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/uio.h>

using namespace std;
namespace sockets
{
int createFd()
{   
  int fd = ::socket(AF_INET, SOCK_STREAM, 0);
  if(fd < 0)
  {
    fprintf(stdout, "errno = %d, err = %s\n", errno, strerror(errno));
  }
  return fd;
};
int createUdpFd()
{
  int fd = ::socket(AF_INET, SOCK_DGRAM, 0);
  if(fd < 0)
  {
    fprintf(stdout, "errno = %d, err = %s\n", errno, strerror(errno));
  }
  return fd;
};

int setNoBlocking(int fd)
{
  int flags = fcntl(fd, F_GETFL, 0);
  int r = fcntl(fd, F_SETFL, flags|O_NONBLOCK);
  if(r < 0)
    fprintf(stdout, "fd = %d, errno = %d, err = %s\n", fd, errno, strerror(errno));
  return r;
};
int setReuseAddr(int fd)
{
  int val = 1;
  int r = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
  if (r < 0)
  {
    fprintf(stdout, "fd = %d, errno = %d, err = %s\n", fd, errno, strerror(errno));
  }
  return r;
};

int setRcvTimeout(int sockfd, int seconds)
{
  struct timeval timeout;  
  timeout.tv_sec = seconds;  
  timeout.tv_usec = 0;  
  socklen_t len = sizeof(timeout);  
  int r = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, len);
  if (r < 0)
  {
    fprintf(stdout, "fd = %d, errno = %d, err = %s\n", sockfd, errno, strerror(errno));
  }
  return r;
};

int setSndTimeout(int sockfd, int seconds)
{
  struct timeval timeout;  
  timeout.tv_sec = seconds;  
  timeout.tv_usec = 0;  
  socklen_t len = sizeof(timeout);  
  int r = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
  if (r < 0)
  {
    fprintf(stdout, "fd = %d, errno = %d, err = %s\n", sockfd, errno, strerror(errno));
  }
  return r;
};

void setAddr(struct sockaddr_in &addr, const char *ip, int port)
{
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
};

int bind(int fd, struct sockaddr_in &addr)
{
  int r = ::bind(fd,  (struct sockaddr *)&addr, sizeof(addr));
  if (r < 0)
  {
    fprintf(stdout, "errno = %d, err = %s\n", errno, strerror(errno));
  }
  return r;
};

int listen(int fd)
{
  int r = ::listen(fd, 10);
  if (r < 0)
  {
    fprintf(stdout, "fd = %d, errno = %d, err = %s\n", fd, errno, strerror(errno));
  }
  return r;
};

int accept(int fd, struct sockaddr_in &addr)
{
  socklen_t len = sizeof(addr);
  int r = ::accept(fd, (struct sockaddr *)&addr, &len);
  if (r < 0)
  {
    fprintf(stdout, "fd = %d, errno = %d, err = %s\n", fd, errno, strerror(errno));
  }
  return r;
};

int connect(int fd, struct sockaddr_in &addr)
{
  int r = connect(fd, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  if (r < 0)
  {
    fprintf(stdout, "fd = %d, errno = %d, err = %s\n", fd, errno, strerror(errno));
  }
  return r;
};

int close(int fd)
{
  int r = ::close(fd);
  if (r < 0)
  {
    fprintf(stdout, "fd = %d, errno = %d, err = %s\n", fd, errno, strerror(errno));
  }
  return r;
};

ssize_t write(int fd, const void* buf, size_t len)
{
  ssize_t r = ::write(fd, buf, len);
  if (r < 0)
  {
    fprintf(stdout, "fd = %d, errno = %d, err = %s\n", fd, errno, strerror(errno));
  }
  return r;
};

ssize_t read(int fd, void* buf, size_t len)
{
  ssize_t r = ::read(fd, buf, len);
  if (r < 0)
  {
    fprintf(stdout, "fd = %d, errno = %d, err = %s\n", fd, errno, strerror(errno));
  }
  return r;
};

}