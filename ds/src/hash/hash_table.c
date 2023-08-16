/*********************************
 * Reviewer: 
 * Author: 
 * File Name: hash_table.c
 * ******************************/

#include <stdlib.h>/*malloc - free*/
#include <assert.h>
#include "dll.h"
#include "hash_table.h"

#define NODE_SIZE sizeof(node_hash_t);
static void DListDestroyTillIndex(hash_t *hash,size_t faild_index);
static size_t FindIndex(hash_t *hash, const void *data);
static dll_iterator_t FindIterator(hash_t *hash, const void *data);

typedef struct node_hash
{
    dll_t *list;

}node_hash_t;

struct hash
{
    size_t table_size;
    hash_is_match_t is_match_func;
    hash_func_t hash_func;
    node_hash_t list_arr[1]; /*flexible array*/
};

hash_t *HashCreate(hash_is_match_t is_match_func, hash_func_t hash_func,size_t table_size)
{
    hash_t *hash=NULL;
    size_t i=0;

    assert(is_match_func);
    assert(hash_func);
    
    hash=malloc(offsetof(hash_t,list_arr)+table_size*sizeof(node_hash_t));
    if(!hash)
    {
        return NULL;
    }

    hash->table_size=table_size;
    hash->is_match_func=is_match_func;
    hash->hash_func=hash_func;

    for(i=0; i<table_size; ++i)
    {
        if(!((hash->list_arr+i)->list=DListCreate()))
        {
            DListDestroyTillIndex(hash,i);
            return NULL;
        }
    }
    
    return hash;
}

static void DListDestroyTillIndex(hash_t *hash,size_t faild_index)
{
    size_t i=0;
    for(i=0; i<faild_index;++i)
    {
        DListDestroy((hash->list_arr+i)->list);
    }
    hash->table_size=0;
    hash->is_match_func=NULL;
    hash->hash_func=NULL;
    free(hash);
    hash=NULL;
}

int HashIsEmpty(hash_t *hash)
{
    size_t i=0;
    dll_t *curr_list=NULL;

    assert(hash);

    curr_list=(hash->list_arr)->list;

    for(i=0; i<hash->table_size && DListIsEmpty(curr_list); ++i)
    {
        curr_list=(hash->list_arr+i)->list;
    }

    return DListIsEmpty(curr_list);
}

void HashDestroy(hash_t *hash)
{
    DListDestroyTillIndex(hash,hash->table_size);
    hash=NULL;
}

int HashInsert(hash_t *hash, const void *data)
{
    size_t index=0;

    assert(hash);
    assert(data);

    index=FindIndex(hash, data);

    if(!(DListInsert((hash->list_arr+index)->list,DListBegin((hash->list_arr+index)->list),(void *)data)))
    {
        return 1;
    }

    return 0;
}

static size_t FindIndex(hash_t *hash, const void *data)
{
    
    size_t index=hash->hash_func((void *)data);

    if(index>=hash->table_size)
    {
        index = index % hash->table_size;
    }

    return index;

}

void *HashFind(hash_t *hash, const void *data)
{

    assert(hash);
    assert(data);

    return DListGetData(FindIterator(hash, data));
}

static dll_iterator_t FindIterator(hash_t *hash, const void *data)
{
    dll_t *curr_list=NULL;
    size_t index=0;

    assert(hash);
    assert(data);

    index=FindIndex(hash, data);

    curr_list=(hash->list_arr+index)->list;

    return DListFind(DListBegin(curr_list),DListEnd(curr_list),data,hash->is_match_func);
}

int HashForEach(hash_t *hash, hash_action_func_t action_func, void *param)
{
    size_t i=0;
    dll_t *curr_list=NULL;
    int action_res=0;

    assert(hash);
    assert(action_func);

    for(i=0; i<hash->table_size && !action_res; ++i)
    {
        curr_list=(hash->list_arr+i)->list;
        action_res=DListForEach(DListBegin(curr_list),DListEnd(curr_list),param,action_func);    
    }

    return action_res;
}

static int Size(void *hash_data, void *user_param)
{
    assert(hash_data);
    assert(user_param);

    ++*(size_t *)user_param;

    return 0;

}

size_t HashSize(hash_t *hash)
{
    size_t size=0;

    assert(hash);

    HashForEach(hash, Size, &size);

    return size;
}

void HashRemove(hash_t *hash, void *data)
{
    assert(hash);
    assert(data);

    DListRemove(FindIterator(hash, data));

}
