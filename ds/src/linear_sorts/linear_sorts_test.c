/*********************************
 * Reviewer: Kobi          
 * Author: Sigal Tal       
 * File: linear_sort_test.c          
 * ******************************/

#include <stdio.h>/**printf*/
#include <stdlib.h>/*malloc - free*/
#include "linear_sorts.h"

static void PrintArr(int *arr, size_t size);
static int IsSorted(int *arr, size_t size);
void SmallTest(void);
void RdixSmallTest(void);

int main(int argc, char const *argv[])
{

    size_t i=0, size=0;
    int *array=NULL;

    if(argc<2)
    {
        printf("error");
    }

    size=atoi(argv[1]);
    array=(int *)malloc(sizeof(int)*size);

    for(i=0; i<size;i++)
    {
        array[i]=1000000 + rand() % 9999999;
    }

    RadixSort(array, size);

/*    CountingSort(array, size);*/

    if(!IsSorted(array, size))
    {
        printf("error2\n");
    }

    free(array);
   RdixSmallTest();
    /*SmallTest();
    */
    return 0;
}

void SmallTest(void)
{
    int array[7]={1,4,1,2,7,5,2};

    CountingSort(array, 7);
    PrintArr(array,7);
}

void RdixSmallTest(void)
{
    /*int array[8]={170,45,75,90,802,24,2,66};*/

    int array[8]={1,4,1,2,7,5,2,6};

   /* int array[8]={234,55677,134000,45300,33123,67891,3456,990578};*/

    RadixSort(array, 8);
    PrintArr(array,8);
}

static void PrintArr(int *arr, size_t size)
{
    size_t i=0;
    for(i=0;i<size;++i)
    {
        printf("%d ,",arr[i]);
    }

    printf("\n");
}

static int IsSorted(int *arr, size_t size)
{
    size_t i=0;
    for(i=1;i<size;++i)
    {
        if(arr[i-1]>arr[i])
        {
            return 0;
        }
    }

    return 1;
}