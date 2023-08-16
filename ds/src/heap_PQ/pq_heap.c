/*********************************
 * Reviewer:           
 * Author: Sigal Tal       
 * File: pq_heap.c          
 * ******************************/
#include <stdlib.h>
#include <assert.h>
#include "priority_queue.h"
#include "heap.h"

static int PQIsMatchUID(const void *list_data,const void *data, void *user_param);

struct p_queue
{
    heap_t *heap;
    PQcompare_t priority_func;
    void *user_param;
};

typedef struct pqueue_member
{
    void *data;
    ilrd_uid_t uid;

}pqueue_member_t;

static int pq_compare(const void *data1, const void *data2, void *user_param)
{
    pqueue_member_t *first_data=(pqueue_member_t *)data1;
    pqueue_member_t *second_data=(pqueue_member_t *)data2;
    pri_queue_t *pq = (pri_queue_t *)user_param;

   return pq->priority_func(first_data->data ,second_data->data, pq->user_param);
}

pri_queue_t *PQueueCreate(PQcompare_t priority_func, void *user_param)
{
    pri_queue_t *pq = NULL;
    assert(priority_func);
   
    pq=(pri_queue_t *)malloc(sizeof(pri_queue_t));
    if(!pq)
    {
        return NULL;
    }

    pq->heap=HeapCreate(pq_compare, pq);
    if(!pq->heap)
    {
        free(pq);
        return NULL;
    }
    pq->priority_func=priority_func;
    pq->user_param=user_param;

    return pq;
}

ilrd_uid_t PQueueEnQueue(pri_queue_t *pq, void *data)
{
    pqueue_member_t *member=NULL;
    assert(pq);
    assert(data);
    member=(pqueue_member_t *)malloc(sizeof(pqueue_member_t));
    if(!member)
    {
        return g_bad_uid;
    }

    member->data=data;
    member->uid=UIDGet();

    if(1==HeapPush(pq->heap, member))
    {
        free(member);
        return g_bad_uid;
    }

    return member->uid;
}

int PQueueReEnQueue(pri_queue_t *pq, void *data, ilrd_uid_t old_uid)
{
    pqueue_member_t *member=NULL;
    assert(pq);
    assert(data);
    member=(pqueue_member_t *)malloc(sizeof(pqueue_member_t));
    if(!member)
    {
        return 1;
    }

    member->data=data;
    member->uid=old_uid;

    if(1==HeapPush(pq->heap, member))
    {
        free(member);
        return 1;
    }

    return 0;
}

ilrd_uid_t PQueueDeQueue(pri_queue_t *pq)
{
    pqueue_member_t *member=NULL;
    ilrd_uid_t rm_uid=UIDGetNull();
    assert(pq);

    member=(pqueue_member_t *)HeapPeek(pq->heap);
    HeapPop(pq->heap);
    
    rm_uid=member->uid;
    member->data=NULL;
    member->uid=UIDGetNull();

    free(member);
    member=NULL;

    return rm_uid;
}

void PQueueClear(pri_queue_t *pq)
{
    assert(pq);
    while(!PQueueIsEmpty(pq))
    {
        PQueueDeQueue(pq);
    }
}

void PQueueDestroy(pri_queue_t *pq)
{
    assert(pq);
    PQueueClear(pq);
    HeapDestroy(pq->heap);

    pq->heap=NULL;
    pq->priority_func=NULL;
    pq->user_param=NULL;

    free(pq);
    pq=NULL;
}

size_t PQueueSize(pri_queue_t *pq)
{
    assert(pq);

    return HeapSize(pq->heap);
}

int PQueueIsEmpty(pri_queue_t *pq)
{
    assert(pq);

    return HeapIsEmpty(pq->heap);
}

void *PQueuePeek(pri_queue_t *pq)
{
    assert(pq);

    return (((pqueue_member_t *)HeapPeek(pq->heap))->data);
}

void *PQueueErase(pri_queue_t *pq, ilrd_uid_t uid)
{
    pqueue_member_t *member=NULL;
    void *data=NULL;

    assert(pq);

    member=(pqueue_member_t *)HeapRemove(pq->heap,&uid,PQIsMatchUID, NULL);

    if(NULL == member)
    {
        return NULL;
    }

    data=member->data;

    member->data=NULL;
    member->uid=UIDGetNull();

    free(member);
    member=NULL;

    return data;
}

static int PQIsMatchUID(const void *list_data,const void *data, void *user_param)
{
    assert(list_data);
    assert(data);

    return UIDIsSame((((pqueue_member_t *)list_data)->uid),*(ilrd_uid_t *)data);
}
