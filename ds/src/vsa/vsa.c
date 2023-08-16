/*********************************
 * Reviewer: 
 * Author: Sigal
 * File Name: vsa.c
 * ******************************/
#include <stdio.h>
#include <assert.h>
#include "vsa.h"

#define WORD_SIZE sizeof(size_t)

#define META_SIZE (size_t)align(sizeof(meta_data_t), WORD_SIZE)

struct vsa
{
    size_t al_pool_size;
};

typedef struct meta_data
{
    size_t meta_data;

    #ifndef NDEBUG
    void *magic;
    #endif

}meta_data_t;

static void* align(size_t what, size_t to);
static size_t SizeOfVSA(void);
static void SetFlagOn(meta_data_t *md);
static void SetFlagOff(meta_data_t *md);
static void *Defragmentaion(vsa_t *vsa, size_t variable_size);
static int IsSetON(meta_data_t *md);



vsa_t *VSAInit(void *pool, size_t pool_size)
{
    vsa_t *vsa=NULL;

    meta_data_t *md=NULL;

    assert(pool);

    if(pool_size<SizeOfVSA()+((size_t)align((size_t)pool,WORD_SIZE)-(size_t)pool)+META_SIZE+WORD_SIZE)
    {
        return NULL;
    }

    vsa=align((size_t)pool,WORD_SIZE);
    pool_size=pool_size-((size_t)vsa-(size_t)pool)-SizeOfVSA();
    vsa->al_pool_size=pool_size;
    vsa->al_pool_size &=~(WORD_SIZE-1);

    md=(meta_data_t *)((char *)vsa+SizeOfVSA());
    md->meta_data=vsa->al_pool_size-META_SIZE;

    #ifndef NDEBUG
    md->magic=(void *)8;
    #endif

    return vsa;
}


void *VSAAlloc(vsa_t *vsa, size_t variable_size)
{
    meta_data_t *block=NULL;
    meta_data_t* remainder_meta_data=NULL;

    assert(vsa);

    variable_size=(size_t)align(variable_size, WORD_SIZE);

    if(!(block=Defragmentaion(vsa, variable_size)))
    {
        return NULL;
    }

    if(block->meta_data>=variable_size+META_SIZE)
    {
        remainder_meta_data = (meta_data_t*)((char *)block+META_SIZE+variable_size); 
        remainder_meta_data->meta_data=block->meta_data-META_SIZE-variable_size;

        #ifndef NDEBUG
        remainder_meta_data->magic=(void *)8;
         #endif

        block->meta_data=variable_size;
    }
    
    SetFlagOn(block);
    return ((char *)block+META_SIZE);
}



void VSAFree(void *block)
{
    meta_data_t* meta_data = NULL;
    
    assert(block);

    meta_data = (meta_data_t*)((char*)block - META_SIZE);

    assert((void *)8 ==(meta_data->magic));

    SetFlagOff(meta_data);
}


size_t VSALargestChunckAvailable(vsa_t *vsa)
{
    size_t max_chanck=0;
    meta_data_t *block=NULL;
    meta_data_t* end_of_pool=NULL;

    assert(vsa);

    end_of_pool=(meta_data_t *)((char *)vsa+SizeOfVSA()+vsa->al_pool_size);
    block=(meta_data_t *)((char *)vsa+SizeOfVSA());

    Defragmentaion(vsa, vsa->al_pool_size-META_SIZE);

    while(block<end_of_pool)
    {
        if(0==(IsSetON(block) && max_chanck<block->meta_data))
        {
            max_chanck=block->meta_data;
        }

        block=(meta_data_t *)((char *)block+META_SIZE+((block->meta_data)&~(size_t)1));
    }

    return max_chanck;
}


static void *Defragmentaion(vsa_t *vsa, size_t variable_size)
{
    meta_data_t *block=NULL;
    meta_data_t* end_of_pool=NULL;
    meta_data_t* next_block=NULL;

    assert(vsa);

    variable_size=(size_t)align(variable_size, WORD_SIZE);

    end_of_pool=(meta_data_t *)((char *)vsa+SizeOfVSA()+vsa->al_pool_size);
    block=(meta_data_t *)((char *)vsa+SizeOfVSA());

    while(block<end_of_pool && (IsSetON(block) || variable_size>(block->meta_data)))
    {
        next_block=(meta_data_t *)((char *)block+META_SIZE+((block->meta_data)&~(size_t)1));
        if(IsSetON(block))
        {
            block=next_block;
        }
        else if(!IsSetON(block) && (next_block<end_of_pool) && !IsSetON(next_block))
        {
            block->meta_data+=META_SIZE+next_block->meta_data;
        }
        else
        {
            block=next_block;
        }
    }

    if(block>=end_of_pool) 
    {
        return NULL;
    }

    return (void *)block;
}

static size_t SizeOfVSA(void)
{
   return (size_t)align(sizeof(vsa_t),WORD_SIZE); 
}

static void* align(size_t what, size_t to)
{
    return (void*)((what - 1 + to) & -to);
}

static void SetFlagOn(meta_data_t *md)
{
    md->meta_data=md->meta_data|(size_t)1;
}

static void SetFlagOff(meta_data_t *md)
{
    md->meta_data=md->meta_data&~(size_t)1;
}

static int IsSetON(meta_data_t *md)
{
    return ((md->meta_data)&(size_t)1);
}