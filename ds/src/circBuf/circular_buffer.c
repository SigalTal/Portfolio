/*********************************
 * Reviewer: 
 * Author: Sigal Tal
 * File Name: circular_buffer.h
 * ******************************/
#include <stddef.h>/*size_t*/
#include <assert.h>
#include <stdlib.h>/*malloc - free*/
#include "circular_buffer.h"

struct circular_buffer
{
    size_t capacity;
    size_t read_index;
    size_t size;
    char arr[1];
};

circ_buff_t *CircBuffCreate(size_t capacity)
{
    circ_buff_t *c_buff=(circ_buff_t *)malloc(sizeof(circ_buff_t)
                                                +capacity-sizeof(char)*8);
    if(!c_buff)
    {
        return NULL;
    }

    c_buff->capacity=capacity;
    c_buff->read_index=0;
    c_buff->size=0;

    return c_buff;
}

void CircBuffDestroy(circ_buff_t *c_buff)
{
    assert(c_buff);
    c_buff->capacity=0;
    c_buff->read_index=0;
    c_buff->size=0;
    free(c_buff);
    c_buff=NULL;
}

size_t CircBuffBufSiz(const circ_buff_t *c_buff)
{
    assert(c_buff);
    return c_buff->capacity;
}

size_t CircBuffFreeSpace(const circ_buff_t *c_buff)
{
    assert(c_buff);
    return (c_buff->capacity)-(c_buff->size);
}

int CircBuffIsEmpty(const circ_buff_t *c_buff)
{
    assert(c_buff);
    return !c_buff->size;
}

ssize_t CircBuffRead(circ_buff_t *c_buff, void *stream, size_t count)
{
    size_t i=0;
    size_t bytes_to_read=(c_buff->size<count?c_buff->size:count);
    size_t read_index=c_buff->read_index%c_buff->capacity;

    assert(c_buff);
    assert(stream);

    for(i=0;i<bytes_to_read;++i)
    {
        *((char *)(stream)+i)=*(c_buff->arr+read_index);
        read_index=(read_index+1)%c_buff->capacity;
    }

    c_buff->read_index=read_index;

    c_buff->size-=bytes_to_read;

    return bytes_to_read;
}

ssize_t CircBuffWrite(circ_buff_t *c_buff, const void *stream, size_t count)
{
    size_t i=0;
    size_t bytes_to_write=(CircBuffFreeSpace(c_buff)<count?
                            CircBuffFreeSpace(c_buff):count);
    size_t write_index=(c_buff->read_index+c_buff->size)%c_buff->capacity;

    assert(c_buff);
    assert(stream);
    for(i=0;i<bytes_to_write;++i)
    {
       *(c_buff->arr+write_index)=*((char *)(stream)+i);
        write_index=(write_index+1)%(c_buff->capacity);

    }

    c_buff->size+=bytes_to_write;

    return bytes_to_write;
}

