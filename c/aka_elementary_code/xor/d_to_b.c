#include <stdio.h>

int d_to_b(int x);

int main(int argc, const char *argv[])
{
    int x;

    printf("please input the number\n");
    while (!scanf("%d",&x))
        printf("error\n");
    printf("binary:");
    d_to_b(x);
    printf("\n");

    return 0;
}

int d_to_b(int x)
{
    int i;
    int y;
    int flag = 0;
    for (i=31;i>=0;i--)
    {   y = ((x>>i) & 1);
        if (y==1)
            flag=1;
        if (flag ==1 )
            printf("%d",y);
    }
    return 0 ;
}
