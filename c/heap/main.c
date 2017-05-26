#include<stdio.h>
#include<stdlib.h>

#include"heap.h"

int main()
{
    int a[]={1000, 20, 11, 3, 44, 5, 23, 45, 234};
    int i;

    heap_manager_t *m=create_heap(50);

    for(i=0; i<sizeof(a)/sizeof(int); i++)
    {
        node_t n = {a[i], NULL};

        heap_push(m, &n);
    }

    for(i=0; i<sizeof(a)/sizeof(int); i++)
    {
        node_t *n = heap_pop(m);
        if(n)
            printf("%d\t", n->key);

        if(n)
            free(n);
    }
    printf("\n");

    return 0;
}

