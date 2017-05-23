#include <stdio.h>

typedef struct
{
    char a;
    int b;
    char c;
}my_packed_origin;

typedef struct __attribute__ ((packed))
{
    char a;
    int b;
    char c;
}my_packed;

int main()
{
    printf("size:%d\n", sizeof(my_packed_origin));
    printf("size:%d\n", sizeof(my_packed));

    return 0;
}
