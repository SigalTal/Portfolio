/*********************************
 * Reviewer: 
 * Author: 		
 * File: bst.h
 * ******************************/

#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct
{
  struct bst_node* bst_node;
}bst_iterator_t;

typedef struct bst bst_t;
typedef int (*bst_action_func_t)(void *bst_data, void *data);
typedef int (*bst_compare_func_t)(const void *a_data, const void *b_data, void *user_param);



bst_t *BSTCreate(bst_compare_func_t compare_func, void *user_param); 
/* Description: 
   Params: 
   Return value: bst_t or NULL if malloc failed
   Undefined behavior: 
   Complexity: O(1)
*/  

void BSTDestroy(bst_t *bst);
/* Description: 
   Params: 
   Return value: none
   Undefined behavior: 
   Complexity: O(n)
*/  

size_t BSTSize(bst_t *bst);
/* Description: 
   Params: 
   Return value : number of nodes in the tree.
   Undefined behavior: 
   Complexity: O(n)
*/  

int BSTIsEmpty(bst_t *bst);
/* Description: 
   Params: 
   Return value: 0 if not empty, non-zero if empty.
   Undefined behavior: 
   Complexity: O(1)
*/ 
  
bst_iterator_t BSTInsert(bst_t *bst, const void *data); /* data is key and value */
/* Description: 
   Params: 
   Return value: EOL if key already exist or malloc failed, iterator to the new node if succsses. 
   Undefined behavior: 
   Complexity: o(logn), o(n) in unbalanced tree
*/ 

void BSTRemove(bst_iterator_t iter);
/* Description: 
   Params: 
   Return value: none
   Undefined behavior: 
   Complexity: o(1)
*/ 

bst_iterator_t BSTBegin(bst_t *bst);
/* Description: 
   Params: 
   Return value: iterator with smallest key
   Undefined behavior: 
   Complexity: o(1)
*/ 

bst_iterator_t BSTEnd(bst_t *bst);
/* Description:
   Params: 
   Return value: returns the iteraor to the node which it's previous is the biggest key 
   Undefined behavior: 
   Complexity: o(?) save in the admin struct or iterate?
*/ 

bst_iterator_t BSTNext(bst_iterator_t iter);
/* Description: 
   Params: 
   Return value: 
   Undefined behavior: 
   Complexity: O(1)
*/

bst_iterator_t BSTPrev(bst_iterator_t iter);
/* Description: 
   Params: 
   Return value: 
   Undefined behavior: 
   Complexity: o(1)
*/ 

int BSTIsSameIter(bst_iterator_t f_iter, bst_iterator_t s_iter);
/* Description: 
   Params: 
   Return value: 0 if different, non-zero if iterators are the same.
   Undefined behavior: 
   Complexity: o(1)
*/ 

void *BSTGetData(bst_iterator_t iter);
/* Description: returns the value held in the node of the given iterator
   Params: 
   Return value: user data of the node held by the iterator.
   Undefined behavior: 
   Complexity - o(1)
*/ 

bst_iterator_t BSTFind(bst_t *bst, const void *data);
/* Description: finds the node in the tree that matches the data 
   Params: 
   Return value : EOL case not found data in the tree, or correspond iterator.
   Undefined behavior: 
   Complexity: o(n)
*/ 

int BSTForEach(bst_t *bst, bst_action_func_t action_func, void *param);
/* Description: executes the func on each of the nodes of the tree
   Params: 
   Return value : 0 if function worked on all nodes succesfully, none zero if at least 1 failed. 
   Undefined behavior: 
   Complexity: o(n)
*/
  
#endif
