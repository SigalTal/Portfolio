/*********************************
 * Reviewer: Daniel Binyamin 
 * Author: Sigal Tal		
 * File: recursion.c
 * ******************************/
#include <string.h>
#include <assert.h>
#include "recursion.h"
#include "stack.h"

static void SortedInsert(stack_t *stack,int elem);

int Fibonacci(int elem_index)
{
    if (elem_index<2)
    {
        return elem_index;
    }

    return Fibonacci(elem_index-1)+Fibonacci(elem_index-2);
}

size_t StrLenRec(const char *str)
{
    assert(str);
    if('\0'==*str)
    {
        return 0;
    }

    return StrLenRec(str+1)+1;   
}

int StrCmpRec(const char *str1, const char *str2)
{
    assert(str1);
    assert(str2);
    if(*str1 != *str2 || *str1=='\0' || *str2=='\0')
    {
        return *str1-*str2;
    }

    return StrCmpRec(str1+1,str2+1);
}

char *StrCpyRec(char *dest, const char *src)
{
    assert(src);
    if('\0'!=*src)
    {
        *dest=*src;
        *(dest+1)='\0';
        StrCpyRec(dest+1,src+1);
    }

    return dest;
}

char *StrCatRec(char *dest,const char *src)
{
    assert(src);
    if('\0'!=*dest)
    {
       StrCatRec(dest+1,src);
    }

    else
    {
        StrCpyRec(dest,src);
    }
    
    return dest;
}

char *StrStrRec(const char *haystack, const char *needle)
{
    assert(haystack);
    assert(needle);
    if('\0'==*haystack)
    {
        return NULL;
    }

    if(0!=strncmp(haystack,needle,StrLenRec(needle)))
    {
       return StrStrRec(++haystack, needle); 
    }

    return (char *)haystack;
}

node_t* FlipList(node_t* node)
{
    
    node_t *tmp=NULL;
    assert(node);

    if(NULL==node->next)
    {
        return node;
    }

    tmp=FlipList(node->next);
    node->next->next=node;
    node->next=NULL;
    return tmp;
}

void SortStack(stack_t *stack)
{
    int elem;
    assert(stack);
    if(StackSize(stack)<=1)
    {
        return;
    }

    StackPeek(stack,&elem);
    StackPop(stack);
    SortStack(stack);
    SortedInsert(stack,elem);
}

static void SortedInsert(stack_t *stack,int elem)
{
    int top=0;
    assert(stack);
    if(StackIsEmpty(stack))
    {
        StackPush(stack,&elem);
        return;
    }

    StackPeek(stack,&top);

    if(top<=elem)
    {
        StackPush(stack,&elem);
        return;
    }

    StackPop(stack);
    SortedInsert(stack,elem);
    StackPush(stack,&top);
}

