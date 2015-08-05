#include <stdio.h>
#define DEBUG_

#ifdef DEBUG
char *func()
{
    char a[]="hello";

    return (a);
}

#else
char *func()
{
    char *p="hello";

    return p;
}
#endif

int main(int argc,char *argv[])
{
    printf("%s\n",func());

    return 0;
}
