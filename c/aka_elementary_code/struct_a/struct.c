#include <stdio.h>
#include <stdlib.h>
#define DEBUG

typedef struct node{
    int a;
    char b;
    char *c;
}Node,*PNode;

int main(int argc,char *argv[])
{
#ifdef DEBUG
    Node p;

    p.a=1;
    p.b='a';
    p.c="hello";
    printf("p.a=%d\n",p.a);
    printf("p.b=%c\n",p.b);
    printf("p.c=%s\n",p.c);
#else
    PNode p=(PNode)malloc(sizeof(Node));

    p->a=1;
    p->b='a';
    p->c="hello";
    printf("p->a=%d\n",p->a);
    printf("p->b=%c\n",p->b);
    printf("p->c=%s\n",p->c);
    free(p);

#endif
    return 0;
}


