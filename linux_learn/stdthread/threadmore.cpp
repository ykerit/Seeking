#include <iostream>
#include <thread>

using namespace std;

class X
{
public:
    void do_lengthy_work(int num);
};

void X::do_lengthy_work(int num)
{
    cout << "is thread" << num << endl;
}

X my_x;

int main()
{
    thread t(&X::do_lengthy_work, &my_x, 5);
    t.join();
    return 0;
}