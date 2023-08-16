/*********************************
 * Reviewer: Viktor  
 * Author: Sigal Tal		
 * File: sll_test.c
 * ******************************/
#include <stdio.h>/*printf, size_t*/
#include <string.h>/*strcmp*/
#include <assert.h>
#include "sll.h"

void TestCreate();
void TestHead();
void TestTail();
void TestSetData();
int TestMatchString(sll_iterator curr, void *param);
void TestFindString();
int SetStr(sll_iterator curr, void *param);
void TestForEachString();
int ActionInt (sll_iterator curr, void *param);
void TestForEach();
void TestSLLAppend();

int main()
{
    TestCreate();
    TestHead();
    TestTail();
    TestSetData();
    TestFindString();
    TestForEach();
    TestForEachString();
    TestSLLAppend();
    return 0;
}

void TestCreate()
{
    sll_t *new_sll=SLLCreate();

    sll_iterator begin=SLLBegin(new_sll);
    sll_iterator end=SLLEnd(new_sll);

    assert(1==SLLIteratorsIsEqual(begin,end));
    (void)begin;
    (void)end;

    SLLDestroy(new_sll);

}

void TestHead()
{
    int new_data=4;

    sll_t *new_sll=SLLCreate();

    sll_iterator curr=SLLBegin(new_sll);

    sll_iterator end=SLLEnd(new_sll);
    
    SLLInsert(curr, &new_data);
    end=SLLEnd(new_sll);

    assert(0==SLLIteratorsIsEqual(curr,end));

    assert(*(int *)SLLGet(curr)==new_data);

    (void)end;

    SLLDestroy(new_sll);
}

void TestTail()
{
    int new_data1=4;
    int new_data2=5;
    int new_data3=6;

    sll_t *new_sll=SLLCreate();

    sll_iterator curr=SLLBegin(new_sll);

    SLLInsert(curr, &new_data1);
    curr=SLLNext(curr);
    SLLInsert(curr, &new_data2);
    curr=SLLNext(curr);
    SLLInsert(curr, &new_data3);

    assert(3==SLLCount(new_sll));

    assert(SLLNext(curr)==SLLEnd(new_sll));

    SLLDestroy(new_sll);
}

void TestSetData()
{

    int new_data1=4;
    int new_data2=5;
    int new_data3=6;

    sll_t *new_sll=SLLCreate();

    sll_iterator curr=SLLBegin(new_sll);

    SLLInsert(curr, &new_data1);
    curr=SLLNext(curr);
    SLLInsert(curr, &new_data2);

    assert(new_data2==*(int *)SLLGet(curr));

    SLLSetData(curr, &new_data1);

    assert(new_data1==*(int *)SLLGet(curr));

    curr=SLLNext(curr);
    SLLInsert(curr, &new_data3);

    SLLDestroy(new_sll);
}

void TestRemove()
{
    int new_data1=4;
    int new_data2=5;
    int new_data3=6;

    sll_t *new_sll=SLLCreate();

    sll_iterator curr=SLLBegin(new_sll);

    SLLInsert(curr, &new_data1);
    curr=SLLNext(curr);
    SLLInsert(curr, &new_data2);
    curr=SLLNext(curr);
    SLLInsert(curr, &new_data3);

    SLLRemove(curr);

    assert(2==SLLCount(new_sll));

    SLLDestroy(new_sll);
}

int TestMatchString(sll_iterator curr, void *param)
{
    return strcmp(SLLGet(curr),param);
}


void TestFindString()
{
    char *name="Sigal";
    char *last_name="Tal";
    char *rock="rocks";

    char *find_str="Sigal";

    sll_t *new_sll=SLLCreate();

    sll_iterator curr=SLLBegin(new_sll);

    SLLInsert(curr, name);
    curr=SLLNext(curr);
    SLLInsert(curr, last_name);
    curr=SLLNext(curr);
    SLLInsert(curr, rock);

    curr= SLLFind(SLLBegin(new_sll), SLLEnd(new_sll),find_str, TestMatchString);

    assert(1==SLLIteratorsIsEqual(SLLBegin(new_sll),curr));

    SLLDestroy(new_sll);
}


