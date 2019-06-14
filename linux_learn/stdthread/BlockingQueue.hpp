#pragma once

/*
*	1. 抛异常 add() 添加 remove() 移除 element() 检查 操作如果无法立刻执行抛出异常
*	2. 特定值 offer() poll() peek() 如果操作无法立即执行， 返回true/false
*	3. 阻塞   put() take() 如果试图的操作无法立即执行，该方法调用将会发生阻塞，直到能够执行
*/

#include <queue>
#include <mutex>
#include <condition_variable>


template <class T>
class BlockingQueue
{
public:
	explicit BlockingQueue(size_t capacity = 0):capacity_(capacity) {}
	bool add(T& e) {
		return offer(e);
	}
	bool offer(T& e)
	{
		std::lock_guard<std::mutex> lock(lock_);
		if (count_ == capacity_)
			return false;
		else
		{
			queue_.push(e);
			return true;
		}
	}
	void put(T& e)
	{
		std::unique_lock<std::mutex> lock(lock_);
		notFull_.wait(lock, [this] {
			while (count_ == capacity_)
				return false;
			return true;
		});
		queue_.push(e);
	}

	T poll()
	{
		std::lock_guard<std::mutex> lock(lock_);
		if (count_ == 0)
		{
			throw "NullPointException";
		}
		T e = queue_.front();
		queue_.pop();
		return e;
	}

	T take()
	{
		std::unique_lock<std::mutex> lock(lock_);
		notEmpty_.wait(lock, [this] {
			while (count_ == 0)
				return false;
			return true;
		});
		T e = queue_.front();
		queue_.pop();
		return e;
	}

	size_t size()
	{
		std::lock_guard<std::mutex> lock(lock_);
		return count_;
	}

	~BlockingQueue() = default;


private:
	std::queue<T> queue_;
	size_t capacity_;
	size_t count_;
	std::mutex lock_;
	std::condition_variable notFull_;
	std::condition_variable notEmpty_;
};

