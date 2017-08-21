#include <pthread.h>
#include <errno.h> 
#include <stdio.h>
#include <unistd.h>

int ret = 0;

void cleanup(void *arg)
{
    fprintf(stdout, "cleanup\n");
};

void* test_cancel(void* arg)
{
    pthread_cleanup_push(cleanup, NULL);
    pthread_testcancel();
    sleep(3);
    pthread_testcancel();//取消点
    pthread_cleanup_pop(0);
    return NULL;
};

void* test_exit(void* arg)
{
    pthread_cleanup_push(cleanup, NULL);
    //pthread_testcancel();
    ret = 2;
    pthread_exit(&ret);
    //pthread_testcancel();
    pthread_cleanup_pop(0);
    return NULL;
};

void* test_return(void* arg)
{
    pthread_cleanup_push(cleanup, NULL);
     return (void*)(1);//在cleanup中return 会引起 segment fault
    pthread_cleanup_pop(0);
    //return NULL;
};

int main()
{
    pthread_t t1 ;
    void* t1_ret;
    pthread_create(&t1, NULL, test_cancel, NULL);
    pthread_cancel(t1);//call cleanup
    pthread_join(t1, &t1_ret);

    pthread_t t2 ;
    pthread_create(&t2, NULL, test_exit, NULL);//call cleanup
    pthread_join(t2, NULL);

    pthread_t t3 ;
    pthread_create(&t3, NULL, test_return, NULL);//dont call cleanup
    pthread_join(t3, NULL);
 
    return 0;
}
