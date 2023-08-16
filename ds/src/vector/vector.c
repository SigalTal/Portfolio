/*********************************
 * Reviewer:            
 * Author: Sigal Tal       
 * File: vector.c          
 * ******************************/
#include <stddef.h>/*size_t*/
#include <stdlib.h>/*malloc - free - realloc*/
#include <string.h>/*memcpy*/
#include <assert.h>
#include "vector.h"

#define FACTOR 2

struct vector
{
    char* vector;
    size_t element_size;
    size_t capacity;
    size_t size;
};


vector_t *VectorCreate(size_t capacity, size_t element_size)
{
    vector_t *vector_ptr=(vector_t *)malloc(sizeof(vector_t));
    if(!vector_ptr)
    {
        return NULL;
    }
    vector_ptr->vector=(char *)malloc(capacity*element_size);
    if(!vector_ptr->vector)
    {
        free(vector_ptr);
        return NULL;
    }
    vector_ptr->element_size=element_size;
    vector_ptr->capacity=capacity;
    vector_ptr->size=0;

    return vector_ptr;
}

void VectorDestroy(vector_t *vector_ptr)
{
    assert(vector_ptr);

    free(vector_ptr->vector); 
    vector_ptr->vector=NULL;
    vector_ptr->element_size=0;
    vector_ptr->capacity=0;
    free(vector_ptr);
}

int VectorPush(vector_t *vector_ptr, void *element_to_push)
{
    assert(vector_ptr);
    assert(element_to_push);

    if(vector_ptr->size==vector_ptr->capacity)
    {
        if(VectorReserve(vector_ptr,vector_ptr->capacity*FACTOR))
        {
            return 1;
        }

    }

    memcpy((vector_ptr->vector)+(vector_ptr->size*vector_ptr->element_size),
		element_to_push,
		vector_ptr->element_size);

    ++vector_ptr->size;

    return 0;
}

void VectorPop(vector_t *vector_ptr)
{
    assert(vector_ptr);

     --vector_ptr->size;
}

int VectorIsEmpty(vector_t *vector_ptr)
{
    assert(vector_ptr);

    return (!vector_ptr->size);
}

size_t VectorSize(vector_t *vector_ptr)
{
    assert(vector_ptr);

    return vector_ptr->size;
}

size_t VectorCapacity(vector_t *vector_ptr)
{
    assert(vector_ptr);

    return vector_ptr->capacity;
}

void *VectorGetAccess(vector_t *vector_ptr, int index)
{
    assert(vector_ptr);

    return (void *)(vector_ptr->vector+index*(vector_ptr->element_size));
}

int VectorShrinkToFit(vector_t *vector_ptr)
{
    assert(vector_ptr);

    vector_ptr->vector=(char *)realloc(vector_ptr->vector,vector_ptr->size*vector_ptr->element_size);
    if(!vector_ptr->vector)
    {
        free(vector_ptr);
        return 1;
    }

    vector_ptr->capacity=vector_ptr->size;

    return 0;/*VectorReserve(vector_ptr,vector_ptr->size)*/
}

int VectorReserve(vector_t *vector_ptr, size_t new_capacity)
{
    assert(vector_ptr);

    vector_ptr->vector=(char *)realloc(vector_ptr->vector,new_capacity*vector_ptr->element_size);
    if(!vector_ptr->vector)
    {
        free(vector_ptr);
        return 1;
    }

    vector_ptr->capacity=new_capacity;

    return 0;
}
