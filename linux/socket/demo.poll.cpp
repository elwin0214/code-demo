#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <poll.h>
#include <algorithm>
#include "sockets.cpp"

struct pollfd;
using namespace std;

typedef function<void(int)> CloseCallBack;


struct Channel
{
    Channel(int fd, int index):fd_(fd),index_(index),closed_(false)
    {

    }
    ~Channel()
    {
        if (!closed_)
        {
            cout<<"close fd="<<fd_<<endl;
            sockets::close(fd_);
            closed_ = true;
        }
    }

    void handleRead()
    {
        char buf[1024];
        int len = read(fd_, buf, 1024);
        if (len < 0)
        {

        }
        else if (len == 0)
        {
            //close(); 不能先关
            if (closeCallBack_)
                closeCallBack_(fd_);
        }
        else
        {
            cout<<"handleRead, fd="<<fd_ <<",len="<<len<<", read="<<string(buf,len) <<endl;
            if (string(buf, 6) == "quit\r\n")
            {
                if (closeCallBack_)
                    closeCallBack_(fd_);
            }else
                write(fd_, buf, len);

        }

    }
    void handleWrite()
    {

    }
    void close()
    {
        if (!closed_)
        {
            cout<<"close fd="<<fd_<<endl;
            sockets::close(fd_);
            closed_ = true;
        }
    }
    void setCloseCallBack(CloseCallBack closeCallBack)
    {
        closeCallBack_ = closeCallBack;
    }
    void setIndex(int index){index_ = index;}
    int index(){return index_;}
    int fd_;
    int index_;
    bool closed_;
    CloseCallBack closeCallBack_;

};


struct ServerChannel
{
    ServerChannel(int fd):fd_(fd)
    {

    }
    int handleRead()
    {
        int cfd = accept(fd_, NULL, NULL);
        if (cfd < 0)
        {
            cout<<"accept fd="<<cfd << ",errno="<<errno<<endl;
        }
        sockets::setNoBlocking(cfd);
        return cfd;
    }
    ~ServerChannel()
    {
        sockets::close(fd_);
    }
    int fd(){return fd_;}
    
    int fd_;
};



struct EventLoop
{

public:
    typedef shared_ptr<Channel> ChannelPtr;

private:

    ServerChannel serverChannel;
    vector<struct pollfd> pollfds;
    map<int, ChannelPtr> channels;
    vector<int> acceptedFds;
    unordered_set<int> removeFds;


public:
    EventLoop(int fd):serverChannel(fd),pollfds(),channels()
    {
        struct pollfd pfd;
        pfd.fd = serverChannel.fd();
        pfd.events = POLLIN;
        pfd.revents = 0;
        pollfds.push_back(pfd);
    }
    ~EventLoop()
    {
        // for (map<int, ChannelPtr>::const_iterator itr = channels.begin(); itr != channels.end(); itr++)
        // {
        //     itr->second->close();
        // }

    }

    void acceptClient()
    {
        int fd = serverChannel.handleRead();
        cout<<"acceptClient,fd=" <<fd<<endl;
        acceptedFds.push_back(fd);
    }
    void registerClient()
    {
        removeClients();
        for (vector<int>::const_iterator itr = acceptedFds.begin(); itr != acceptedFds.end(); itr++)
        {
            struct pollfd pfd;
            int fd = *itr;
            pfd.fd = fd;
            pfd.events = POLLIN;
            pfd.revents = 0;

            pollfds.push_back(pfd);
            channels[fd] = make_shared<Channel>(fd, pollfds.size() - 1);
            channels[fd]->setCloseCallBack(std::bind(&EventLoop::addRemoveClient, this, std::placeholders::_1));

        }
        acceptedFds.clear();
        
    }
    void removeClients()
    {
        for (auto itr = removeFds.begin(); itr != removeFds.end(); itr++)
        {
            int fd = *itr;
            ChannelPtr removeChannel = channels[fd];
            channels.erase(fd);
            if( removeChannel->index() == pollfds.size() - 1 )
            {
                pollfds.pop_back();
                continue;
            }
            int endFd = pollfds.back().fd;
            iter_swap(pollfds.begin() + removeChannel->index(), pollfds.end() - 1);
            pollfds.pop_back();
        //pollfds.begin() + client->index()
            channels[endFd]->setIndex(removeChannel->index());

        }
        removeFds.clear();
        
    }

    void addRemoveClient(int fd)
    {
        cout<<"add client which will be removed, fd="<<fd <<""<<endl;
        removeFds.insert(fd);


    }


    void processClient(int fd)
    {
        ChannelPtr channel = channels[fd];
        if (!channel)
        {
            cout<<"fd="<<fd<<",error=null"<<endl;
            return;
        }
        int revents = pollfds[channel->index()].revents;
        cout<<"processClinet fd="<<fd<<", revents="<<revents<<endl;
        channel->handleRead();

    }
    void loop()
    {
        while (true)
        {   
            int r = poll(&(*(pollfds.begin())), pollfds.size(), 1000);
           // cout<<"poll result="<<r <<",size="<<(pollfds.size())<<endl;
            if (r < 0)
                cout<<"ERROR, r=" <<r <<" , errno="<<errno <<" "<<strerror(errno)<<endl;
            else if (r == 0)
            {
                //closeClient()
            }
            else
            {

                for (vector<pollfd>::const_iterator itr = pollfds.begin(); itr != pollfds.end(); itr++)
                {
                    short events = itr->revents;
                    int fd = itr->fd;
                    if ((events & POLLIN) == 0) continue;
                    if (fd == serverChannel.fd())
                    {
                        acceptClient();
                    }
                    else
                    {
                        processClient(fd);
                    }
                }   
            }
            registerClient();
        }
    }
};

int main()
{
    struct sockaddr_in addr;
    sockets::setAddr(addr, "127.0.0.1", 9999);
    int fd = sockets::createFd();
    sockets::setReuseAddr(fd);
    sockets::setNoBlocking(fd);
    sockets::bind(fd, addr);
    sockets::listen(fd);
    cout<<"create server fd= "<<fd<<endl;
    EventLoop loop(fd);
    loop.loop();
    
    //exit(1);
    return 0;
}
