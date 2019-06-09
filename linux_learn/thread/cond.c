#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

pthread_cond_t product;
pthread_cond_t consumer;

int container = 1;

void *thr_productor(void *arg)
{
    while (1)
    {
        
        // 创建临界区
        pthread_mutex_lock(&mutex);
        if (container == 0)
        {
            printf("i producted\n");
            container++;
            // 加锁
            pthread_cond_signal(&consumer);
        }
        // 解锁
        pthread_cond_wait(&product, &mutex);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

void *thr_consumer(void *arg)
{
    while (1)
    {
        // 创建临界区
        pthread_mutex_lock(&mutex);
        if (container == 1)
        {
            printf("i consumer\n");
            container--;
            // 加锁
            pthread_cond_signal(&product);
        }

        // 解锁
        pthread_cond_wait(&consumer, &mutex);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t tid1, tid2;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&consumer, NULL);
    pthread_cond_init(&product, NULL);

    pthread_create(&tid1, NULL, thr_productor, "productor");
    pthread_create(&tid2, NULL, thr_consumer, "consumer");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&consumer);
    pthread_cond_destroy(&product);

    return 0;
}