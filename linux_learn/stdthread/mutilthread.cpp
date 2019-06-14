#include <thread>
#include <list>
#include <iostream>

class mutilthread
{
private:
    std::list<int> list_;
public:
    void in()
    {
        for (int i = 0; i < 10000; i++)
        {
            
        }
        
    }
    void out()
    {

    } 
};

void myprint()
{
    std::cout << "线程ID: " << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::cout << std::this_thread::get_id() << std::endl;
    std::thread t(myprint);
    std::cout << "从外获取线程ID：" << t.get_id() << std::endl;
    t.join();
    return 0;
}