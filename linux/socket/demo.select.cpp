#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <map>
#include <string>
#include <iostream>
#include <string.h>
#include "sockets.cpp"

using namespace std;

int main()
{
    const char *addr = "127.0.0.1";
    int port = 9999;
    int max_fd = -1;

    int sfd = sockets::createFd();
    max_fd = max_fd < sfd ? sfd : max_fd;
    sockets::setReuseAddr(sfd);
    struct sockaddr_in server_addr;
    sockets::setAddr(server_addr, addr, port);
    sockets::bind(sfd, server_addr);
    sockets::listen(sfd);

    fd_set rfs;
    fd_set wfs;
    struct timeval tv;
    //tv.tv_sec = 3;
    //tv.tv_usec = 0;

    FD_ZERO(&rfs);
    FD_SET(sfd, &rfs);

    map<int,bool> fd_map;
    while (true)
    {
        tv.tv_sec = 3;//linux: man (ii)   select() may update the timeout argument to indicate how much time was left.  pselect() does not change this argument.
        tv.tv_usec = 0;
        int n = select(max_fd + 1, &rfs, NULL, NULL, &tv);
        cout << "select max_fd=" << max_fd <<", events=" << n <<endl;
        if (n <= 0)
        {
            //continue;
        }
        else
        {
            if (FD_ISSET(sfd, &rfs))
            {
                struct sockaddr_in client_addr;
                socklen_t len = sizeof(client_addr);
                int fd = accept(sfd, (struct sockaddr *)&client_addr, &len);
                if (fd < 0)
                {
                    cout << "accept error" << endl;
                    exit(1);
                }
            
                else// new client
                {
                    max_fd = max_fd < fd ? fd : max_fd;
                    cout << "accept a new fd=" << fd <<", port="<< ntohs(client_addr.sin_port) <<endl;
                    // int flags = fcntl(fd, F_GETFL, 0);
                    // cout << "fd=" << fd <<", flag=" << flags << ",noblock=" << O_NONBLOCK <<endl;
                    // fcntl(fd, F_SETFL, flags|O_NONBLOCK);
                    sockets::setNoBlocking(fd);
                    sockets::setRcvTimeout(fd, 5);
                    fd_map.insert(map<int, bool>::value_type(fd, true));
                }

            }
            for (map<int, bool>::iterator itr = fd_map.begin(); itr != fd_map.end();)
            {
                int fd = itr->first;
                char buf[1024];
                bzero(buf, sizeof(buf));
                if (FD_ISSET(fd, &rfs))
                {
                    int len = read(fd, buf, 5);
                    if (len <= 0)
                    {
                        if (len < 0)
                            cout << "fd "<<fd << " error " << endl;
                        else
                            cout<< "fd " <<fd << " closed " << endl;

                        map<int, bool>::iterator prev = itr;
                        itr++;
                        fd_map.erase(prev);
                        close(fd);
                        continue;
                    }
                    else
                    {
                        cout << " read fd=" << fd << ", len=" <<len << ", read content=" << string(buf, len) << endl;
                    }
                }

                itr++;
            }
        }
        FD_ZERO(&rfs);
        FD_ZERO(&wfs);
        cout << "map.size:" << fd_map.size() <<endl;
        for (map<int, bool>::iterator itr = fd_map.begin(); itr != fd_map.end(); itr++)
        {
            cout<< "add fd:" << (itr->first) <<endl;
            FD_SET(itr->first, &rfs);
        }
        FD_SET(sfd, &rfs);

    }
    return 0;
}