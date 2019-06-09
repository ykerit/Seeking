#include <pthread.h>
#include <queue>
#include <cstdio>

class BlockQueue
{
private:
    std::queue<int> _queue;
    int _capacity;
    pthread_mutex_t _mutex;
    pthread_cond_t _consumer;
    pthread_cond_t _product;

public:
    BlockQueue(int capacity = 10) : _capacity(capacity)
    {
        pthread_mutex_init(&_mutex, NULL);
        pthread_cond_init(&_consumer, NULL);
        pthread_cond_init(&_product, NULL);
    }

    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_consumer);
        pthread_cond_destroy(&_product);
    }

    // push
    bool Push(const int &data);
    // pop
    bool Pop(int *data);

private:
    bool mutexLock()
    {
        pthread_mutex_lock(&_mutex);
        return true;
    }
    bool mutexUnLock()
    {
        pthread_mutex_unlock(&_mutex);
        return true;
    }
    bool notifyProduct()
    {
        pthread_cond_signal(&_product);
        return true;
    }
    bool waitProduct()
    {
        pthread_cond_wait(&_product, &_mutex);
        return true;
    }
    bool notifyConsumer()
    {
        pthread_cond_signal(&_consumer);
        return true;
    }
    bool waitConsumer()
    {
        pthread_cond_wait(&_consumer, &_mutex);
        return true;
    }
    bool isEmpty()
    {
        return _queue.empty();
    }
    bool isFull()
    {
        return _queue.size() == _capacity;
    }
};

// push
bool BlockQueue::Push(const int &data)
{
    mutexLock();
    while (isFull())
    {
        waitProduct();
    }
    _queue.push(data);
    notifyConsumer();
    mutexUnLock();
    return true;
}

// pop
bool BlockQueue::Pop(int *data)
{
    mutexLock();
    while (isEmpty())
    {
        waitConsumer();
    }
    *data = _queue.front();
    _queue.pop();
    notifyProduct();
    mutexUnLock();
    return true;
}

void *productStart(void *arg)
{
    int data = 1;
    BlockQueue *q = (BlockQueue *)arg;
    while (1)
    {
        q->Push(data++);
        printf("tid=%lu product: %d\n", pthread_self(), data);
    }
    return NULL;
}

void *consumerStart(void *arg)
{
    BlockQueue *q = (BlockQueue *)arg;
    int data;
    while (1)
    {
        q->Pop(&data);
        printf("tid=%lu consumer: %d\n", pthread_self(), data);
    }
}

int main()
{
    BlockQueue blockQueue;

    pthread_t tidProduct[4];
    pthread_t tidConsumer[4];

    for (int i = 0; i < 4; i++)
    {
        pthread_create(&tidProduct[i], NULL, productStart, &blockQueue);
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_create(&tidConsumer[i], NULL, consumerStart, &blockQueue);
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(tidProduct[i], NULL);
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(tidConsumer[i], NULL);
    }

    return 0;
}