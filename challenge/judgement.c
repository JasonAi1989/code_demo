#include <stdio.h>

int func(int a, int b)
{
    int ret=a>b;
    return ret*a+(!ret)*b;
}
int main()
{
    printf("big:%d\n", func(10, 20));
    printf("big:%d\n", func(-10, -20));
    printf("big:%d\n", func(10, -20));
    printf("big:%d\n", func(-10, 20));

    printf("big:%d\n", func(20, 10));
    printf("big:%d\n", func(-20, -10));
    printf("big:%d\n", func(20, -10));
    printf("big:%d\n", func(-20, 10));

	return 1;
}
