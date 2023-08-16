/*********************************
 * Reviewer: 
 * Author: 
 * File Name: hash_table.h
 * ******************************/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h> /* size_t */

typedef struct hash hash_t;

typedef int (*hash_action_func_t)(void *hash_data, void *user_param);

typedef int (*hash_is_match_t)(const void *list_data, const void *data);

typedef int (*hash_func_t)(void *key);

hash_t *HashCreate(hash_is_match_t is_match_func,
					hash_func_t hash_func ,size_t table_size);
/*	Description: 
	Parameters: 
	Return value: hash_t pointer or NULL if malloc failed
	Undefined behavior: 
	Complexity: O(1)
*/  

void HashDestroy(hash_t *hash);
/*	Description: 
	Parameters: 
	Return value: none
	Undefined behavior: 
	Complexity: O(n)
*/  

size_t HashSize(hash_t *hash);
/*	Description: 
	Parameters: 
	Return value: number of nodes.
	Undefined behavior: 
	Complexity: O(n)
*/  

int HashIsEmpty(hash_t *hash);
/*	Description: 
	Parameters: 
	Return value: 0 if not empty, 1 if empty.
	Undefined behavior: 
	Complexity: O(1)
*/ 
  
int HashInsert(hash_t *hash, const void *data);
/*	Description: 
	Parameters: 
	Return value: 0 for success, non-zero if failed to insert
	Undefined behavior: 
	Complexity: O(1)
*/ 

void HashRemove(hash_t *hash, void *data);
/*	Description: 
	Parameters: 
	Return value: none
	Undefined behavior: 
	Complexity: O(1)
*/ 

void *HashFind(hash_t *hash, const void *data);
/*	Description: finds the node that matches the data 
	Parameters: 
	Return value: NULL if data not found, or corresponding data.
	Undefined behavior: 
	Complexity: O(1)
*/ 

int HashForEach(hash_t *hash, hash_action_func_t action_func, void *param);
/*	Description: executes the action_func on each of the nodes
	Parameters: 
	Return value : 0 on success, return value of action_func on fail. 
	Complexity: O(n)
*/


#endif /* __HASH_TABLE_H__ */