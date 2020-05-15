#pragma once

class MyTest
{
public:
    MyTest(int a);
    MyTest(const MyTest& m);
    MyTest operator+(const MyTest &a);

    int GetData(){return data;}

private:
    int data;
};
