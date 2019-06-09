/*
 * @Description: string by myself
 * @Author: yker
 * @Date: 2019-05-31 10:48:04
 * @LastEditTime: 2019-05-31 16:02:59
 */

#include <cstddef>
#include <cstring>
#include <algorithm>

class String
{
private:
	char *str_;
	int capacity_;
	int size_;
	static const size_t npos = -1;

public:
	String(const char *str = "") : capacity_(0), size_(strlen(str)), str_(nullptr)
	{
		Reserve(size_);
		strcpy(str_, str);
	}
	~String()
	{
		if (str_)
		{
			delete[] str_;
			str_ = nullptr;
			size_ = capacity_ = 0;
		}
	}
	// 拷贝构造
	String(const String& str): str_(new char[str.capacity_]), capacity_(str.capacity_), size_(str.size_)
	{
		strcpy(str_, str.str_);
	}

	// 赋值 使用构造函数重新分配空间
	String& operator=(String str)
	{
		std::swap(str_, str.str_);
		size_ = str.size_;
		capacity_ = str.capacity_;
		return *this;
	}

	size_t Size()
	{
		return size_;
	}

	size_t Capacity()
	{
		return capacity_;
	}

	char *Str()
	{
		return str_;
	}

	void Reserve(size_t n);
	void Resize(size_t n);
	void Resize(size_t n, char c);

	char &operator[](size_t pos)
	{
		if (pos >= size_)
		{
			return str_[size_];
		}
		return str_[pos];
	}

	const char &operator[](size_t pos) const
	{
		if (pos >= size_)
		{
			return str_[size_];
		}
		return str_[pos];
	}

	void push_back(char c);
	String &Append(const String &str);
	String &Append(const char *s);
	String &Append(size_t n, char c);
	String &Erase(size_t pos = 0, size_t len = npos);
};

void String::Reserve(size_t n = 0)
{
	// 没有空间或者空间不够扩容
	if (n == 0 || n > capacity_)
	{
		size_t newSize = 0;
		// 每次扩容8的倍数
		if (n % 8 != 0)
		{
			newSize = (n / 8 + 1) * 8;
		}
		else
		{
			newSize = n + 8;
		}
		char *newStr = new char[newSize];
		if (str_)
		{
			strcpy(newStr, str_);
		}
		// 指针为空
		str_ = newStr;
		capacity_ = newSize - 1;
	}
}
void String::Resize(size_t n)
{
	if (n > capacity_)
	{
		Reserve(n);
	}
	size_ = n;
}
void String::Resize(size_t n, char c)
{
	if (n > capacity_)
	{
		Reserve(n);
	}
	for (size_t i = size_; i < n; i++)
	{
		str_[i] = c;
	}
	str_[n] = '\0';
	size_ = n;
}

void String::push_back(char c)
{
	++size_;
	if (size_ > capacity_)
	{
		Reserve(size_);
	}
	str_[size_ - 1] = c;
	str_[size_] = '\0';
}

String &String::Append(const String &str)
{
	size_t len = str.size_ + size_;
	if (len > capacity_)
	{
		Reserve(len);
	}
	strcat(str_, str.str_);
	size_ = len;
	return *this;
}

String &String::Append(const char *s)
{
	size_t len = strlen(s) + size_;
	if (len > capacity_)
	{
		Reserve(len);
	}
	strcat(str_, s);
	size_ = len;
	return *this;
}
