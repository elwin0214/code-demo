#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    const char *addr = "127.0.0.1";
    int port = 9999;
    int max_fd = -1;
    struct sockaddr_in server_addr;
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        cout<<"socket exit,errno=" <<errno <<endl;
        exit(1);
    }
    max_fd = max_fd < sfd ? sfd : max_fd;
    int val = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int)) < 0)
    {
        cout<<"setsockopt exit,errno=" <<errno <<endl;
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(addr);
 
    if (::bind(sfd,  (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        cout<<"bind exit,errno=" <<errno <<endl;
        exit(1);
    }
    if (::listen(sfd, 10) < 0)
    {
        cout<<"listen exit,errno=" <<errno <<endl;
        exit(1);
    }
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int fd = accept(sfd, (struct sockaddr *)&client_addr, &len);

    if (fd<0)
    {
        cout<<"accept exit,errno=" <<errno <<endl;
        exit(1);
    }
    uint16_t client_port = ntohs(client_addr.sin_port);
    char client_ip[1024];
    inet_ntop(AF_INET, &(client_addr.sin_addr.s_addr), client_ip, 1024);

    cout<<"client,ip=" <<client_ip <<",port=" <<client_port <<endl;
    char buf[1024];

    int flags = fcntl(fd, F_GETFL, 0);
    cout<<"fd=" <<fd <<", before flag=" <<flags <<",noblock=" <<O_NONBLOCK <<endl;
    int r = fcntl(fd, F_SETFL, flags|O_NONBLOCK);
    cout<<"fd=" <<fd <<", result=" <<r <<",noblock=" <<O_NONBLOCK <<endl;

    while (true)
    {
        //int len = read(fd, buf,5);
        int len = recv(fd, buf,5, 0);
        if (len <= 0)
        {
            cout<<"client, len="<<len<<",errno="<<strerror(errno)<<endl;// errno=35
            //非阻塞状态没数据可读 client, len=-1,errno=Resource temporarily unavailable

            //::close(fd);
            //break;
        }
        else
        {
            cout<<" read fd="<<fd<<", len="<<len<<", read:"<<string(buf,len)<<endl;
        }
        sleep(2);
        cout<<"end sleep"<<endl;
    }
   
    return 0;
}
