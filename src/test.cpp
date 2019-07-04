#include "Vector.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "List.h"
#include <list>

using namespace std;

// int 测试
void test1()
{
    Vector<int> arr;
    arr.PushBack(1);
    arr.PushBack(2);
    arr.PushBack(3);
    arr.PushBack(4);
    arr.PushBack(5);

    for (auto i : arr)
    {
        cout << i << endl;
    }
    cout << endl;
    cout << arr.Size() << endl;
    cout << arr.Capacity() << endl;

}
// string 测试

void testString()
{
    Vector<string> str;
    str.PushBack("111111");
    str.PushBack("222222");
    str.PushBack("333333");
    str.PushBack("444444");
    str.PushBack("555555");

    cout << *str.Erase(str.begin()) << endl;

    for (auto i : str)
    {
        cout << i << endl;
    }
    cout << endl;
    cout << str.Size() << endl;
    cout << str.Capacity() << endl;
}

void nativeTest()
{
    std::vector<string> str;
    str.push_back("111111");
    str.push_back("222222");
    str.push_back("333333");
    str.push_back("444444");
    str.push_back("555555");

    cout << *str.erase(str.begin()) << endl;

    for (auto i : str)
    {
        cout << i << endl;
    }
    cout << endl;
    cout << str.size() << endl;
    cout << str.capacity() << endl;
}

void listTest()
{
    List<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_back(4);
    li.push_back(5);
    li.push_back(6);
    li.push_back(7);

    for(auto t : li)
        cout << t << " ";
    cout << endl;

    li.pop_back();
    li.pop_front();

    for(auto t : li)
        cout << t << " ";
    cout << endl;

    li.push_front(9);
    li.push_front(10);
    li.push_front(11);

    for(auto t : li)
        cout << t << " ";
    cout << endl;
}

void listTest1()
{
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    l.push_back(7);

    l.resize(10);
    cout << l.size() << endl;
    for (auto t : l)
        cout << t << " ";
    cout << endl;
}

void listTest2()
{
    List<int> sd;
    sd.push_back(1);
    sd.push_back(3);
    sd.push_back(4);
    sd.insert(++sd.begin(), 2);
    for (auto t : sd)
        cout << t << " ";
    cout << endl;

}

int main()
{
//    listTest();
//    listTest1();
    listTest2();
    return 0;
}
