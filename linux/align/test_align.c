#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

struct A
{
    int i;
    char c[0];
};

int main()
{
    fprintf(stdout, "sizeof(A)=%lu\n", sizeof(A));
    fprintf(stdout, "sizeof(size_t)=%lu\n", sizeof(size_t));//32-unsigned int ;64-unsigned long
    fprintf(stdout, "sizeof(unsigned long)=%lu\n", sizeof(unsigned long));
    fprintf(stdout, "sizeof(int)=%lu\n", sizeof(int));
    fprintf(stdout, "sizeof(ssize_t)=%lu\n", sizeof(ssize_t));//signed size_t
    fprintf(stdout, "sizeof(pid_t)=%lu\n", sizeof(pid_t));
    fprintf(stdout, "sizeof(pid_t)%lu\n", sizeof(ssize_t));

    char buf[3];
    buf[1] = '\0';
    fprintf(stdout, "%s\n", buf);//signed size_t

     
    return 0;
}