#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void* thr_start(void *arg)
{
    printf("i am start\n");
    sleep(3);
    printf("i died\n");
    return NULL;
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
    pthread_detach(tid);
    while (1)
    {
        printf("i am main thread[%d]\n", (int)pthread_self());
        sleep(1);
    }
    return 0;
}
