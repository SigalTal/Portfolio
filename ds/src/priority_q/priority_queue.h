/*********************************
 * Reviewer:           
 * Author: Sigal Tal       
 * File: priority_queue.h          
 * ******************************/


#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stddef.h> /*size_t*/ 
#include "uid.h"

typedef struct p_queue pri_queue_t;
typedef int(*PQcompare_t)(const void *data1, const void *data2, void *user_param);

/*	Description: Creates a Priority Queue
	Parameters: User's Priority function and user's parameter
	Return Value: Handler for Priority Queue if succeeded, NULL if failed
	Undefined Behavior:
*/
pri_queue_t *PQueueCreate(PQcompare_t priority_func, void *user_param);

/*	Description: Destroys the Priority Queue
	Parameters: Handler for Priority Queue
	Return Value: 
	Undefined Behavior: 
*/
void PQueueDestroy(pri_queue_t *pq);

/*	Description: Insert a new element to the queue
	Parameters: Handler for Priority Queue, data to insert
	Return Value: UID of the inserted element, BadUID if failed
	Undefined Behavior:
*/
ilrd_uid_t PQueueEnQueue(pri_queue_t *pq, void *data); 

/*	Description: Insert a old element to the queue with old uid
	Parameters: Handler for Priority Queue, data to insert, and old uid
	Return Value: 0 for sucsess, non zero for failure
	Undefined Behavior:
*/
int PQueueReEnQueue(pri_queue_t *pq, void *data, ilrd_uid_t old_uid);

/*	Description: Removes the front element from the Priority Queue
	Parameters: Handler for Priority Queue
	Return Value: 
	Undefined Behavior: 
*/
ilrd_uid_t PQueueDeQueue(pri_queue_t *pq);

/*	Description: Peek at the front element of the Priority Queue
	Parameters: Handler for Priority Queue
	Return Value: Data of the element with the highest priority
	Undefined Behavior: empty queue
*/
void *PQueuePeek(pri_queue_t *pq); /* data, or null if empty */

/*	Description: Checks if the queue is empty
	Parameters: Handler for Priority Queue
	Return Value: non-zero integer if queue is empty, zero otherwise
	Undefined Behavior:
*/
int PQueueIsEmpty(pri_queue_t *pq); /* non-zero if empty */

/*	Description: Checks the number of elements in the Priority Queue
	Parameters: Handler for Priority Queue
	Return Value: number of element in the queue
	Undefined Behavior:
*/
size_t PQueueSize(pri_queue_t *pq);

/*	Description: Clears the Priority Queue, leaves it empty
	Parameters: Handler for Priority Queue
	Return Value: 
	Undefined Behavior:
*/
void PQueueClear(pri_queue_t *pq);

/*	Description: Erases a specific element from the queue
	Parameters: Handler for Priority Queue, uid of the element to erase
	Return Value: when not found uid returns NULL, if found uid the data in this uid
	Undefined Behavior:
*/
void *PQueueErase(pri_queue_t *pq, ilrd_uid_t uid);

#endif /* __PRIORITY_QUEUE_H__ */
