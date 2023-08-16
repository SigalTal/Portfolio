/*********************************
 * Reviewer: Daniel Natan
 * Author: Sigal Tal    
 * File: AVL.h
 * ******************************/

#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */


typedef struct avl avl_t;

typedef int (*avl_action_func_t)(void *avl_data, void *user_param);

typedef int (*avl_compare_func_t)(const void *a_data, 
                                  const void *b_data, void *user_param);



avl_t *AvlCreate(avl_compare_func_t compare_func, void *user_param); 
/* Description: 
   Params: 
   Return value: avl_t or NULL if malloc failed
   Undefined behavior: 
   Complexity: O(1)
*/  

void AvlDestroy(avl_t *avl);
/* Description: 
   Params: 
   Return value: none
   Undefined behavior: 
   Complexity: O(n)
*/  

size_t AvlSize(avl_t *avl);
/* Description: 
   Params: 
   Return value : number of nodes.
   Undefined behavior: 
   Complexity: O(n)
*/  

int AvlIsEmpty(avl_t *avl);
/* Description: 
   Params: 
   Return value: 0 if not empty, 1 if empty.
   Undefined behavior: 
   Complexity: O(1)
*/ 
  
int AvlInsert(avl_t *avl, const void *data); /* data is key and value */
/* Description: 
   Params: 
   Return value:  
   Undefined behavior: 
   Complexity: O(logn)
*/ 

void AvlRemove(avl_t *avl, void *data);
/* Description: 
   Params: 
   Return value: none
   Undefined behavior: 
   Complexity: O(logn)
*/ 

void *AvlFind(avl_t *avl, const void *data);
/* Description: finds the node that matches the data 
   Params: 
   Return value : EOL if data not found, or corresponding data.
   Undefined behavior: 
   Complexity: O(logn)
*/ 

int AvlForEach(avl_t *avl, avl_action_func_t action_func, void *param);
/* Description: executes the func on each of the nodes
   Params: 
   Return value : 0 on success, return value of action_func on fail. 
   Complexity: O(n)
*/

size_t AvlHeight(const avl_t *tree);

size_t AvlSize(avl_t *avl);


#endif /* __AVL_H__ */