#include <stdio.h>

int main(int argc, char const* argv[])
{
    int a[10] = {[0 ... 3]=1, [4 ... 9]=2};
    for(int i=0; i<10; i++)
    {
        printf("a[%d]=%d\n", i, a[i]);
    }

    return 0;
}
