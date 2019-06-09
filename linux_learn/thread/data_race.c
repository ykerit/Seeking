#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int ticket = 100;

void* thr_start(void* arg)
{
    pthread_detach(pthread_self());
    char* id = (char*)arg;


    while (ticket > 0)
    {
        sleep(1);
        printf("%s sell ticket %d\n", id, ticket);
        ticket--;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, NULL, thr_start, "thread 1");
    sleep(1);
    pthread_create(&t2, NULL, thr_start, "thread 2");
    sleep(1);
    pthread_create(&t3, NULL, thr_start, "thread 3");
    sleep(1);
    pthread_create(&t4, NULL, thr_start, "thread 4");
    // 如果使用pthread_detach, 需要保持主线程不会销毁,也就是程序不退出,否则线程会跟随进程的退出而退出
    while (1)
    {
        /* code */
    }
    
    // pthread_join(t1, NULL);
    // pthread_join(t2, NULL);
    // pthread_join(t3, NULL);
    // pthread_join(t4, NULL);

    return 0;
}