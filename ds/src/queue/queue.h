/*********************************
 * Reviewer: 
 * Author:Sigal Tal 
 * File Name: queue.h
 * ******************************/

#ifndef __Queue_H__
#define __Queue_H__

#include <stddef.h>

typedef struct queue queue_t;

/* description: creates a new queue 
   params:
   return value: In case of success pointer to the new queue, Null in case of failure
   undefined behavior:  
   complexity - O(1)*/ 
queue_t *QueueCreate();

/* description: frees all allocations
   params: pointer to the queue
   undefined behavior: null pointer  
   complexity - O(n)*/
void QueueDestroy(queue_t *q);

/* description: push an new element to the end of the queue
   params: pointer to queue and element to add
   return value : 1 if alloc faild, 0 if success.
   undefined behavior: null pointer, push to a full queue 
   complexity - O(1)*/   
int QueueEnQueue(queue_t *q, void *element_add);

/* description: extract the first element
   params: pointer to the queue
   undefined behavior: extract on an empty queue, null pointer 
   complexity - O(1)*/
void QueueDeQueue(queue_t *q);

/* description: copies the value of the first element.
   params: pointer to the queue.
   undefined behavior: empty queue, null pointer.
   complexity - O(1)*/
void *QueuePeek(const queue_t *q);

/* description: Attaches queue 2 to the end of Queue 1. 
   params: queue_t *q1, queue_t *q2.
   return value: Pointer to the new queue (q1)
   undefined behavior: 
   complexity - O(1)*/ 
queue_t *QueueAppend(queue_t *q1, queue_t *q2);

/* description: Prints out the size of Queue. 
   params: queue_t *q.
   return value: returns the size of the queue.
   undefined behavior:
   complexity - O(n)*/ 
size_t QueueSize(const queue_t *q);

/* description: checks if the queue is empty.
   params: pointer to the queue.
   return value: 1 if queue is empty 0 otherwise.
   undefined behavior:
   complexity - O(1)*/
int QueueIsEmpty(const queue_t *q);


#endif /*__Queue_H__*/