/*********************************
 * Reviewer:   
 * Author: Sigal Tal		
 * File: sorted_list.h
 * ******************************/
#include <stdio.h>/*printf*/
#include <assert.h>
#include "sorted_list.h"

int CompareInt (const void *data1, const void *data2, void *user_param);
int CompareIntDown (const void *data1, const void *data2);
int IsMatchInt(const void *list_data, const void *data);
int Plus(void *list_data, void *data);
void TestNewList(void);
void TestAll(void);
void TestForEach(void);
void TestMerge();
void TestFindIf(void);

int main()
{
    TestNewList();
    TestAll();
    TestForEach();
    TestMerge();
    TestFindIf();
    
    return 0;
}

int CompareInt (const void *data1, const void *data2, void *user_param)
{
	(void)(user_param);
    return (*(int*)data2 - *(int*)data1);
}

int CompareIntDown (const void *data1, const void *data2)
{
    return (*(int*)data1 - *(int*)data2);
}

void TestNewList(void)
{
   
    sorted_list_t *list=SortedListCreate(CompareInt,"sigal");

    SortedListDestroy(list);
}

void TestAll(void)
{
    sorted_list_t *list=SortedListCreate(CompareInt,"sigal");

    int a=1;
    int b=2;
    int c=3;

    sorted_list_iterator_t curr=SortedListInsert(list, &a);
    assert(1==SortedListSize(list));
    assert(0==SortedListIsEmpty(list));

    SortedListInsert(list, &b);
    assert(2==SortedListSize(list));
    assert(0==SortedListIsEmpty(list));

    SortedListInsert(list, &c);
    assert(3==SortedListSize(list));
    assert(0==SortedListIsEmpty(list));

    assert(&a==SortedListGetData(SortedListBegin(list)));
    assert(&b==SortedListGetData(SortedListNext(curr)));
    assert(&c==SortedListGetData(SortedListPrev(SortedListEnd(list))));

    assert(1==SortedListIsSameIter(curr, SortedListBegin(list)));

    SortedListRemove(curr);
    assert(2==SortedListSize(list));
    assert(0==SortedListIsEmpty(list));

    SortedListPopFront(list); 
    assert(1==SortedListSize(list));
    assert(0==SortedListIsEmpty(list));

    SortedListPopBack(list);
    assert(0==SortedListSize(list));
    assert(1==SortedListIsEmpty(list));

    SortedListDestroy(list);
}

int Plus(void *list_data, void *data)
{
   *(int *)list_data+=*(int *)data;

    return 0;
}

void TestForEach(void)
{
    sorted_list_t *list=SortedListCreate(CompareInt,"sigal");

    int a=1;
    int b=5;
    int c=2;
    int param=10;

    sorted_list_iterator_t curr=SortedListInsert(list, &a);
    SortedListInsert(list, &b);
    SortedListInsert(list, &c);

    assert(&a==SortedListGetData(SortedListBegin(list)));
    assert(&c==SortedListGetData(SortedListNext(curr)));
    assert(&b==SortedListGetData(SortedListPrev(SortedListEnd(list))));

    SortedListForEach(SortedListBegin(list), SortedListEnd(list), &param, *Plus);

    assert(11==*(int *)SortedListGetData(SortedListBegin(list)));
    assert(12==*(int *)SortedListGetData(SortedListNext(curr)));
    assert(15==*(int *)SortedListGetData(SortedListPrev(SortedListEnd(list))));


    SortedListDestroy(list);
}

void TestMerge()
{
    int x = 1 , y = 8, z =12 , o = 15, m = 100;
    int a = 2 , b = 4, c = 6, d = 10, e = 17, f= 43, g=105;
    sorted_list_t *list1 = SortedListCreate(CompareInt,"sigal");
    sorted_list_t *list2 = SortedListCreate(CompareInt,"sigal");
    sorted_list_iterator_t iter ;

    SortedListInsert(list1, &x);
    SortedListInsert(list1, &y);
    SortedListInsert(list1, &z);
    SortedListInsert(list1, &o);
    SortedListInsert(list1, &m);
    
    SortedListInsert(list2, &a);
    SortedListInsert(list2, &b);
    SortedListInsert(list2, &c);
    SortedListInsert(list2, &d);
    SortedListInsert(list2, &e);
    SortedListInsert(list2, &f);
    SortedListInsert(list2, &g);
    

    SortedListMerge (list1, list2);

    /*assert (9 == SortedListSize(list1));*/
    iter = SortedListBegin (list1);
    while (!SortedListIsSameIter(iter, SortedListEnd(list1)))
    {
        printf("%d,", *(int*)SortedListGetData(iter));
        iter= SortedListNext(iter);
    }

    SortedListDestroy(list1);
    SortedListDestroy(list2);
}

int IsMatchInt(const void *list_data, const void *data)
{
    if(*(int *)list_data==*(int *)(data))
    {
        return 1;
    }

    return 0;
}

void TestFindIf(void)
{
    sorted_list_t *list=SortedListCreate(CompareInt,"sigal");

    int a=1;
    int b=5;
    int c=2;
    int d=99;
    int e=76;

    sorted_list_iterator_t curr=SortedListInsert(list, &a);
    SortedListInsert(list, &b);
    SortedListInsert(list, &c);
    SortedListInsert(list, &c);
    SortedListInsert(list, &d);
    SortedListInsert(list, &e);


    curr=SortedListFindIf(SortedListBegin(list), SortedListEnd(list), &c, IsMatchInt);

    assert(2==*(int*)SortedListGetData(curr));

    curr=SortedListFindIf(SortedListBegin(list), SortedListEnd(list), &d, IsMatchInt);

    assert(99==*(int*)SortedListGetData(curr));

    SortedListDestroy(list);
}
