/*********************************
 * Reviewer:Roy
 * Author: Sigal
 * File Name: heap_test.c
 * ******************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"
static int IntCompare(const void *data1,const void *data2, void *user_param);
void BasicTest();
void AdvancedTest();
void CheckHeap(heap_t* heap);

int main()
{
    BasicTest();
    AdvancedTest();
    return 0;
}

static int IntCompare(const void *data1,const void *data2, void *user_param)
{
    (void)(user_param);
    return (*(int*)data1 > *(int*)data2);
}

static int IntMatch(const void *data1,const void *data2, void *user_param)
{
    (void)(user_param);
    return (*(int*)data2 == *(int*)data1);
}

void BasicTest()
{
    int a=6, b=5, c=9, d=2;
    heap_t *heap=HeapCreate(IntCompare, NULL);
    assert(1==HeapIsEmpty(heap));
    assert(HeapSize(heap)==0);

    HeapPush(heap, &a);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==1);
    assert(6==*(int *)HeapPeek(heap));

    HeapPush(heap, &b);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==2);
    assert(6==*(int *)HeapPeek(heap));

    HeapPush(heap, &c);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==3);
    assert(9==*(int *)HeapPeek(heap));

    HeapPush(heap, &d);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==4);
    assert(9==*(int *)HeapPeek(heap));

    HeapPop(heap);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==3);
    assert(6==*(int *)HeapPeek(heap));

    HeapPop(heap);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==2);
    assert(5==*(int *)HeapPeek(heap));

    HeapPop(heap);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==1);
    assert(2==*(int *)HeapPeek(heap));

    HeapDestroy(heap);
}

void RemoveTest()
{
     int a=6, b=5, c=9, d=2, test=0;
    heap_t *heap=HeapCreate(IntCompare, NULL);
    assert(1==HeapIsEmpty(heap));
    assert(HeapSize(heap)==0);

    HeapPush(heap, &a);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==1);
    assert(6==*(int *)HeapPeek(heap));

    HeapPush(heap, &b);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==2);
    assert(6==*(int *)HeapPeek(heap));

    HeapPush(heap, &c);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==3);
    assert(9==*(int *)HeapPeek(heap));

    HeapPush(heap, &d);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==4);
    assert(9==*(int *)HeapPeek(heap));

    test =*(int *)HeapRemove(heap,&b,IntMatch,NULL);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==3);
    assert(9==*(int *)HeapPeek(heap));
    assert(b==test);

    HeapPop(heap);
    assert(0==HeapIsEmpty(heap));
    assert(HeapSize(heap)==2);
    assert(6==*(int *)HeapPeek(heap));

    HeapDestroy(heap);
}

int numbers[10000];

void AdvancedTest()
{
    int i, toRem;
    heap_t *heap=HeapCreate(IntCompare, NULL);

    for (i=0; i < 10000; ++i)
    {
        numbers[i] = rand() % 100000;
        HeapPush(heap, &numbers[i]);
    }

    CheckHeap(heap);

    toRem = rand() % 10000;
    HeapRemove(heap, &numbers[toRem],IntMatch,NULL);

    CheckHeap(heap);

    HeapDestroy(heap);
}

void CheckHeap(heap_t* heap)
{
    int  num;
    size_t heapSize = HeapSize(heap), i;


    num = *(int*)HeapPeek(heap);
    for (i=0; i < heapSize-1; ++i)
    {
        HeapPop(heap);
        if (num < *(int*)HeapPeek(heap))
        {
            printf("OOOPPPPPSSSS\n");
        }
        num = *(int*)HeapPeek(heap);
    }
}