#include <unistd.h> 
#include <signal.h>

#include <iostream>
using namespace std;

/**
mac 上 20表示 SIGCHLD 和 linux不一致。 
*/
void sig_chld(int sig)
{
    cout<<"child exist, sign = "<<sig <<" "<<SIGCHLD<<endl;
};

int main()
{
    signal(SIGCHLD, sig_chld);

    if (fork() == 0)
    {

        cout<<"child process ="<<getpid() <<" started."<<endl;
        return 0;
    }
    else
    {

        cout<<"parent process started"<<endl;
        int status;
        pid_t pid = wait(&status);
        cout<<"child process=" <<pid <<" status="<<status<<endl;
        return 0;
    }
}