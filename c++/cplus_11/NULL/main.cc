#include <iostream>

void foo(void* a)
{
    std::cout<<"char*"<<std::endl;
}
void foo(int)
{
    std::cout<<"int"<<std::endl;
}

int main(int argc, char const* argv[])
{
    foo(NULL);
    return 0;
}
