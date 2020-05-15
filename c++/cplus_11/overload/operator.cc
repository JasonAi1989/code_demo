#include "operator.h"

#include <iostream>

using namespace std;

MyTest::MyTest(int a)
{
    data = a;
}
MyTest::MyTest(const MyTest& m)
{
    data = m.data;
}
MyTest MyTest::operator+(const MyTest &a)
{
    MyTest b(data + a.data);
    return b;
}

int main(void)
{
    MyTest a(10);
    MyTest b(12);
    MyTest c = a;
    MyTest d = b + a;

    cout<<"a:"<<a.GetData()<<endl;
    cout<<"b:"<<b.GetData()<<endl;
    cout<<"c:"<<c.GetData()<<endl;
    cout<<"d:"<<d.GetData()<<endl;

    return 0;
}
