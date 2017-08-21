#include <pthread.h>
#include <stdio.h>
//gdb : info register rdi

// g++ test_gcc_atomic.c  -o test_gcc_atomic.o -g
//  otool -tV test_gcc_atomic.o 
//https://en.wikipedia.org/wiki/Fetch-and-add

//xadd 指令 见http://x86.renejeschke.de/html/file_module_x86_id_327.html
/*
Exchanges the first operand (destination operand) with the second operand (source operand), 
then loads the sum of the two values into the destination operand. The destination operand
can be a register or a memory location; the source operand is a register.
This instruction can be used with a LOCK prefix to allow the instruction to be executed atomically.
*/
int atomic_add(int *p, int value)
{
   return __sync_add_and_fetch (p, value);
};

/*
__Z10atomic_addPii:
0000000100000de0    pushq   %rbp
0000000100000de1    movq    %rsp, %rbp
0000000100000de4    movq    %rdi, -0x8(%rbp)  ##int *p
0000000100000de8    movl    %esi, -0xc(%rbp)  ##int value
0000000100000deb    movq    -0x8(%rbp), %rdi
0000000100000def    movl    %esi, %eax
0000000100000df1    lock
0000000100000df2    xaddl   %esi, (%rdi)
0000000100000df5    addl    %eax, %esi
0000000100000df7    movl    %esi, %eax
0000000100000df9    popq    %rbp
0000000100000dfa    retq
0000000100000dfb    nopl    (%rax,%rax)
*/
struct Data
{
    char name;
    int value;
};

void* write_obj(void *p)
{   
    struct Data* pd = (struct Data*)p;
    int result = atomic_add(&(pd->value), 1);
    fprintf(stdout, "add = %d\n", result);
    return NULL;
};
/*
0000000100000e00    pushq   %rbp
0000000100000e01    movq    %rsp, %rbp
0000000100000e04    subq    $0x20, %rsp
0000000100000e08    movl    $0x1, %esi  ## 形参 1
0000000100000e0d    movq    %rdi, -0x8(%rbp) 
0000000100000e11    movq    -0x8(%rbp), %rdi
0000000100000e15    movq    %rdi, -0x10(%rbp)
0000000100000e19    movq    -0x10(%rbp), %rdi
0000000100000e1d    addq    $0x4, %rdi  // Data.value 偏移
0000000100000e24    callq   __Z10atomic_addPii      ## atomic_add(int*, int)
*/

void* read_obj(void *p)
{   
    struct Data* pd = (struct Data*)p;
    fprintf(stdout, "%d\n", pd->value);
    return NULL;
};

int main()
{
    struct Data data = {'a', 0};
    int i = 0;
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, write_obj, &data);
    pthread_create(&t2, NULL, write_obj, &data);
    pthread_create(&t3, NULL, read_obj, &data);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);


    return 0;
}