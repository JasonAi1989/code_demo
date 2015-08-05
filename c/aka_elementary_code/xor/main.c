#include <stdio.h>

char str[1024];

int mul(const signed int x,const signed int y);
int d_to_b(int x);
char * encrypt(char *a);
char * trans(char *a);
int menu(void);

int main(int argc, const char *argv[])
{

    menu();
    return 0;
}

int menu(void)
{
    int ch,num1,num2x,num2y,flag;
    flag = 1;

    while(flag)
    {
    printf("1.decimal to binary\n");
    printf("2.x*y\n");
    printf("3.low or up exchange\n");
    printf("4.encryption\n");
    printf("5.exit\n");
    printf("please choose [1-5] :");
    scanf("%d",&ch);

    switch(ch)
    {
        case 1:
            printf("input a number:");
            scanf("%d",&num1);
            printf("decimal %d chage to binary is ",num1);
            d_to_b(num1);
            printf("\n");
            break;
        case 2:
            printf("please input x y :");
            scanf("%d %d",&num2x,&num2y);
            printf("%d * %d = ",num2x,num2y);
            printf("%d\n",mul(num2x,num2y));
            printf("\n");
            break;
        case 3:
            printf("please input a string : ");
            scanf("%s",str);
            printf("%s\n",trans(str));
            printf("\n");
            break;
        case 4:
            printf("please input a char:");
            scanf("%s",str);
            printf("After encrytion : %s\n",encrypt(str));
            printf("\n");
            break;
        case 5:
            flag =0;
            printf("\n");
            break;
    }
    }

    return 0;
}


//A_to_a
char * trans(char *a)
{   int j;

    for (j=0;a[j] != '\0';j++)
    if (a[j]>='a'&&a[j]<='z'||a[j]>='A'&&a[j]<='Z')
       a[j]=a[j] ^ 0x20;
    return a;

}

//encryption 
char * encrypt(char *a)
{   int j;

    for (j=0;a[j] != '\0';j++)
        a[j]=a[j] ^ 34;
    return a;

}

//d_to_b
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
    printf("\n");
    return 0 ;
}


//mul
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
    for (i= 0;i<31;i++)
        if ((ay>>i & 1))
            result = result + (ax<<i);
    if (flag == 0)
        return result;
    else
        return ~result + 1;
}

