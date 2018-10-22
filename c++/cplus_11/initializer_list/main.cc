#include <iostream>
#include <vector>
#include <string>

void func1(std::initializer_list<int> list)
{
    std::vector<int> v(list);
    for(auto i:v)
        std::cout<<"vector:"<<i<<std::endl;
    for(auto i:list)
        std::cout<<"input list:"<<i<<std::endl;
}

struct MyType{
    std::string s;
    int n;
};
MyType func2()
{
    return {"aizhaoyu", 10};
}
int main(int argc, char const* argv[])
{
    func1({1,2,3,4,5,6,7,8,9});
    MyType x=func2();
    std::cout<<"name:"<<x.s<<" age:"<<x.n<<std::endl;
    return 0;
}
