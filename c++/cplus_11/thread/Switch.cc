#include <iostream>

int main(int argc, char const* argv[])
{
    int a=2;
    switch(a)
    {
        case 1:
            /*Can't define the variable here, compile error*/
            //int b=10;
            //std::cout<<b<<std::endl;
            break;
        case 2:
            /*But, we can define the variable in brace*/
            {
                int c=11;
                std::cout<<c<<std::endl;
                break;
            }
        default:
            break;
    }
    return 0;
}
