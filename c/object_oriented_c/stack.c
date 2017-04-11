#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "object.h"

METHOD(my_stack_t, push, void,
        private_my_stack_t *this, int i)
{
    this->values[MAX_STACK_SIZE - ++this->stack_size] = i;

}
METHOD(my_stack_t, add, void,
        private_my_stack_t *this)
{
    return ;

}
METHOD(my_stack_t, pop, void,
        private_my_stack_t *this)
{
    return ;
}

my_stack_t *my_stack_create()
{
    private_my_stack_t *this;

    INIT(this,
            .public = {
            .push = _push,
            .add = _add,
            .pop = _pop,

            },
            /* uninitialized fields are automatically set to zero */
        );

    /* return public part */
    return &this->public;

}

int main()
{
    my_stack_t *p = my_stack_create();

    return 0;
}
