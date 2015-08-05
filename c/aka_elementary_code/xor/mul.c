#include <stdio.h>

int mul(const  int a,const  int b);

int main(int argc, const char *argv[])
{
    int result ;
    int x,y;

again:    printf("please input two number:\n");
    if (2 != scanf("%d %d",&x,&y))
    {
        printf("error\n");
        goto again;
    }

    result = mul(x,y);
    printf("result is %d \n",result);
    return 0;

}

int mul(const signed int x,const signed int y)
{
    int ax,ay;
    int i;
    int flag=0;
    int result = 0;

    if ((x>>31) & 1)
        ax = ~(x - 1);
    else
        ax = x;
    if ((y>>31) & 1)
        ay = ~(y - 1);
    else 
        ay = y;
    if (((x>>31) & 1) ^ ((y>>31) & 1))
        flag = 1;
//        result = 1;
//        result << 31;
    
    for (i= 0;i<31;i++)
        if ((ay>>i & 1))
            result = result + (ax<<i);
    if (flag == 0)
        return result;
    else
        return ~result + 1;
}

