#include <cstdio>
#include <vector>
#include <semaphore.h>
#include <iostream>

using std::vector;

class RingQueue
{
private:
    vector<int> _queue;
    int _capacity;
    int _head;
    int _tail;
    sem_t _size;    // 表示可读资源的数量
    sem_t _residue; // 表示可写资源的数量
    sem_t _lock;
public:
    RingQueue(int capacity = 10)
        : _capacity(capacity), _queue(capacity), _head(0), _tail(0)
    {
        sem_init(&_size, 0, 0);
        sem_init(&_residue, 0, capacity);
        sem_init(&_lock, 0, 1);
    }
    ~RingQueue()
    {
        sem_destroy(&_size);
        sem_destroy(&_residue);
        _queue.~vector();
    }
    // 写入
    void Push(const int &data);
    // 读取
    void Pop(int *data);
};

void RingQueue::Push(const int &data)
{
    // 判断是否有资源能够写入
    sem_wait(&_residue);
    // 加锁
    sem_wait(&_lock);
    _queue[_tail] = data;
    _tail = (_tail + 1) % _capacity;
    // 解锁
    sem_post(&_lock);
    sem_post(&_size);
}

void RingQueue::Pop(int *data)
{
    // 判断是否有资源读取
    sem_wait(&_size);
    // 加锁
    sem_wait(&_lock);
    *data = _queue[_head];
    _head = (_head + 1) % _capacity;
    // 解锁
    sem_post(&_lock);
    sem_post(&_residue);
}

void *thr_consumer(void *arg)
{
    RingQueue *q = (RingQueue*)arg;
    while(1) {
	int data;
	q->Pop(&data);
	std::cout<<"consumer thread get data:"<<data<<std::endl;
    }
    return NULL;
}
void *thr_productor(void *arg)
{
    RingQueue *q = (RingQueue*)arg;
    int i = 0;
    while(1) {
	q->Push(i);
	std::cout<<"productor thread put data:"<<i<<std::endl;
	i++;
    }
    return NULL;
}
int main (int argc, char *argv[])
{
    pthread_t ctid[4], ptid[4];
    int ret, i;
    RingQueue q;

    for (i = 0; i < 4; i++) {
	ret = pthread_create(&ctid[i], NULL, thr_consumer, (void*)&q);
	if (ret != 0) {
	    std::cout<<"thread create error\n";
	    return -1;
	}
    }
    for (i = 0; i < 4; i++) {
	ret = pthread_create(&ptid[i], NULL, thr_productor, (void*)&q);
	if (ret != 0) {
	    std::cout<<"thread create error\n";
	    return -1;
	}
    }
    for (i = 0; i < 4; i++) {
	pthread_join(ctid[i], NULL);
    }
    for (i = 0; i < 4; i++) {
	pthread_join(ptid[i], NULL);
    }
    return 0;
}
