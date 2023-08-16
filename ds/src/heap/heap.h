/*********************************
 * Reviewer:Roy
 * Author: Sigal
 * File Name: heap.h
 * ******************************/
#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

typedef struct heap heap_t;

typedef int (*heap_is_match_func_t)(const void *a_data, 
                                  const void *b_data, void *user_param);

typedef int (*heap_compare_func_t)(const void *a_data, 
                                  const void *b_data, void *user_param);

heap_t *HeapCreate(heap_compare_func_t comp_ptr,void *user_param);
/*	Description: Creates the Heap
	Parameters: 
	Return value:
	Undefined behavior: 
   Complexity: O(1) 
*/  

void HeapDestroy(heap_t *heap);
/*	Description: Destroy the Heap
	Parameters: 
	Return value: none
	Undefined behavior: 
	Complexity: O(1) 
*/

int HeapPush(heap_t *heap, const void *data);
/*	Description: 
	Parameters: 
	Return value: 0 in success, non-zero for fail
	Undefined behavior: 
	Complexity: O(log n)
*/ 

void HeapPop(heap_t *heap);
/*	Description: pop the max/min element
	Parameters: 
	Return value:
	Undefined behavior: 
	Complexity: O(log n)
*/   

void *HeapRemove(heap_t *heap,const void *data,heap_is_match_func_t is_match,void *user_param);
/*	Description: remove specific element
	Parameters: 
	Return value: 
	Undefined behavior: 
	Complexity: O(log n)
*/ 

size_t HeapSize(heap_t *heap);
/*	Description: 
	Parameters: 
	Return value: 
	Undefined behavior: 
	Complexity: O(1)
*/  

int HeapIsEmpty(heap_t *heap);
/*	Description:	
	Parameters: 
	Return value: 0 if not empty, 1 if empty.
	Undefined behavior: 
	Complexity: O(1)
*/ 

void *HeapPeek(heap_t *heap);
/*	Description: peek the max/min element
	Parameters: 
	Return value:  
	Undefined behavior: 
	Complexity: O(1)
*/ 


#endif /* __HEAP_H__ */
