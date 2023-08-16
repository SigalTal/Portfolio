/*********************************
 * Reviewer:Roy
 * Author: Sigal
 * File Name: heap.c
 * ******************************/
#include <stdlib.h>/*malloc - free*/
#include <assert.h>
#include "heap.h"
#include "vector.h"

static void HeapifyUp(heap_t *heap, int curr_index);
static int ParentIndex(int curr_index);
static void Swap(void **a,void **b);
static void HeapifyDown(heap_t *heap);
static int LeftChildIndex(int curr_index);
static int RightChildIndex(int curr_index);
static size_t HeapFind(heap_t *heap,const void *data,heap_is_match_func_t is_match,void *user_param);

enum child{LEFT,RIGHT};

struct heap
{
    heap_compare_func_t comp_ptr;
    void *user_param;
    vector_t *vector;
};

heap_t *HeapCreate(heap_compare_func_t comp_ptr,void *user_param)
{
    heap_t *heap;

    assert(comp_ptr);

    heap=malloc(sizeof(heap_t));
    if(!heap)
    {
        return NULL;
    }
    heap->comp_ptr=comp_ptr;
    heap->user_param=user_param;
    heap->vector=VectorCreate(10,sizeof(void *));
    if(!heap->vector)
    {
        free(heap);
        heap=NULL;
        return NULL;
    }

    return heap;
}


void HeapDestroy(heap_t *heap)
{
    assert(heap);

    VectorDestroy(heap->vector);
    heap->vector=NULL;

    free(heap);
    heap=NULL;
}

size_t HeapSize(heap_t *heap)
{
    assert(heap);

    return VectorSize(heap->vector);
}

int HeapIsEmpty(heap_t *heap)
{
    assert(heap);

    return VectorIsEmpty(heap->vector);
}

void *HeapPeek(heap_t *heap)
{
    void **peeked;
    assert(heap);
    peeked = (void**)VectorGetAccess(heap->vector,0);
    return *peeked;
}

int HeapPush(heap_t *heap, const void *data)
{
    assert(heap);
    assert(data);

    if(VectorPush(heap->vector, &data))
    {
        return 1;
    }

    HeapifyUp(heap, VectorSize(heap->vector)-1);

    return 0;

}

void HeapPop(heap_t *heap)
{

    void **first_elem=NULL, **last_elem=NULL;

    assert(heap);

    first_elem=VectorGetAccess(heap->vector,0);
    last_elem=VectorGetAccess(heap->vector,VectorSize(heap->vector)-1);

    Swap(first_elem,last_elem);
    VectorPop(heap->vector);

    HeapifyDown(heap);
}

void *HeapRemove(heap_t *heap,const void *data,heap_is_match_func_t is_match,void *user_param)
{
    size_t index_found=0;
    void **last_elem=NULL, **curr=NULL;
    void *data_curr=NULL;

    assert(heap);
    assert(data);
    assert(is_match);

    index_found=HeapFind(heap,data,is_match,user_param);
    if (-1==(long)index_found)
    {
        return NULL;
    }

    curr=(void *)VectorGetAccess(heap->vector,index_found);
    data_curr=*curr;
    last_elem=VectorGetAccess(heap->vector,VectorSize(heap->vector)-1);
    Swap(last_elem,curr);

    VectorPop(heap->vector);

    HeapifyDown(heap);

    return data_curr;
}

/*returns index if found or (-1) if not found*/
static size_t HeapFind(heap_t *heap,const void *data,heap_is_match_func_t is_match,void *user_param)
{
    size_t index=0;
    int match_res=0;
    void **curr=NULL;

    for(index=0;index<VectorSize(heap->vector) && !match_res;++index)
    {
        curr=VectorGetAccess(heap->vector,index);
        match_res = is_match(*curr,data,user_param);
    }

    if(!match_res)
    {
        return -1;
    }

    return index-1;
}

static void HeapifyUp(heap_t *heap, int curr_index)
{
    void **root=NULL, **parent=NULL, **curr=NULL;

    if(!curr_index)
    {
        return;
    }

    root=VectorGetAccess(heap->vector,0);
    curr=VectorGetAccess(heap->vector,curr_index);
    parent=VectorGetAccess(heap->vector,ParentIndex(curr_index));

    while (curr_index != 0 && heap->comp_ptr(*curr,*parent, heap->user_param)==1)
    {
        Swap(parent,curr);
        
        curr_index=ParentIndex(curr_index);
        curr=parent;
        parent= VectorGetAccess(heap->vector,ParentIndex(curr_index));
    }
        
}

static void HeapifyDown(heap_t *heap)
{
    void **child[2]={NULL}, **curr=NULL;
    int direction=0, curr_index=0, left_right[2]={1,2};

    while ((size_t)LeftChildIndex(curr_index)<VectorSize(heap->vector))
    {
        curr=VectorGetAccess(heap->vector,curr_index);
        child[LEFT]=VectorGetAccess(heap->vector,LeftChildIndex(curr_index));
        child[RIGHT]=VectorGetAccess(heap->vector,RightChildIndex(curr_index));

        if((size_t)RightChildIndex(curr_index)<VectorSize(heap->vector))
        {
        direction=heap->comp_ptr(*child[RIGHT],*child[LEFT], heap->user_param)==1;
        } 

        Swap(child[direction],curr);
        curr_index=2*curr_index+left_right[direction];
        direction=0;
    }

    HeapifyUp(heap, curr_index);
}

static int ParentIndex(int curr_index)
{
    return (curr_index-1)/2;
}

static int LeftChildIndex(int curr_index)
{
    return (2*curr_index+1);
}

static int RightChildIndex(int curr_index)
{
    return (2*curr_index+2);
}

static void Swap(void **a,void **b)
{
    void *tmp=*a;
    *a=*b;
    *b=tmp;
}