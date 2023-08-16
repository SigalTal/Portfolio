/*********************************
 * Reviewer:   
 * Author: Sigal Tal		
 * File: dll.h
 * ******************************/

#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>

typedef struct dll dll_t;
typedef struct dll_node *dll_iterator_t;

typedef int (*action_func_t)(void *list_data, void *param);
typedef int (*is_match_t)(const void *list_data, const void *data);

/* description: creates new doubly linked list 
   params: none
   return value: ptr to list or NULL if maaloc failes
   undefined behavior:
   O(1)  */  
dll_t *DListCreate(void);

/* description: destroys doubly linked list 
   params: ptr to dll
   undefined behavior:
   O(n) */  
void DListDestroy(dll_t *dlist);

/* description: count number of nodes 
   params: ptr to dll
   return value: number of nodes
   undefined behavior: 
   O(n) */  
size_t DListSize(const dll_t *dlist);

/* description: checks if the list is empty 
   params: ptr to dll
   return value: non-zero if empty 0 if not
   undefined behavior: 
   O(1) */  
int DListIsEmpty(const dll_t *dlist); 

/* description: iterator to the first element in the list 
   params: DList
   return value: dll_iterator to first elemenet node. In case the list is empty returns iterator to the end of the list;
   undefined behavior:
   O(1)  */ 
dll_iterator_t DListBegin(const dll_t *dlist);

/* description: returns the end of list
   params: DList
   return value: dll_iterator with end node
   undefined behavior: 
   O(1) */ 
dll_iterator_t DListEnd(const dll_t *dlist);

/* description: returns  the next node 
   params: dll_iterator_t curr
   return value: dll_iterator with next node
   undefined behavior: if it is the End node
   O(1)  */ 
dll_iterator_t DListNext(dll_iterator_t curr);

/* description: returns the previos node 
   params: dll_iterator_t curr
   return value: dll_iterator with prev node
   undefined behavior: if it is the first node
   O(1)  */
dll_iterator_t DListPrev(dll_iterator_t curr);

/* description: compers bitween 2 iterators  
   params:2 dll_iterator_t   
   return value: non-zero if equal 0 if not
   O(1)  */ 
int DListIsSameIter(dll_iterator_t first, dll_iterator_t second);

/* description: returns the data in the curr node
   params: dll_iterator_t curr
   return value: pointer to the data of the curr node
   undefined behavior: if it the end of list
   O(1) */ 
void *DListGetData(dll_iterator_t curr);

/* description: insert node at the begening of the list
   params: ptr to list and ptr to data
   return value: iterator to the new node 
   undefined behavior:
   O(1) */
dll_iterator_t DListPushFront(dll_t *list, void *data);

/* description: insert node at the end of the list
   params: ptr to list and the data
   return value: iterator to the new node 
   undefined behavior:
   O(1) */ 
dll_iterator_t DListPushBack(dll_t *list, void *data);

/* description: removes the first node
   params: ptr to list
   return value: the data from removed node
   undefined behavior:empty list
   O(1) */ 
void *DListPopFront(dll_t *list);

/* description:removes the last node 
   params: ptr to list
   return value: the data from removed node 
   undefined behavior:empty list
   O(1) */ 
void *DListPopBack(dll_t *list);

/* description: creates new node in the list before the current 
   params: ptr to list,iterator, void *new_data of the new node
   return value: dll_iterator to inserted node if sucsses, end node if fails
   undefined behavior: 
   complexity: O(1) 
*/  
dll_iterator_t  DListInsert(dll_t *dlist, dll_iterator_t curr, void *data);

/* description: removes the curr element 
   params: ptr to curr iterator
   return value: next elemnt 
   undefined behavior: try to remove end node
   complexity: O(1) */ 
dll_iterator_t DListRemove(dll_iterator_t curr);


/* description:find the first match node. Start at from till to (not included)
   params: dll_iterator from, dll_iterator to , pointer to data, ptr to comper function
   return value: dll_iterator of the first found node in case of success and dll_iterator to if fails. 
   Match func returns non-zero if matches and 0 otherwise
   undefined behavior: if you cant implement the function on the nodes*/ 
dll_iterator_t DListFind(dll_iterator_t from, dll_iterator_t to, const void *data, is_match_t func);

/* description:findes the nodes that matches and copy their data to dlist_dest. Start at from till to (not included)
   params: dll_iterator from, dll_iterator to ,ptr to dlist to copy , pointer to data, ptr to comper function
   return value: in casr of sucsess 0 non-zero otherwise . 
   Match func returns 1 if matches and 0 otherwise
   undefined behavior: 
   O(n) */   
int DListMultiFind(dll_iterator_t from, dll_iterator_t to, dll_t *dlist_dest, const void *data, is_match_t func);

/* description: implements the func on node from till to (not included)
   params: ptr to the start node,ptr to the end node, pointer to param and ptr to the function
   return value: 0 in case of success, none-zero in case of failure 
   action function returns 0 in case of success and none-zero in case of failure
   undefined behavior: if you cant implement the function on the nodes
   O(n)*/  
int DListForEach(dll_iterator_t from, dll_iterator_t to, void *param, action_func_t func);


/* description: inserts the nodes from begin to end before where.
   params: where, begin, end
   return : pointer to last element spliced.
   undefined behavior : 
   O(1) */ 
dll_iterator_t DListSplice(dll_iterator_t where,dll_iterator_t begin, dll_iterator_t end);



#endif /* __DLL_H__ */