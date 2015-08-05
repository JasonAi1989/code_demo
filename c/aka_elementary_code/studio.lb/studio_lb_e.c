/* endian type get */

#include <stdio.h>

int main(int argc, char**argv)
{
    int edata = 0x44332211;
    
    if(*(3+(char *)&edata) == 0x44)
    {
        printf("little-endian\n");
    }
    else
    {
        printf("big-endian\n");
    }
    
    return 0;
}
