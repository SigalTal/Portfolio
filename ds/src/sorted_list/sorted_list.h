/*********************************
 * Reviewer:   
 * Author: Sigal Tal		
 * File: sorted_list.h
 * ******************************/

#ifndef __SORTED_DLL_H__
#define __SORTED_DLL_H__

#include <stddef.h> /* size_t */
#include "dll.h"

typedef struct sorted_list sorted_list_t;
typedef struct sorted_list_iterator sorted_list_iterator_t;

/* return: returns negative number if data2 should be before data1 */
typedef int(*sorted_list_compare_func_t)(const void *data1, const void *data2, void *user_param);

/*user's function return 0 on success, non-zero integer if failed*/
typedef int(*sorted_list_is_match_func_t)(const void *list_data, const void *data); 

/*user's function return 0 on success, non-zero integer if failed*/
typedef int(*sorted_list_action_func_t)(void *list_data, void *data); 

/*  Description: Initiates the iterator
    Parameters: 
    Return Value: Initialized iterator
    Undefined Behavior: 
    Complexity: O(1) */
sorted_list_iterator_t SortedListIterInit(void); 

/*  Description: Creates a new Sorted List
    Parameters: pointer to user's comparison function used for sorting
    Return Value: Pointer to the sorted list, NULL if failed to allocate
    Undefined Behavior: 
    Complexity: O(1) */
sorted_list_t *SortedListCreate(sorted_list_compare_func_t compare_func, void* user_param);

/*  Description: Destroys the Sorted List
    Parameters: Pointer to a sorted list
    Return Value:
    Undefined Behavior: 
    Complexity: O(n) */
void SortedListDestroy(sorted_list_t *list); 

/*  Description: Returns the size of the Sorted List
    Parameters: const Pointer to the sorted list
    Return Value: size of sorted list - number of nodes used
    Undefined Behavior: 
    Complexity: O(n) */
size_t SortedListSize(const sorted_list_t *list); 

/*  Description: Checks if the sorted list is empty
    Parameters: const Pointer to the sorted list
    Return Value: non-zero integer if sorted list is empty, 0 otherwise
    Undefined Behavior: 
    Complexity: O(n) */
int SortedListIsEmpty(const sorted_list_t *list); 

/*  Description: Returns the first node in the list
    Parameters:const Pointer to sorted list
    Return Value: Iterator to the first node of the list
    Undefined Behavior: 
    Complexity: O(1) */ 
sorted_list_iterator_t SortedListBegin(const sorted_list_t *list);

/*  Description: Returns the last node in the list
    Parameters: const Pointer to sorted list
    Return Value: Iterator to the end node of the list
    Undefined Behavior: 
    Complexity: O(1) */
sorted_list_iterator_t SortedListEnd(const sorted_list_t *list); 

/*  Description: Returns the next node
    Parameters: Iterator to current node
    Return Value: Iterator to the next node
    Undefined Behavior: if current node is the last node
    Complexity: O(1) */ 
sorted_list_iterator_t SortedListNext(sorted_list_iterator_t iter); 

/*  Description: Returns the previous node
    Parameters: Iterator to current node
    Return Value: Iterator to the previous node
    Undefined Behavior: if current is the first node
    Complexity: O(1) */
sorted_list_iterator_t SortedListPrev(sorted_list_iterator_t iter);

/*  Description: Checks if two iterators are equal
    Parameters: Two iterators
    Return Value: non-zero integer if equal, 0 otherwise
    Undefined Behavior: 
    Complexity: O(1) */ 
int SortedListIsSameIter(sorted_list_iterator_t iter1, sorted_list_iterator_t iter2);

/*  Description: Gets the data from the current node
    Parameters: Iterator to current node
    Return Value: Pointer to data
    Undefined Behavior: if current node is the end node
    Complexity: O(1) */
void *SortedListGetData(sorted_list_iterator_t iter);

/*  Description: Insert a new node to the list, to the proper position
    Parameters: pointer to the sorted list, pointer to the new data
    Return Value: Iterator to the inserted node, end node if failed
    Undefined Behavior: 
    Complexity: O(n) */ 
sorted_list_iterator_t SortedListInsert(sorted_list_t *list, void *data); 

/*  Description: Removes the first node from the list
    Parameters: pointer to the sorted list
    Return Value: void pointer to the removed data
    Undefined Behavior: 
    Complexity: O(1) */
void *SortedListPopFront(sorted_list_t *list); 

/*  Description: Removes the last node from the list
    Parameters: pointer to the sorted list
    Return Value: void pointer to the removed data
    Undefined Behavior: 
    Complexity: O(1) */
void *SortedListPopBack(sorted_list_t *list); 

/*  Description: Remove a node from the sorted list
    Parameters: Iterator to remove
    Return Value: Iterator to the next node after the removed
    Undefined Behavior: Removing the end node
    Complexity: O(1) */
sorted_list_iterator_t SortedListRemove(sorted_list_iterator_t curr); 

/*  Description: Perform action function on every data in range (from-to)
    Parameters: two iterators defining the range in list (not including to)
                pointer to parameter
                pointer to user's action function
                user's function returns 0 on success, non-zero integer if failed
    Return Value: 0 if all succeeded, number of actions performed in case of failure
    Undefined Behavior: 
    Complexity: O(1) */
int SortedListForEach(sorted_list_iterator_t from, sorted_list_iterator_t to, void *param, sorted_list_action_func_t action_func); 

/*  Description: Merge  one sorted list to another
    Parameters: pointer to destination list
                pointer to source list
    Return Value: 
    Undefined Behavior: if the lists aren't sorted by the same criteria
    Complexity: O(n+m) */
void SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list); 

/*  Description: Finds the iterator that would have been after the data
                if it would be inserted
                (i.e.: if appropriate position is not found -
                        data would be before 'to' iterator)
    Parameters: pointer to the sorted list
                two iterators defining the range (not including 'to')
                const pointer to data 
    Return Value:   iterator to the would be next iterator.
                    iterator to end of the list if position is not found
    Undefined Behavior: 
    Complexity: O(n) */ 
sorted_list_iterator_t SortedListFind(sorted_list_t *list, sorted_list_iterator_t from, sorted_list_iterator_t to, const void *data);

/*  Description: Finds an iterator that contains the data 
    Parameters: two iterators defining the range (from-to not including to)
                const pointer to parameter to compare to
                pointer to is_match function
                user's function return 0 on success, non-zero integer if failed
    Return Value: Iterator to the found node
    Undefined Behavior: 
    Complexity: O(n) */ 
sorted_list_iterator_t SortedListFindIf(sorted_list_iterator_t from, sorted_list_iterator_t to, const void *data, sorted_list_is_match_func_t is_match_func); /* O(n) */


/* Please don't deal with instances of iterators */
struct sorted_list_iterator
{
    dll_iterator_t dll_iter;
    
    #ifndef NDEBUG
    sorted_list_t *sorted_list;
    #endif
};



#endif /* __SORTED_DLL_H__ */