#include <stdio.h>

int main(int argc,char *argv[])
{
    int i,a[9];

    for (i=0 ;i<=8 ;i+=2){
        a[i] = i;
        if (i <8 )
            a[i+1] = i+1;
    }
    for (i=0 ;i<=8 ;i++)
        printf("%d\n",a[i]);

    return 0;
}
