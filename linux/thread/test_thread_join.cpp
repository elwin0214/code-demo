#include <pthread.h>
#include <errno.h> 
#include <stdio.h>

int ret = 0;

void* call(void *arg)
{
    fprintf(stdout, "call\n");
    ret = 1;
    return (void*)&ret;
};

void* call_exit(void *arg)
{
    fprintf(stdout, "call\n");
    ret = 2;
    pthread_exit(&ret);
    //return (void*)&ret;
};

int main()
{
    pthread_t t1 ;
    void* t1_ret;
    pthread_create(&t1, NULL, call, NULL);
    pthread_join(t1, &t1_ret);
    fprintf(stdout, "%s-%d\n", "thread1", *(int*)t1_ret);

    ret = 0;

    pthread_t t2 ;
    void* t2_ret;
    pthread_create(&t2, NULL, call_exit, NULL);
    pthread_join(t2, &t2_ret);
    fprintf(stdout, "%s-%d\n", "thread2", *(int*)t2_ret);
    return 0;
}
