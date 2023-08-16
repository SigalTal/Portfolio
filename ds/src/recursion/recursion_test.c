/*********************************
 * Reviewer: Daniel Binyamin 
 * Author: Sigal Tal		
 * File: recursion_test.c
 * ******************************/

#include <stdio.h>/*printf*/
#include <assert.h>
#include <string.h>
#include "recursion.h"
#include "stack.h"


void TestFlipList();
void TestSortedStack();

int main()
{
    char str1[20]="sigal";
    char str2[10]="sigal";
    char str3[10]={0};
    char *str5;
    char str4[30]="xbbytsigaluyt";
    int i=0;
    printf("fib: %d\n",Fibonacci(4));
    printf("strlen: %lu\n",StrLenRec("Sigal"));
    printf("strcmp: %d\n",StrCmpRec(str1,str2));
    str5=StrCpyRec(str3,str2);
    assert(0==StrCmpRec(str5,str3));
    printf("cpy: ");
    while(str3[i]!=0)
    {
        
        printf("%c",str3[i]);
       
        ++i;
    }
     printf("\n");
    
    StrCatRec(str1,str2);
    i=0;
    printf("cat: ");
    while ((str1[i]))
    {
        
        printf("%c",str1[i]);
       
        ++i;
    }
    assert(strstr(str4,str1)==StrStrRec(str4,str1));  
    TestFlipList();
    TestSortedStack();
    return 0;
}

void TestFlipList()
{
    int e=1,f=2,g=3,h=4;
    
    node_t a;
    node_t b;
    node_t c;
    node_t d;
    node_t* res;

    a.data = &e;
    a.next = &b;

    b.data = &f;
    b.next = &c;

    c.data = &g;
    c.next = &d;

    d.data = &h;
    d.next = NULL;

    res = FlipList(&a);
    assert(res == &d);
}

void TestSortedStack()
{
    stack_t *stack=StackCreate(6,sizeof(int));
    int e=1,f=2,g=3,h=4;
    int x;

    StackPush(stack,&e);
    StackPush(stack,&g);
    StackPush(stack,&f);
    StackPush(stack,&h);

    SortStack(stack);

    StackPeek(stack,&x);
    assert(x==4);
    StackPop(stack);
    StackPeek(stack,&x);
    assert(x==3);
    StackPop(stack);
    StackPeek(stack,&x);
    assert(x==2);
    StackPop(stack);
    StackPeek(stack,&x);
    assert(x==1);
    StackPop(stack);

    StackDestroy(stack);

}
