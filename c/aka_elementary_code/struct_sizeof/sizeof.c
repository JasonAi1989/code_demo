#include <stdio.h>

int main(int argc,char *argv[])
{
    typedef struct node{
        int n;
        char ch;
        char c;
        short m;
        float f;
        char p;
        char q;
        char s[6];
        int a[4];
    }Node,*PNode;

    printf("%d\n",sizeof(Node));
    printf("%d\n",sizeof(PNode));

    return 0;
}
