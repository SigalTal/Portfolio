/*********************************
 * Reviewer: Sivan            
 * Author: Sigal Tal       
 * File: stack.c          
 * ******************************/

#include <stddef.h>/*size_t*/
#include <stdlib.h>/*malloc - free*/
#include <string.h>/*memcpy*/
#include <assert.h>
#include <stdio.h>
#include "stack.h"

struct stack
{
    char* stack;
    size_t element_size;
    size_t capacity;
    size_t size;
};


stack_t *StackCreate(size_t capacity, size_t  element_size)
{
    stack_t *stack_ptr=(stack_t *)malloc(sizeof(stack_t));
    if(!stack_ptr)
    {
        return NULL;
    }
    stack_ptr->stack=(char *)malloc(capacity*element_size);
    if(!stack_ptr->stack)
    {
        free(stack_ptr);
        return NULL;
    }
    stack_ptr->element_size=element_size;
    stack_ptr->capacity=capacity;
    stack_ptr->size=0;

    return stack_ptr;
}

void StackDestroy(stack_t *stack_ptr)
{
    assert(stack_ptr);

    free(stack_ptr->stack);
    stack_ptr->stack=NULL;
    stack_ptr->element_size=0;
    stack_ptr->capacity=0;
    stack_ptr->size=0;
    free(stack_ptr);
    stack_ptr=NULL;
   
}

void StackPop(stack_t *stack_ptr)
{
    assert(stack_ptr);
    --stack_ptr->size;
}

void StackPush(stack_t *stack_ptr, void *element_to_push)
{
     assert(stack_ptr);
     assert(element_to_push);

     memcpy((stack_ptr->stack)+(stack_ptr->size*stack_ptr->element_size),element_to_push,stack_ptr->element_size);

     ++stack_ptr->size;
}

void StackPeek(stack_t *stack_ptr, void *store_element)
{
    assert(stack_ptr);

    memcpy(store_element,(stack_ptr->stack)+((stack_ptr->size-1)*stack_ptr->element_size),stack_ptr->element_size);

}

size_t StackSize(stack_t *stack_ptr)
{
    assert(stack_ptr);

    return stack_ptr->size;
}

size_t StackCapacity(stack_t *stack_ptr)
{
    assert(stack_ptr);

    return stack_ptr->capacity;
}

int StackIsEmpty(stack_t *stack_ptr)
{
    assert(stack_ptr);

    return (!stack_ptr->size);

}
