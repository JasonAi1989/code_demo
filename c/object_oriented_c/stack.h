#ifndef __STACK_H__
#define __STACK_H__

typedef struct my_stack_t my_stack_t;
struct my_stack_t {

    /**
     ** Method "push" with one parameter and no return value
     **
     ** @param i    element to push
     **/
    void (*push)(my_stack_t *this, int i);

    /**
     ** Method "add" with no parameters and no return value
     **/
    void (*add)(my_stack_t *this);

    /**
     ** Method "pop" with no parameters (except "this") and a return value
     **
     ** @return    popped element
     **/
    int (*pop)(my_stack_t *this);

};

/**
 ** Constructor
 **
 ** @return    instance of my_stack_t
 **/
my_stack_t *my_stack_create();

#define MAX_STACK_SIZE 32
typedef struct private_my_stack_t private_my_stack_t;
struct private_my_stack_t {

    /**
     ** Public interface
     **/
    my_stack_t public;

    /**
     ** Internal stack items
     **/
    int values[MAX_STACK_SIZE];

    /**
     ** Number of items
     **/
    int stack_size;
};

#endif
