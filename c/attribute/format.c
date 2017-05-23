#include <stdio.h>

int my_printf(int a, const char* format, ...) __attribute__((format (printf, 2 ,3)));
int main()
{
    my_printf(10, "test id: %d\n", 100);
    my_printf(10, "test id: %s %s\n", 100);

    return 0;
}

int my_printf(int a, const char* format, ...)
{

    return 10;
}
