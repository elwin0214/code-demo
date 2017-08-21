#include <unistd.h>
#include <errno.h> 
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define TRUE 1
//http://stackoverflow.com/questions/13322709/use-of-undeclared-identifier-true
void* read_fd(void *fd_ptr)
{   
    int fd = *(int*)fd_ptr;
    int i = 0;
    for (; i < 3; i++)
    {
        char buf[5];
        int r = read(fd, buf, 2);
        buf[3] = '\0';
        if (r <= 0)
        {
            fprintf(stdout, "try %d read, result=%d,errno=%d,msg=%s\n", i, r, errno, strerror(errno));
            close(fd);
        }else
        {
            fprintf(stdout, "try %d read %s\n", i, buf); 
        }
    }
    
    return NULL;
};
void* write_fd(void *fd_ptr)
{
    int i = 0;
    sleep(1);
    for (; i < 1; i++)
    {

        const char *buf = "h";
        int fd = *(int*)fd_ptr;
        int r = write(fd, buf, 2);
        if (r <= 0)
        {
            fprintf(stdout, "try %d write, result=%d,errno=%d,msg=%s\n", i, r, errno, strerror(errno));

        }else
        {
            fprintf(stdout, "try %d write %s then close fd\n", i, buf);
            int r = close(fd);
            fprintf(stdout, "close fd result=%d\n", r);

        }
        
        
    }
    
    return NULL;
};
int main()
{
    int fd[2];

    int r = pipe(fd);
    if (r < 0)
    {
        printf("pipe error, errno=%d", errno);
        return -1;
    }
    pthread_t t1, t2;
    pthread_create(&t1, NULL, write_fd, &(fd[1]));
    pthread_create(&t2, NULL, read_fd, &(fd[0]));
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}