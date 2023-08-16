/*********************************
 * Reviewer:Nofar 
 * Author: Sigal
 * File Name: merge_quick_test.c
 * ******************************/
#include <stdio.h>/*printf*/
#include <assert.h>
#include "merge_quick.h"
void TestBinery();
int is_before(const void *a, const void *b);
void TestMeregSort();
void TestQuickSort();


int main()
{
    TestBinery();
    TestMeregSort();
    TestQuickSort();

    return 0;
}


void TestBinery()
{
    int array[]={1,2,3,4,5,6,7,8,9};

    int res=0, res_rec=0;

    res=IterBinarySearch(array, 9 ,9);

    assert(res==8);

    res_rec=RecurBinarySearch(array, 9 ,1);

    assert(res_rec==0);
}

void TestMeregSort()
{
    int array[]={9,4,5,1,2,7,3,3,1,-1};
    size_t i=0;
    size_t size_arr=10;
    MergeSort(array, size_arr, 4, is_before);

    for(i=0;i<size_arr;++i)
    {
        printf("%d, ",array[i]);
    }

    printf("\n");

}

int is_before(const void *a, const void *b)
{
    assert(a);
    assert(b);
    return *(int *)a<*(int *)b;
}

void TestQuickSort()
{
    int array[]={2,8,5,3,9,4,1,0};
    size_t i=0;
    size_t size_arr=8;
    QuickSort(array, size_arr, 4, is_before);

    for(i=0;i<size_arr;++i)
    {
        printf("%d, ",array[i]);
    }

    printf("\n");
}
