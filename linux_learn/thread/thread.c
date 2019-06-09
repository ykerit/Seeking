#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void* thr_start(void *arg)
{
    // printf("thread start!\n");
    // sleep(5);
    // pthread_exit("i did exit");
    while (1)
    {
        printf("i am new thread![%s][%d]\n", arg, (int)pthread_self());
        sleep(1);
    }
    // int* p = (int*)malloc(sizeof(int));
    // *p = 1;
    // return (void*)p;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thr_start, (void*)"for new");
    if (ret != 0)
    {
        fprintf(stderr, "thread create error: [$s]\n", strerror(ret));
        return -1;
    }

    // char exit[200] = {0}; // 不能使用数组形式的char数组
    // 如果线程是pthread_exit()退出， pthread_join接受的是pthread_exit函数中参数值
    // char* exit = NULL;
    // pthread_join(tid, (void**)&exit);
    // printf("exit info: %s\n", exit);
    // 如果线程是return退出，pthread_join接受的是return的值
    void* exit;
    // pthread_join(tid, &exit);
    // printf("exit info: %d\n", *(int*)exit);
    // 如果线程是通过pthread_cancel 退出，pthread_join接受的是PTHREAD_CANCELED
    sleep(5);
    pthread_cancel(tid);
    pthread_join(tid, &exit);
    if (exit == PTHREAD_CANCELED)
    {
        printf("exit info: PTHREAD_CANCELED\n");
    } else
    {
        printf("exit info: NULL");
    }
    
    
    while (1)
    {
        printf("i am main thread[%d]\n", (int)pthread_self());
        sleep(1);
    }
    return 0;
}
