#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>

#include"heap.h"

static void head2tail(node_t *queue, int last)
{
//    printf("%s\n", __func__);
    if(!queue || last < 0)
        return;

    int i=0;
    int l,r,largest;

    while(i<last)
    {
        l = LEFT(i);
        r = RIGHT(i);

        if(l < last && queue[l].key > queue[i].key)
            largest = l;
        else if(r < last && queue[r].key > queue[i].key)
            largest = r;
        else
            largest = i;

        if(largest != i)
        {
            SWAP(queue, largest, i);
            i = largest;
        }
        else
            break;
    }
}
static void tail2head(node_t *queue, int last)
{
//    printf("%s\n", __func__);
    if(!queue || last < 0)
        return;

    int i;
    for(i=last; i>0 && queue[PARENT(i)].key < queue[i].key; i=PARENT(i))
    {
        SWAP(queue, i, PARENT(i));
    }
}

heap_manager_t* create_heap(unsigned int total_num)
{
    if(total_num == 0)
        return NULL;

    unsigned int len = total_num*sizeof(node_t);
    heap_manager_t *m = malloc(sizeof(heap_manager_t));
    if(m == NULL)
        return NULL;

    bzero(m, sizeof(heap_manager_t));
    m->heap = malloc(len);
    if(m->heap == NULL)
    {
        free(m);
        return;
    }

    m->number=0;
    m->total_num=total_num;

    return m;
}

node_t* heap_pop(heap_manager_t *m)
{
 //   printf("%s\n", __func__);
    if(!m)
        return NULL;
    if(m->number == 0)
        return NULL;

    node_t *n=malloc(sizeof(node_t));
    bzero(n, sizeof(n));

    n->key = m->heap[0].key;
    n->event = m->heap[0].event;

    memcpy(&m->heap[0], &m->heap[m->number-1], sizeof(node_t));
    bzero(&m->heap[m->number-1], sizeof(node_t));
    m->number--;

    head2tail(m->heap, m->number-1);
    return n;
}


int heap_push(heap_manager_t *m, node_t *n)
{
//    printf("%s\n", __func__);
    if(!m || !n)
        return -1;
    if(m->number == m->total_num)
        return 0;

    m->heap[m->number].key = n->key;
    m->heap[m->number].event = n->event;
    m->number++;

    tail2head(m->heap, m->number-1);
    return 0;
}
