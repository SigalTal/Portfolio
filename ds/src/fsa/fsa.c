/*********************************
 * Reviewer: 
 * Author: Sigal 
 * File Name: fsa.h
 * ******************************/
#include <stddef.h>/*size_t*/
#include <assert.h>
#include "fsa.h"

#define WORD_SIZE sizeof(size_t)

static void* align(size_t what, size_t to);
static size_t OffsetStruct(void);

struct fsa 
{
    size_t offset_first;
};

fsa_t *FSAInit(void *pool, size_t pool_size, size_t block_size)
{
    fsa_t *fsa=NULL;
    char *block=NULL;
    size_t i=0;

    assert(pool);

    block_size=(size_t)align(block_size, WORD_SIZE);

    if(pool_size<OffsetStruct()+block_size+((size_t)align((size_t)pool, WORD_SIZE)-(size_t)pool))
    {
        return NULL;
    }

    fsa=align((size_t)pool, WORD_SIZE);
    /*printf("fsa: %p\n",(void *)fsa);*/

    /*printf("block_size: %lu\n",block_size);*/
    fsa->offset_first=0;

    pool_size=pool_size-((size_t)fsa-(size_t)pool)-OffsetStruct();


    block=(char *)fsa+OffsetStruct();

    while((long)i<=(long)(pool_size-(2*block_size)))
    {
        i+=block_size;
        *(size_t *)block=i;
        block+=block_size;
    }

    *(int *)block=-1;
    /*printf("block: %d",*(int *)block);*/

    return fsa;
}


static void* align(size_t what, size_t to)
{
    return (void*)((what - 1 + to) & -to);
}

static size_t OffsetStruct(void)
{
   return (size_t)align(sizeof(fsa_t),WORD_SIZE); 
}

size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{
    block_size=(size_t)align(block_size, WORD_SIZE);

    return (block_size*num_of_blocks)+(WORD_SIZE-1)+OffsetStruct();
}

void *FSAAlloc(fsa_t *fsa)
{
    size_t offset_first=fsa->offset_first;

    assert(fsa);

    if(-1==(int)(fsa->offset_first))
    {
        return NULL;
    }

    offset_first=fsa->offset_first;

    fsa->offset_first=*(size_t *)((char *)fsa+OffsetStruct()+fsa->offset_first);

    return (char *)fsa+OffsetStruct()+offset_first;

}

void FSAFree(fsa_t *fsa, void *block_address)
{
    assert(fsa);
    assert(block_address);

    *(size_t *)block_address=fsa->offset_first;
    fsa->offset_first=(size_t)((char *)block_address-(((char *)fsa)+OffsetStruct()));
}

size_t FSACountFree(fsa_t *fsa)
{
    size_t count=0;

    size_t offset_first=fsa->offset_first;

    assert(fsa);

    while((-1)!=(int)offset_first)
    {
        ++count;

        offset_first=*(size_t *)(((char *)fsa)+OffsetStruct()+offset_first);
    }

    return count;
}
