#include <stdlib.h>/*malloc - free*/
#include <assert.h>
#include "sll.h"
#include "queue.h"

struct queue
{
	sll_t *slist;
};

queue_t *QueueCreate()
{
	queue_t *q=(queue_t *)malloc(sizeof(queue_t));
	if(!q)
	{
		return NULL;
	}
	q->slist=SLLCreate();
	if(!q->slist)
	{
		free(q);
		return NULL;
	}

	return q;
}

void QueueDestroy(queue_t *q)
{
	assert(q);

	SLLDestroy(q->slist);
	q->slist=NULL;
	free(q);
	q=NULL;
}

int QueueEnQueue(queue_t *q, void *element_add)
{
	assert(q);
	assert(element_add);
	return (SLLIteratorsIsEqual(SLLEnd(q->slist),
								SLLInsert(SLLEnd(q->slist), element_add)));
}

void QueueDeQueue(queue_t *q)
{
	assert(q);
	SLLRemove(SLLBegin(q->slist));
}

void *QueuePeek(const queue_t *q)
{
	assert(q);
	return SLLGet(SLLBegin(q->slist));
}

size_t QueueSize(const queue_t *q)
{
	assert(q);
	return SLLCount(q->slist);

}

int QueueIsEmpty(const queue_t *q)
{
	assert(q);
	return (SLLCount(q->slist)?0:1);
}

queue_t *QueueAppend(queue_t *q1, queue_t *q2)
{
	assert(q1);
	assert(q2);
	SLLAppend(q1->slist, q2->slist);
	free(q2);

	return q1;
}