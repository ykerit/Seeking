// #include <iostream>
// #include <stdio.h>
// #include <vector>
// #include "String.hpp"
// #include "class.hpp"
// #include "../data_struct/seq_list/seq_list.h"

// using namespace std;

// class B
// {
// private:
//     int data;

// public:
//     B()
//     {
//         cout << "defalue" << endl;
//     }
//     B(int a) : data(a)
//     {
//         cout << "anothrea" << endl;
//     }
//     ~B()
//     {
//         cout << "destory" << endl;
//     }
//     int getData()
//     {
//         data = 1;
//         return data;
//     }
// };

// B play(B b)
// {
//     return b;
// }

// void TestString()
// {
//     String s("hello");
//     cout << s.Str() << endl;
//     cout << s.Capacity() << endl;
//     cout << s.Size() << endl;
//     String s1(s);
//     String s2("nihao");
//     s2 = s;
//     cout << "----------" << endl;
//     cout << s2.Capacity() << endl;
//     cout << s2.Size() << endl;
//     cout << s2.Str() << endl;
// }

// class TestClass1
// {
// public:
//     virtual void play()
//     {
//         cout << "base" << endl;
//     }
//     TestClass1()
//     {
//         play();
//     }
//     ~TestClass1()
//     {
//         play();
//     }
// };

// class TestClass2 : public TestClass1
// {
// public:
//     void play()
//     {
//         cout << "dived" << endl;
//     }
//     TestClass2()
//     {
//         play();
//     }
//     ~TestClass2()
//     {
//         play();
//     }
// };

// void TestClass()
// {
//     // 继承
//     // class1::Student s;
//     // class1::Teacher t;
//     // s.Print();
//     // t.Print();

//     using namespace class2;
//     Student sins;
//     // 派生类赋值给父类对象/ 指针/ 引用
//     Person pins = sins;
//     Person *ppins = &sins;
//     Person &rpins = sins;

//     // 基类对象不能赋值给派生类对象
//     // sins = pins;
//     // 基类的指针可以通过强制类型转换赋值给派送类的指针
//     Student *psins1 = (Student *)ppins;
//     psins1->No_ = 10;

//     ppins = &pins;
// }

// class Test
// {
// public:
//     Test()
//     {
//         cout << "create" << endl;
//     }
//     void foo()
//     {
//         delete this;
//     }
// };
// void gen(int number)
// {

// }

// int yang(int number, int index)
// {
//     if(index == 1 || k == number*2-1)
//         return 1;
//     if(k < 1 || k > number*2 -1)
//         return 0;
//     else
//         return yang(number-1, index-2)+yang(number-1, index-1)+yang(number, index);

// }

// vector<vector<int>> v;
//         v.resize(number);
//         for (int i = 0; i < number; i++)
//         {
//             v[i].resize(2 * i + 1, 1);
//         }
//         for (int i = 2; i < number; i++)
//         {
//             for (int j = 1; j < v[i].size() - 1; j++)
//             {
//                 v[i][j] = v[i - 1][j - 1] + v[i - 1][j] + v[i - 1][j + 1];
//             }
//         }
//         for (auto i : v)
//         {
//             for (auto j : i)
//             {
//                 cout << j << " ";
//             }
//             cout << "\n";
//         }
//         for (int i = 0; i < v[number].size(); i++)
//         {
//             if (i % 2 == 0)
//             {
//                 cout << (i + 1) << endl;
//                 break;
//             }
//         }

// int main()
// {
//     int n;
//     while (cin >> n)
//     {
//         if (n == 1 || n == 2) //判断是1还是2
//             cout << -1 << endl;
//         else
//         {
//             if (n % 2 == 0) //判断偶数
//             {
//                 if (n % 4 == 0)
//                 {
//                     cout << 3 << endl;
//                 }
//                 else
//                 {
//                     cout << 4 << endl;
//                 }
//             }
//             if (n % 2 == 1) //判断奇数
//             {
//                 cout << 2 << endl;
//             }
//         }
//     }
//     return 0;
// }
#include "Vector.hpp"
#include <iostream>
#include <string>
#include <vector>

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

int main()
{
    // test1();
    testString();
    // nativeTest();
    return 0;
}
