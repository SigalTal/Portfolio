/*********************************
 * Reviewer: Viktor  
 * Author: Sigal Tal		
 * File: sll.h
 * ******************************/

#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h>/*size_t*/

typedef struct node node_t;

typedef struct sll sll_t;

typedef node_t *sll_iterator;


/* description: returns the head 
   params: sll
   return value: sll_iterator with head node in case the list is empty returns Dummy
   undefined behavior:
   O(1)  */ 
sll_iterator SLLBegin(sll_t *slist);

/* description: returns the tail
   params: sll
   return value: sll_iterator with tail node (Dummy)
   undefined behavior: 
   O(1) */ 
sll_iterator SLLEnd(sll_t *slist);

/* description: returns the next node 
   params: sll
   return value: sll_iterator with next node
   undefined behavior: if it is the End node
   O(1)  */ 
sll_iterator SLLNext(sll_iterator curr);

/* description: returns the value of the curr node
   params: 
   return value: value of the curr node
   undefined behavior: if it the End
   O(1) */ 
void *SLLGet(sll_iterator curr);

/* description: sets the data in curr node 
   params:sll_iterator 
   return value: 
   undefined behavior: if it is the end
   O(1)  */ 
void SLLSetData(sll_iterator curr, void *data);

/* description: compers bitween 2 iterators  
   params:sll_iterator  
   return value: 1 if equal 0 if not
   undefined behavior: if sll_iterator is NULL
   O(1)  */ 
int SLLIteratorsIsEqual(sll_iterator iter1, sll_iterator iter2);

/* description: creates new singly linked list 
   params: 
   return value: ptr to head node or NULL if failed
   undefined behavior:
   O(1)  */  
sll_t *SLLCreate();

/* description: creates new node in the list before the current 
   params: iterator, void *new_data of the new node
   return value: sll_iterator to inserted node if sucsses, end node if fails
   undefined behavior: 
   complexity: O(1) in case of success, O(n) in case of failure
*/  
sll_iterator SLLInsert(sll_iterator curr, void *new_data);

/* description: remove the curr element 
   params: ptr to node_t
   return value: next elemnt if sucsses, End node if fails
   undefined behavior: 
   complexity: O(1) in case of success, O(1) in case of failure */  
sll_iterator SLLRemove(sll_iterator curr);

/* description: count number of nodes 
   params: ptr to sll
   return value: number of nodes
   undefined behavior: 
   O(n) */  
size_t SLLCount(const sll_t *slist);

/* description:stops when findes the node. Start at from till to (not included)
   params: sll_iterator from, sll_iterator to , ptr to comper function
   return value: sll_iterator of the found node in case of success and sll_iterator to if fails. 
   Match func returns 0 if matches and 1 otherwise
   undefined behavior: if the end node does not exict
   O(n) */  
sll_iterator SLLFind(sll_iterator from, sll_iterator to,void *param, int (*match)(sll_iterator curr,void *param));

/* description: implements the func on node from till to (not included)
   params: ptr to the start node,ptr to the end node, and ptr to the function
   return value: 0 in case of success, none-zero in case of failure 
   action function returns 0 in case of success and none-zero in case of failure
   undefined behavior: if you cant implement the function on the nodes, if the end node does not exist
   O(n)*/  
int SLLForEach(sll_iterator from, sll_iterator to, void *param, int (*action)(sll_iterator curr,void *param));

/* description: destroys singly linked list 
   params: ptr to sll
   undefined behavior:
   O(n) */  
void SLLDestroy(sll_t *slist);

/* description: Append 2 lists into 1 & deletes sll1 dummy.
   params: ptr to sll1 & ptr to sll2
   return : pointer to sll1 head.
   undefined behavior : 
   O(1) */ 
sll_t *SLLAppend(sll_t *slist1, sll_t *slist2);

#endif /* __SLL_H__ */
