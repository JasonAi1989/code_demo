#include <stdio.h>


void func1(int a, int *b)
{
    *b = a *a;
    return;
}

int main(int argc, char const* argv[])
{
    printf("start main\n");

    int a =10;
    int b=0;
    func1(a, &b);
    printf("b=%d\n", b);

    return 0;
}
