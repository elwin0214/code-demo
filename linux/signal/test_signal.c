#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> 
#include <stdio.h>
#include <string.h>
/*
kill -l 
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL
 5) SIGTRAP      6) SIGABRT      7) SIGBUS       8) SIGFPE
 9) SIGKILL     10) SIGUSR1     11) SIGSEGV     12) SIGUSR2
13) SIGPIPE     14) SIGALRM     15) SIGTERM     16) SIGSTKFLT
17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU
25) SIGXFSZ     26) SIGVTALRM   27) SIGPROF     28) SIGWINCH
29) SIGIO       30) SIGPWR      31) SIGSYS      34) SIGRTMIN
35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3  38) SIGRTMIN+4
39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12
47) SIGRTMIN+13 48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14
51) SIGRTMAX-13 52) SIGRTMAX-12 53) SIGRTMAX-11 54) SIGRTMAX-10
55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7  58) SIGRTMAX-6
59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
*/
/*
mac 上 20表示 SIGCHLD 和 linux不一致。 

The signals SIGKILL and SIGSTOP cannot be caught or ignored.

两种语义：
BSD
SYSTEM V ：会重置为SIG_DFL


 On glibc 2 and later, if the _BSD_SOURCE feature test macro is not defined, 
 then signal() provides System V semantics.  
 (The default implicit definition of _BSD_SOURCE is not provided 
  if one  invokes  gcc(1)  in  one  of  its  standard  modes 
   (-std=xxx  or  -ansi) or defines various other feature test macros
    such as _POSIX_SOURCE, _XOPEN_SOURCE, or _SVID_SOURCE; see fea‐
         ture_test_macros(7).)
*/
void func(int sig)
{
    fprintf(stdout, "func before, sig - %d\n", sig);
     for (int i = 0; i < 3; i++)
    {
        sleep(3);
        fprintf(stdout, "func, %s", "wake up\n");
    }
    fprintf(stdout, "func after, sig - %d\n", sig);


};
int main()
{
    if (signal(SIGINT, func) == SIG_ERR) //Ctrl+C  kill -2 
    {
        fprintf(stderr, "%s\n", "signal SIGINT error");
        exit(1);
    };
    if (signal(SIGTERM, func) == SIG_ERR) //kill 
    {
        fprintf(stderr, "%s\n", "signal SIGTERM error");
        exit(1);
    };
    //if (signal(SIGKILL, func) == SIG_ERR) //SIGKILL cannot be caught
    //{
      //  fprintf(stderr, "%s\n", "signal SIGKILL error");
        //exit(1);
    //};
   

    for (int i = 0; i < 6; i++)
    {
        sleep(100);
        fprintf(stdout, "main, %s", "wake up\n");

    }
    fprintf(stdout, "main, %s", "exit succ\n");
    return 0;
}