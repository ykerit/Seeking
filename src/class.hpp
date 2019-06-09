/*
 * @Description: class extends
 * @Author: yker
 * @Date: 2019-05-31 20:52:41
 * @LastEditTime: 2019-05-31 21:29:56
 */

#include <iostream>
#include <string>

namespace class1
{
class Person
{
public:
    void Print()
    {
        std::cout << "name:" << name_ << std::endl;
        std::cout << "age:" << age_ << std::endl;
    }

protected:
    std::string name_ = "peter";
    int age_ = 18;
};

class Student : public Person
{
protected:
    int stuid_;
};

class Teacher : public Person
{
protected:
    int jobid_;
};
} // namespace class1


namespace class2
{
class Person
{
protected:
    std::string name_;
    std::string sex_;
    int age_;
};

class Student : public Person
{
public:
    int No_;
};
} // namespace class2
