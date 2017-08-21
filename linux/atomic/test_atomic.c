#include <pthread.h>
#include <stdio.h>
// 查看汇编 gdb下 disassemble <function> 
// 32 -ebp  x86_64 - rbp

//g++ test_atomic.c  -o test_atomic.o -g
//otool -tV test_atomic.o 
//http://www.cnblogs.com/lxgeek/archive/2011/01/01/1923738.html
struct obj
{
    int value;
};
struct obj o;

void* write_1_obj(void *p)
{
    o.value = 1;
    return NULL;
};

void* write_2_obj(void *p)
{
    o.value = 2;
    return NULL;
};

void* read_obj(void *p)
{
    o.value = 2;
    return NULL;
};

int sum(int a, int b)
{
    int s = a + b;
    s = s + 100;
    return s;
};
/*
__Z3sumii:
0000000100000e50    pushq   %rbp
0000000100000e51    movq    %rsp, %rbp
0000000100000e54    movl    %edi, -0x4(%rbp)
0000000100000e57    movl    %esi, -0x8(%rbp)
0000000100000e5a    movl    -0x4(%rbp), %esi
0000000100000e5d    addl    -0x8(%rbp), %esi
0000000100000e60    movl    %esi, -0xc(%rbp)
0000000100000e63    movl    -0xc(%rbp), %esi
0000000100000e66    addl    $0x64, %esi
0000000100000e6c    movl    %esi, -0xc(%rbp)
0000000100000e6f    movl    -0xc(%rbp), %eax
0000000100000e72    popq    %rbp
0000000100000e73    retq
0000000100000e74    nopw    %cs:(%rax,%rax)
*/

int main()
{   
    int p = sum (8, 16);
/*
0000000100000e88    movl    $0x8, %edi
0000000100000e8d    movl    $0x10, %esi
0000000100000e92    movl    $0x0, -0x4(%rbp)
0000000100000e99    callq   __Z3sumii               ## sum(int, int)
*/
    printf("%d", p);
    int i = 0;
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, write_1_obj, NULL);
    pthread_create(&t2, NULL, write_2_obj, NULL);
    pthread_create(&t3, NULL, read_obj, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);


    return 0;
}