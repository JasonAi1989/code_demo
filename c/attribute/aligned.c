#include <stdio.h>

typedef struct __attribute__((aligned(8)))
{
    char a;
}my_char;

int main()
{
    printf("size: %d\n", sizeof(my_char));

    return 0;
}
