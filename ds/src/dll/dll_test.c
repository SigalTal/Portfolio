/*********************************
 * Reviewer:   
 * Author: Sigal Tal		
 * File: dll.h
 * ******************************/
#include <stdio.h>/*printf*/
#include <assert.h>
#include "dll.h"

static int IsMatchInt(const void *list_data, const void *data);
void TestNewDLL(void);
void TestDLLPopPush();
void TestFind(void);
void TestSplice();

int main()
{
    TestNewDLL();
    TestDLLPopPush();
    TestFind();
    TestSplice();
    
    return 0;
}

void TestNewDLL(void)
{
    dll_t *list;
    list=DListCreate();

    DListDestroy(list);
}

void TestDLLPopPush()
{
    dll_t *list=DListCreate();
    dll_iterator_t curr=DListBegin(list);
    int a=1;
    int b=2;
    int c=3;

    assert(1==DListIsEmpty(list));

    DListPushFront(list, &a);
    assert(1==DListSize(list));
    assert(0==DListIsEmpty(list));

    DListPushBack(list, &b);
    assert(2==DListSize(list));
    assert(0==DListIsEmpty(list));

    curr=DListBegin(list);

    DListInsert(list,curr, &c);
    assert(3==DListSize(list));
    assert(0==DListIsEmpty(list));

    curr=DListNext(curr);

    DListRemove(curr);
    assert(2==DListSize(list));

    assert(&c==DListPopFront(list));
    assert(1==DListSize(list));
    assert(0==DListIsEmpty(list));

    assert(&a==DListPopBack(list));
    assert(0==DListSize(list));
    assert(1==DListIsEmpty(list));

    DListDestroy(list);
}

void TestFind(void)
{
    dll_t *list=DListCreate();
    dll_t *dlist_dest=DListCreate();
    dll_iterator_t curr=DListBegin(list);
    dll_iterator_t found=DListBegin(list);
    dll_iterator_t dest=DListBegin(dlist_dest);
    int a=1;
    int b=2;
    int c=1;
    int d=1;
    int e=3;

    DListPushFront(list, &a);
    DListPushFront(list, &b);
    DListPushFront(list, &c);
    DListPushFront(list, &d);
    DListPushFront(list, &e);
    assert(5==DListSize(list));
    assert(0==DListIsEmpty(list));

    curr=DListBegin(list);
    found=DListBegin(list);

    curr=DListNext(curr);

    found=DListFind(DListBegin(list), DListEnd(list), &d, IsMatchInt);
    
    assert(1==DListIsSameIter(curr,found));

    assert(0==DListMultiFind(DListBegin(list), DListEnd(list),dlist_dest, &a, IsMatchInt));

    dest=DListBegin(dlist_dest);

    assert(&d==DListGetData(dest));

    found=DListEnd(dlist_dest);
    found=DListPrev(found);

    assert(&a==DListGetData(found));

    found=DListPrev(found);

    assert(&c==DListGetData(found));

    DListDestroy(list);
    DListDestroy(dlist_dest);

}

static int IsMatchInt(const void *list_data, const void *data)
{
    if(*(int *)list_data==*(int *)(data))
    {
        return 1;
    }

    return 0;
}

void TestSplice()
{
    dll_t *list1=DListCreate();
    dll_t *list2=DListCreate();
    dll_iterator_t curr1=DListBegin(list1);
    dll_iterator_t curr2=DListBegin(list2);

    int a=1;
    int b=2;
    int c=3;
    int d=4;
    int e=5;

    DListPushFront(list1, &a);
    DListPushFront(list1, &b);
    DListPushFront(list1, &c);
    DListPushFront(list1, &d);
    DListPushFront(list1, &e);

    DListPushFront(list2, &a);
    DListPushFront(list2, &b);
    DListPushFront(list2, &c);
    DListPushFront(list2, &d);
    DListPushFront(list2, &e);

    curr1=DListBegin(list1);
    curr2=DListBegin(list2);

    DListSplice(DListNext(DListNext(curr2)),curr1, DListPrev(DListPrev(DListEnd(list1))));
    assert(2==DListSize(list1));
    assert(8==DListSize(list2));

    while(DListNext(curr2))
    {
   /* printf("%d\n", *(int *)DListGetData(curr2));*/
    curr2=DListNext(curr2);
    }
    
    DListDestroy(list1);
    DListDestroy(list2);
}




