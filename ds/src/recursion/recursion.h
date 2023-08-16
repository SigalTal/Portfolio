/*********************************
 * Reviewer: Daniel Binyamin 
 * Author: Sigal Tal		
 * File: recursion.h
 * ******************************/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>/*size_t*/
#include "stack.h"

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

int Fibonacci(int elem_index);

size_t StrLenRec(const char *str);

int StrCmpRec(const char *str1, const char *str2);

char *StrCpyRec(char *dest, const char *src);

char *StrCatRec(char *dest,const char *src);

char *StrStrRec(const char *haystack, const char *needle);

node_t* FlipList(node_t* node);

void SortStack(stack_t *stack);


#endif