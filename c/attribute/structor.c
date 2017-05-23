#include <stdio.h>

int main()
{
    printf("main\n");

    return 0;
}

void start() __attribute__((constructor));
void end() __attribute__((destructor));

void start()
{
    printf("constructor\n");
}

void end()
{
    printf("destructor\n");
}
