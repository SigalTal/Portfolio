#include <assert.h>
#include "comparison_sorts.h"

static void Swap(int *x, int *y);

void BubbleSort(int* array, size_t size)
{
    size_t i=0, j=0;

    assert(array);

    for(i=0;i<size-1;++i)
    {
        for(j=0;j<size-i-1;++j)
        {
            if(array[j]>array[j+1])
            {
                Swap(array+j,array+j+1);
            }
        }
    }
}

static void Swap(int *x, int *y)
{
    int tmp=0;
    tmp=*x;
    *x=*y;
    *y=tmp;
}

void SelectionSort(int* array, size_t size)
{
    size_t i=0, j=0, min_index=0;

    assert(array);


    for(i=0;i<size-1;++i)
    {
        min_index=i;
        
        for(j=i+1;j<size;++j)
        {
            if(array[j]<array[min_index])
            {
                min_index=j;
            }
        }

        if(i!=min_index)
        {
           Swap(array+i,array+min_index); 
        }
    }
}


void InsertionSort(int* array, size_t size)
{
    size_t i=0, j=0;
    int key=0;

    assert(array);

    for(i=1;i<size;++i)
    {
        key=array[i];
        j=i-1;

        while((j+1)>0 && key<array[j])
        {
            array[j+1]=array[j];
            --j;
        }

        array[j+1]=key;
    }
}