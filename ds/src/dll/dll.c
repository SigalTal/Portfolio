/*********************************
 * Reviewer:   
 * Author: Sigal Tal		
 * File: dll.h
 * ******************************/
#include <stdlib.h>/*malloc - free*/
#include <assert.h>
#include "dll.h"
static int CountNode(void *list_data, void *param);

struct dll_node
{
    void *data;
    struct dll_node *next;
    struct dll_node *prev;
};

struct dll
{
    dll_iterator_t head;
    dll_iterator_t tail;
};

dll_t *DListCreate(void)
{
    dll_t *dlist=(dll_t *)malloc(sizeof(dll_t));
    if(!dlist)
    {
        return NULL;
    }

    dlist->head=(struct dll_node *)malloc(sizeof(struct dll_node));
    if(!dlist->head)
    {
        free(dlist);
        return NULL;
    }

    dlist->tail=(struct dll_node *)malloc(sizeof(struct dll_node));
    if(!dlist->tail)
    {
        free(dlist->head);
        free(dlist);
        return NULL;
    }

    dlist->head->data=NULL;
    dlist->head->next=dlist->tail;
    dlist->head->prev=NULL;

    dlist->tail->data=NULL;
    dlist->tail->next=NULL;
    dlist->tail->prev=dlist->head;

    return dlist;
}

void DListDestroy(dll_t *dlist)
{
    dll_iterator_t curr=DListBegin(dlist);

    assert(dlist);

    while(!DListIsEmpty(dlist))
    {
        DListRemove(curr);
        curr=DListBegin(dlist);
    }
    curr=NULL;

    free(dlist->head);
    dlist->head=NULL;

    free(dlist->tail);
    dlist->tail=NULL;

    free(dlist);
    dlist=NULL;
}

static int CountNode(void *list_data, void *param)
{
    assert(list_data);
    assert(param);

    (void)list_data;
    *(int *)param+=1;
    
    return 0;
}

size_t DListSize(const dll_t *dlist)
{
    size_t elem_num=0;

    assert(dlist);

    DListForEach(DListBegin(dlist), DListEnd(dlist), &elem_num, CountNode);

    return elem_num;
}

int DListIsEmpty(const dll_t *dlist)
{
    assert(dlist);
    return (DListBegin(dlist)==DListEnd(dlist));
}

dll_iterator_t DListBegin(const dll_t *dlist)
{
    assert(dlist);
    return dlist->head->next;
}

dll_iterator_t DListEnd(const dll_t *dlist)
{
    assert(dlist);
    return dlist->tail;
}

dll_iterator_t DListNext(dll_iterator_t curr)
{
    assert(curr);
    return curr->next;
}

dll_iterator_t DListPrev(dll_iterator_t curr)
{
    assert(curr);
    return curr->prev;
}

int DListIsSameIter(dll_iterator_t first, dll_iterator_t second)
{
    assert(first);
    assert(second);
    return !(first!=second);
}

void *DListGetData(dll_iterator_t curr)
{
    assert(curr);
    return curr->data;
}

dll_iterator_t  DListInsert(dll_t *dlist, dll_iterator_t curr, void *data)
{

    dll_iterator_t new_node=(dll_iterator_t)malloc(sizeof(struct dll_node));
    if(!new_node)
    {
        return dlist->tail;
    }
    assert(dlist);
    assert(curr);
    assert(data);

    new_node->data=data;
    new_node->prev=curr->prev;
    curr->prev=new_node;
    new_node->next=new_node->prev->next;
    new_node->prev->next=new_node;

    return new_node;
}

dll_iterator_t DListRemove(dll_iterator_t curr)
{
    dll_iterator_t next_node=curr->next;
    assert(curr);

    curr->prev->next=curr->next;
    curr->next->prev=curr->prev;

    free(curr);

    return next_node;
}

dll_iterator_t DListPushFront(dll_t *list, void *data)
{
    assert(list);
    assert(data);

    return DListInsert(list,DListBegin(list),data);
}

dll_iterator_t DListPushBack(dll_t *list, void *data)
{
    assert(list);
    assert(data);

    return DListInsert(list,DListEnd(list),data);
}

void *DListPopFront(dll_t *list)
{
    void *data=DListGetData(list->head->next);

    assert(list);

    DListRemove(DListBegin(list));

    return data;
}

void *DListPopBack(dll_t *list)
{
    void *data=DListGetData(DListPrev(DListEnd(list)));

    assert(list);

    DListRemove(DListPrev(DListEnd(list)));

    return data;
}

dll_iterator_t DListFind(
                            dll_iterator_t from, 
                            dll_iterator_t to, 
                            const void *data, 
                            is_match_t func)
{
    assert(from);
    assert(to);
    assert(data);
    assert(func);

    while(!DListIsSameIter(from,to) && 1!=func(DListGetData(from),data))
    {
        from=DListNext(from);
    }

    return from;
}

int DListForEach(
                    dll_iterator_t from, 
                    dll_iterator_t to, 
                    void *param, 
                    action_func_t func)
{
    int flag=0;
    assert(from);
    assert(to);
    assert(func);

    while(!DListIsSameIter(from,to) && 0==flag)
    {
        flag=func(DListGetData(from),param);
        from=DListNext(from);
    }

    return flag;
}

int DListMultiFind(
                    dll_iterator_t from, 
                    dll_iterator_t to, 
                    dll_t *dlist_dest, 
                    const void *data, 
                    is_match_t func)
{
    dll_iterator_t new_from=from;
    assert(from);
    assert(to);
    assert(dlist_dest);
    assert(data);
    assert(func);

    while(from!=to)
    {
        new_from=DListFind(from, to, data, func);
        if(DListIsSameIter(new_from,to))
        {
            break;
        }
        if(!DListPushBack(dlist_dest, DListGetData(new_from)))
        {
            return 1;
        }
        from=DListNext(new_from);
    }

    return 0;
}

dll_iterator_t DListSplice(
                            dll_iterator_t where,
                            dll_iterator_t begin, 
                            dll_iterator_t end)
{
    dll_iterator_t temp_begin=begin->prev;

    assert(where);
    assert(begin);
    assert(end);

    where->prev->next=begin;
    begin->prev=where->prev;

    end->prev->next=where;
    where->prev=end->prev;

    temp_begin->next=end;
    end->prev=temp_begin;

    return DListPrev(where);
}
