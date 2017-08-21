#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include  <errno.h>

int main()
{
    printf("%s\n", "mmap");
    int fd = open("test.txt", O_RDWR); 
    printf("create fd=%d ,errno=%d\n", fd, errno);
    int len = 10;
    void *p1 = mmap(NULL, len , PROT_READ|PROT_WRITE, MAP_SHARED , fd , 0);
    void *p2 = mmap(NULL, len , PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON , -1 , 0);

    
    printf("mmap file=%p\n", p1);
    printf("mmap file content=%s\n", (char*)p1);//执行到这里,有读取时，才能看到vma
    printf("anonymous mmap=%p , errno=%d\n", p2, errno);

    char* p = (char*)p2;
    p[0] = 1;
    usleep(100000000);//sleep 1000s

    int u1 = munmap(p1, len);
    int u2 = munmap(p2, len);

    printf("u1=%d\n", u1);
    printf("u2=%d\n", u2);


    return 0;
}
