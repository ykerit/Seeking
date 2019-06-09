/*
 * @Description: vector by myself
 * @Author: yker
 * @Date: 2019-05-31 15:43:29
 * @LastEditTime: 2019-06-09 20:09:41
 */
#include <cstddef>
#include <algorithm>
#include <assert.h>

template <class T>
class Vector
{
public:
    typedef T *iterator;
    Vector() : start_(nullptr), finish_(nullptr), endOfStorage_(nullptr) {}
    Vector(const Vector<T> &v) : start_(nullptr), finish_(nullptr), endOfStorage_(nullptr)
    {
        Reserve(v.Size());
        size_t size = v.Size();
        for (size_t i = 0; i < size; i++)
        {
            start_[i] = v[i];
        }
    }
    ~Vector()
    {
        if (start_)
        {
            delete[] start_;
            start_ = finish_ = endOfStorage_ = nullptr;
        }
    }

    Vector<T> &operator=(const Vector<T> &v)
    {
        Swap(v);
        return *this;
    }
    iterator begin()
    {
        return start_;
    }
    iterator end()
    {
        return finish_;
    }
    void Swap(Vector<T> &v)
    {
        std::swap(start_, v.start_);
        std::swap(finish_, v.finish_);
        std::swap(endOfStorage_, v.endOfStorage_);
    }
    void Reserve(size_t n = 0)
    {
        if (n > Capacity())
        {
            // 需要先保存size， 因为finish指针需要推断
            size_t size = Size();
            T *newArray = new T[n];
            for (size_t i = 0; i < size; i++)
            {
                newArray[i] = start_[i];
            }
            delete[] start_;

            start_ = newArray;
            finish_ = start_ + size;
            endOfStorage_ = start_ + n;
        }
    }
    void Resize(size_t n, const T &val = T())
    {
        if (n > Capacity())
        {
            Reserve(n);
            while (finish_ != start_ + n)
            {
                *finish_ = val;
                ++finish_;
            }
        }
        else
        {
            finish_ = start_ + n;
        }
    }
    void PushBack(const T &t)
    {
        if (finish_ == endOfStorage_)
        {
            // 2倍增长
            size_t newCapacity = Capacity() == 0 ? 4 : Capacity() * 2;
            Reserve(newCapacity);
        }
        *finish_ = t;
        ++finish_;
    }
    void Insert(iterator pos, const T &t)
    {
        assert(pos < finish_);
        if (finish_ == endOfStorage_)
        {
            size_t n = pos - start_;
            size_t newCapacity = Capacity() == 0 ? 4 : 2 * Capacity();
            Reserve(newCapacity);
            // 扩容后 pos地址所指向的内容失效 需要将pos指向新的地址
            pos = start_ + n;
        }
        iterator end = finish_ - 1;
        while (end >= pos)
        {
            *(end + 1) = *end;
            --end;
        }
        *pos = t;
        ++finish_;
    }
    iterator Erase(iterator pos)
    {
        assert(pos < finish_);
        iterator iter = pos;
        while (iter < finish_-1)
        {
            *iter = *(iter+1);
            ++iter;
        }
        --finish_;
        return pos;
    }
    size_t Capacity() const { return endOfStorage_ - start_; }
    size_t Size() const { return finish_ - start_; }

private:
    iterator start_;
    iterator finish_;
    iterator endOfStorage_;
};