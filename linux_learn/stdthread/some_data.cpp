#include <string>
#include <mutex>
#include <iostream>

class some_data
{
private:
    int a;
    std::string b;

public:
    void do_something()
    {
        std::cout << "do something" << std::endl;
    }
};

class data_wrapper
{
private:
    some_data data;
    std::mutex m;

public:
    template <typename Function>
    void process_data(Function func)
    {
        std::lock_guard<std::mutex> l(m);
        func(data);
    }
};

some_data *unprotected;

void malicious_function(some_data &protected_data)
{
    unprotected = &protected_data;
}

data_wrapper x;
void foo()
{
    x.process_data(malicious_function); // 传递恶意函数 对对象进行修改
    unprotected->do_something();        // 在无保护下访问数据
}