void TestForEach()
{
    sll_t *sll=SLLCreate();
    sll_iterator start=SLLBegin(sll);
    sll_iterator itr=SLLBegin(sll);


    int x = 11;
    int a = 22;
    int y = 33;
    int b = 44;
    int plus = 10;

    SLLInsert(SLLEnd(sll),&x);
    SLLInsert(SLLEnd(sll),&a);
    SLLInsert(SLLEnd(sll),&y);
    SLLInsert(SLLEnd(sll),&b);
    
    SLLForEach(SLLBegin(sll), SLLEnd(sll), &plus, ActionInt);

    itr=start;
    if (21 != *(int*)SLLGet(itr))
        {
            printf("error foreach\n");
        }

    itr = SLLNext(itr);
    if (32 != *(int*)SLLGet(itr))
        {
            printf("error foreach\n");
        }

    itr = SLLNext(itr);
    if (43 != *(int*)SLLGet(itr))
        {
            printf("error foreach\n");
        }

    itr = SLLNext(itr);
    if (54 != *(int*)SLLGet(itr))
        {
            printf("error foreach\n");
        }
    

    SLLDestroy(sll);
}

int ActionInt (sll_iterator curr, void *param)
{
    int *new = (int*)SLLGet(curr);
    *new += *(int*)param;
    
    return 0;
}

int SetStr(sll_iterator curr, void *param)
{
   SLLSetData(curr,param);
   return 0;
}

void TestForEachString()
{
    char name[]="Sigal";
    char last_name[]="Tal";
    char rock[]="rocks";

    char param[]="AAA";

    sll_t *new_sll=SLLCreate();

    sll_iterator iter1=SLLBegin(new_sll);
    sll_iterator iter2=SLLBegin(new_sll);
    sll_iterator iter3=SLLBegin(new_sll);

    SLLInsert(iter1, name);
    iter2=SLLNext(iter1);
    SLLInsert(iter2, last_name);
    iter3=SLLNext(iter2);
    SLLInsert(iter3, rock);

    SLLForEach(SLLBegin(new_sll), SLLEnd(new_sll),param, SetStr);

    assert(SLLGet(iter1)==param);
    assert(SLLGet(iter2)==param);
    assert(SLLGet(iter3)==param);

    SLLDestroy(new_sll);
}

void TestSLLAppend()
{
    int new_data1=1;
    int new_data2=2;
    int new_data3=3;

    int data4=4;
    int data5=5;
    int data6=6;

    sll_t *new_sll1=SLLCreate();

    sll_t *new_sll2=SLLCreate();

    sll_iterator curr1=SLLBegin(new_sll1);

    sll_iterator curr2=SLLBegin(new_sll2);

    sll_iterator start=SLLBegin(new_sll1);
    sll_iterator itr=SLLBegin(new_sll1);

    SLLInsert(curr1, &new_data1);
    curr1=SLLNext(curr1);
    SLLInsert(curr1, &new_data2);
    curr1=SLLNext(curr1);
    SLLInsert(curr1, &new_data3);

    SLLInsert(curr2, &data4);
    curr2=SLLNext(curr2);
    SLLInsert(curr2, &data5);
    curr2=SLLNext(curr2);
    SLLInsert(curr2, &data6);

    SLLAppend(new_sll1, new_sll2);

    assert(SLLCount(new_sll1)==6);

    itr=start;
    if (1 != *(int*)SLLGet(itr))
        {
            printf("error foreach\n");
        }

    itr = SLLNext(itr);
    if (2 != *(int*)SLLGet(itr))
        {
            printf("error foreach\n");
        }

    itr = SLLNext(itr);
    if (3 != *(int*)SLLGet(itr))
        {
            printf("error foreach\n");
        }

    itr = SLLNext(itr);
    if (4 != *(int*)SLLGet(itr))
        {
            printf("error foreach\n");
        }

        itr = SLLNext(itr);
    if (5 != *(int*)SLLGet(itr))
        {
            printf("error foreach\n");
        }
        itr = SLLNext(itr);
    if (6 != *(int*)SLLGet(itr))
        {
            printf("error foreach\n");
        }

    SLLDestroy(new_sll1);
}


