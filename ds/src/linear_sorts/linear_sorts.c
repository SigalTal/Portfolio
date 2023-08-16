/*********************************
 * Reviewer: Kobi           
 * Author: Sigal Tal       
 * File: linear_sort.c          
 * ******************************/

#include <stdlib.h>/*malloc - free*/
#include <stddef.h>/*size_t*/
#include <assert.h>
#include "linear_sorts.h"

static int FindMax(int *array, size_t size);
static void RadixCountingSort(int* array, size_t size, int exp);
/*static int FindMin(int *array, size_t size);*/

void CountingSort(int* array, size_t size)
{
    int max_num=0;
    size_t i=0;
    int *count=NULL;
    int *sorted_arr=NULL;

    assert(array);

    max_num=FindMax(array, size);

    count=(int *)calloc((max_num+1),sizeof(int));
    if(!count)
    {
        return;
    }

    /*histogram- Count the number of times it is in the array*/
    for(i=0;i<size;++i)
    {
        ++count[array[i]];
    }

    /*sums the valuse */
    for(i=1;i<(size_t)max_num;++i)
    {
        count[i]+=count[i-1];
    }

    /*shift to the right*/
    for(i=max_num;i>0;--i)
    {
        count[i]=count[i-1];
    }

    count[0]=0;

    sorted_arr=(int *)calloc(size, sizeof(int));
    if(!sorted_arr)
    {
        return;
    }

    /*places the numbers in sorted order*/
    for(i=0;i<size;++i)
    {
        sorted_arr[count[array[i]]]=array[i];
        ++count[array[i]];
    }

    /*copies to the origenal array*/
    for(i=0;i<size;++i)
    {
        array[i]=sorted_arr[i];
    }

    free(count);
    count=NULL;
    free(sorted_arr);
    sorted_arr=NULL;
}

void RadixSort(int* array, size_t size)
{
    int max_num=0;
    int exp=1;

    assert(array);

    max_num=FindMax(array, size);

    for(exp=1; max_num/exp>0; exp*=10)
    {
        RadixCountingSort(array, size, exp);
    }
}

static void RadixCountingSort(int* array, size_t size, int exp)
{
    int max_num=0,index=0;
    size_t i=0;
    int *count=NULL;
    int *sorted_arr=NULL;

    assert(array);

    for(i=0; i<size; ++i)
    {
        if(max_num<(array[i]/exp)%10)
        {
            max_num=(array[i]/exp)%10;
        }
    }

    count=(int *)calloc(max_num+1,sizeof(int));
    if(!count)
    {
        return;
    }

    /*histogram- Count the number of times it is in the array*/
    for(i=0;i<size;++i)
    {
        index=(array[i]/exp)%10;
        ++count[index];
    }

    /*sums the valuse */
    for(i=1;i<(size_t)max_num+1;++i)
    {
        count[i]+=count[i-1];
    }

    /*shift to the right*/
    for(i=(size_t)max_num;i>0;--i)
    {
        count[i]=count[i-1];
    }

    count[0]=0;

    sorted_arr=(int *)calloc(size, sizeof(int));
    if(!sorted_arr)
    {
        return;
    }

    /*places the numbers in sorted order*/
    for(i=0;i<size;++i)
    {
        index=(array[i]/exp)%10;
        sorted_arr[count[index]]=array[i];
        ++count[index];
    }

    /*copies to the origenal array*/
    for(i=0;i<size;++i)
    {
        array[i]=sorted_arr[i];
    }

    free(count);
    count=NULL;
    free(sorted_arr);
    count=NULL;
}

static int FindMax(int *array, size_t size)
{
    size_t i=0;
    int max_num=0;

    assert(array);

    for(i=0;i<size;++i)
    {
        if(max_num<array[i])
        {
            max_num=array[i];
        }
    }

    return max_num;
}

/*static int FindMin(int *array, size_t size)
{
    size_t i=0;
    int min_num=0;

    assert(array);

    min_num=array[0];

    for(i=0;i<size;++i)
    {
        if(min_num>array[i])
        {
            min_num=array[i];
        }
    }

    return min_num;
}*/