#include <iostream>
#include <string>

int func1()
{
    static int x=99;
    return x;
}
int& func2()
{
    static int x=100;
    return x;
}
int* func3()
{
    static int x=101;
    return &x;
}
std::string func4()
{
    std::string x("func4");
    return x;
}

void process_value(int& i)
{
    std::cout<<"left value, i:"<<i<<std::endl;
}
void process_value(int&& i)
{
    std::cout<<"right value, i:"<<i<<std::endl;
}
void process_str_value(std::string& i)
{
    std::cout<<"left value, i:"<<i<<std::endl;
}
void process_str_value(std::string&& i)
{
    std::cout<<"left value, i:"<<i<<std::endl;
}
int main(int argc, char const* argv[])
{
    int a = 42;
    int b = a;
    int c = a * b;
    int* p = &a;
    int& ref=a;
    std::string s("aizhaoyu");

    std::cout<<"a:"<<a<<std::endl;
    std::cout<<"b:"<<b<<std::endl;
    std::cout<<"p:"<<p<<std::endl;
    std::cout<<"*p:"<<*p<<std::endl;
    std::cout<<"ref:"<<ref<<std::endl;
    std::cout<<"str:"<<s<<std::endl;

    process_value(a);  //left value
    process_value(func2()); //left value
    process_value(*func3()); //left value

    /*If there doesn't define the && function, below two calling will be raised compiling error*/
    process_value(func1()); //right value
    process_value(10);  // right value

    process_str_value(s); // left value
    process_str_value(func4());  //left value

    //raise compile error: lvalue required as left operand of assignment
    //func1() = a;

    //those could be passed in compiling
    func2() = a;
    *func3() = a;
    func4() = s;

    /*Note:
     * The normal variable, pointer, reference is the left value.
     * The constant 42 is the right value.
     * The expression result of (a*b) is the right value, but variable 'c' is the lvalue.
     * The return value of func1 is lvalue; but the return value of func2, func3 and func4 is rvalue.
     * Actually, I have a little doubt why the func4 return a right value???
     *
     * In my new opinion, the func1 reuturn a duplication of x, no matter whether the x is static or not,
     * so it is the left vaule. But for func2 and func3, the return value isn't the duplication, so it is
     * right value. However, regarding the func4...*/

    return 0;
}
