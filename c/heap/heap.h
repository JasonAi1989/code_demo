#ifndef __HEAP__
#define __HEAP__

typedef struct{
    unsigned int key;
    void *event;
}node_t;

typedef struct{
    node_t *heap;
    int number;
    int total_num;
}heap_manager_t;

heap_manager_t* create_heap(unsigned int total_num);
node_t* heap_pop(heap_manager_t *m);
int heap_push(heap_manager_t *m, node_t *n);

#define LEFT(i)     ((i+1)*2-1)
#define RIGHT(i)    ((i+1)*2)
#define PARENT(i)   ((i-1)/2)
#define SWAP(array, i, j)   { \
        unsigned int key=array[i].key; \
        void* p = array[i].event; \
        array[i].key = array[j].key; \
        array[j].key = key;  \
        array[i].event = array[j].event; \
        array[j].event = p;}

#endif
