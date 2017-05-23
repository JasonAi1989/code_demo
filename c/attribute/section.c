#include<stdio.h>
int test[10] __attribute__((section("TEST"))) = {0};
int main()
{
    printf("hello world\n");

    return 0;
}
