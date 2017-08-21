#include <setjmp.h>
#include <stdio.h>

/**
 longjnp 不能跳转到已经返回的函数中。
*/
jmp_buf env;

void call(int i)
{
    fprintf(stdout, "call before\n");
    longjmp(env, i);

}

int main()
{
    int r = setjmp(env);
    if (0 == r)
    {
        call(1);
    }
    else if (1 == r)
    {
        fprintf(stdout, "call after result=%d\n", r);
 
    }
    return 0;
}

