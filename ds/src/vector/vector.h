/*********************************
 * Reviewer:            
 * Author: Sigal Tal       
 * File: vector.h          
 * ******************************/

#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct vector vector_t;

#include <stddef.h>/*size_t*/


    /* This function creates vector and returns a pointer to vector struct
    based on user specification for capacity & number of element*/
vector_t *VectorCreate(size_t capacity, size_t element_size);
   
    /* This function frees all allocated memory in prog*/
void VectorDestroy(vector_t *vector_ptr);
    
    /* push new item into the Vector,Succes criteria 0, if fault return NUM */
int VectorPush(vector_t *vector_ptr, void *element_to_push);
    
    /* This function pops a vector element from the vector(stack)*/
void VectorPop(vector_t *vector_ptr);
    
    /* This function test's wether the Vector is empty or not
    (returns 1 on Empty (success) other value for failed*/
int VectorIsEmpty(vector_t *vector_ptr);
    
    /* This function tells the user currently the size of the vector - Size is how many
    items are currently allocated inside the vector */
size_t VectorSize(vector_t *vector_ptr);
    
    /* This function tells the user what is the 
    capacity he requested at the begining initiallize step */
size_t VectorCapacity(vector_t *vector_ptr);
    
    /* This function allows us to re-allocate a vector element with a 
    diffrent value that previously initiallized
    undefinde behavior if index>=size*/
void *VectorGetAccess(vector_t *vector_ptr, int index);
   
    /*Shrinks Vector size dependent (how many currently till 
    fitted size [Malloc could fail, 0 on success]*/
int VectorShrinkToFit(vector_t *vector_ptr);
    
    /*Changes the capacity per user input, can request a new 
    size bigger than current capacity [Malloc could fail, 0 on success]*/
int VectorReserve(vector_t *vector_ptr, size_t new_capacity);
#endif /*__VECTOR_H__*/