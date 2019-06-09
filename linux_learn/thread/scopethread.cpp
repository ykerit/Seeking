#include <iostream>
#include <thread>

class scopethread
{
private:
    std::thread t_;

public:
    scopethread(std::thread t) : t_(std::move(t))
    {
        if (!t_.joinable())
        {
            throw std::logic_error("No thread");
        }
    }
    ~scopethread()
    {
        t_.join();
    }
    scopethread(const scopethread &) = delete;
    scopethread &operator=(const scopethread &) = delete;
};

int main()
{
    std::cout << std::thread::hardware_concurrency() << std::endl;
}