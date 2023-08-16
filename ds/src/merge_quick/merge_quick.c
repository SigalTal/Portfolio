/*********************************
 * Reviewer:Nofar
 * Author: Sigal
 * File Name: merge_quick.c
 * ******************************/
#include <stdlib.h>/*malloc - free*/
#include <string.h>/*memcpy*/
#include <assert.h>
#include "merge_quick.h"

static int HelpRecBinarySeatch(int *array, size_t high, size_t low, int data_to_find);
static int RecMergeSort(void *arr_to_sort, size_t left, size_t right, size_t elem_size, int (*is_before)(const void *elem1, const void *elem2));
static int Merge(void *arr_to_sort, size_t left, size_t right, size_t elem_size, int (*is_before)(const void *elem1, const void *elem2));
static void Swap(void *a, void *b, void *tmp, size_t elem_size);
static void RecQuickSort(void *arr_to_sort, void *tmp_to_swap, size_t left, size_t right, size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2));
static size_t Partition(void *arr_to_sort, void *tmp_to_swap, size_t left, size_t right, size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2));

int IterBinarySearch(int *array, size_t arr_size, int data_to_find)
{
    int low = 0, high = arr_size - 1, mid = 0;

    assert(array);

    while (high >= low)
    {
        mid = (high + low) / 2;
        if (data_to_find == *(array + mid))
        {
            return mid;
        }

        else if (data_to_find < *(array + mid))
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return -1;
}

int RecurBinarySearch(int *array, size_t arr_size, int data_to_find)
{
    int low = 0, high = arr_size;

    assert(array);

    return HelpRecBinarySeatch(array, high, low, data_to_find);
}

static int HelpRecBinarySeatch(int *array, size_t high, size_t low, int data_to_find)
{
    int mid = 0;

    if (high < low)
    {
        return -1;
    }

    mid = (high + low) / 2;

    if (data_to_find == array[mid])
    {
        return mid;
    }

    if (data_to_find < *(array + mid))
    {
        high = mid - 1;
        return HelpRecBinarySeatch(array, high, low, data_to_find);
    }
    else
    {
        low = mid + 1;
        return HelpRecBinarySeatch(array, high, low, data_to_find);
    }
}

int MergeSort(void *arr_to_sort, size_t num_elements, size_t elem_size, 
                int (*is_before)(const void *elem1, const void *elem2))
{
    size_t left = 0, right = num_elements - 1;

    assert(arr_to_sort);
    assert(is_before);

    return RecMergeSort(arr_to_sort, left, right, elem_size, is_before);
}

static int RecMergeSort(void *arr_to_sort, size_t left, size_t right, size_t elem_size, int (*is_before)(const void *elem1, const void *elem2))
{
    size_t mid = 0;

    if (left >= right)
    {
        return 0;
    }

    mid = (right + left) / 2;

    RecMergeSort(arr_to_sort, left, mid, elem_size, is_before);

    RecMergeSort(arr_to_sort, mid + 1, right, elem_size, is_before);

    return Merge(arr_to_sort, left, right, elem_size, is_before);
}

static int Merge(void *arr_to_sort, size_t left, size_t right, size_t elem_size, int (*is_before)(const void *elem1, const void *elem2))
{
    size_t mid = (left + right) / 2;
    size_t size_left_arr = mid - left + 1;
    size_t size_right_arr = right - mid;
    size_t i = 0, j = 0, k = left;

    char *left_element = NULL;
    char *right_element = NULL;
    char *dest_address = NULL;

    void *right_arr = NULL;
    void *left_arr = NULL;

    right_arr = malloc(elem_size * size_right_arr);
    if (!right_arr)
    {
        return 1;
    }
    left_arr = malloc(elem_size * size_left_arr);
    if (!left_arr)
    {
        return 1;
    }

    memcpy(left_arr, (char *)arr_to_sort + (left * elem_size), size_left_arr * elem_size);
    memcpy(right_arr, (char *)arr_to_sort + ((mid + 1) * elem_size), size_right_arr * elem_size);

    while (i < size_left_arr && j < size_right_arr)
    {
        left_element = ((char *)(left_arr) + i * elem_size);
        right_element = ((char *)(right_arr) + j * elem_size);
        dest_address = ((char *)(arr_to_sort) + k * elem_size);
        if (is_before(left_element, right_element))
        {
            memcpy(dest_address, left_element, elem_size);
            ++i;
            ++k;
        }
        else
        {
            memcpy(dest_address, right_element, elem_size);
            ++j;
            ++k;
        }
    }

    dest_address = ((char *)(arr_to_sort) + k * elem_size);
    left_element = ((char *)(left_arr) + i * elem_size);
    right_element = ((char *)(right_arr) + j * elem_size);

    memcpy(dest_address, left_element, elem_size*(size_left_arr-i));

    memcpy(dest_address, right_element, elem_size*(size_right_arr-j));

    free(right_arr);
    free(left_arr);

    return 0;
}

int QuickSort(void *arr_to_sort, size_t num_elements, size_t elem_size, int(*is_before)(const void *elem1, const void *elem2))
{
    size_t left = 0, right = num_elements - 1;
    void *tmp_to_swap=NULL;
    
    assert(arr_to_sort);
    assert(is_before);
    
    tmp_to_swap=malloc(elem_size);
    if(!tmp_to_swap)
    {
        return -1;
    }

    RecQuickSort(arr_to_sort, tmp_to_swap, left, right, elem_size,is_before);

    free(tmp_to_swap);
    tmp_to_swap=NULL;

    return 0;

}

static void RecQuickSort(void *arr_to_sort, void *tmp_to_swap ,size_t left, size_t right, size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2))
{
    size_t partition_index = 0;

    if ((long)left >= (long)right)
    {
        return;
    }

    partition_index = Partition(arr_to_sort,tmp_to_swap, left,right, elem_size ,is_before);

    RecQuickSort(arr_to_sort,tmp_to_swap, left, partition_index-1, elem_size, is_before);

    RecQuickSort(arr_to_sort,tmp_to_swap, partition_index+1, right, elem_size, is_before);
}

static size_t Partition(void *arr_to_sort, void *tmp_to_swap, size_t left, size_t right, size_t elem_size, 
                        int (*is_before)(const void *elem1, const void *elem2))
{
    size_t i= left-1;
    size_t j=left;
    size_t pivot_index=right;
    void *pivot=NULL;
    void *elem_addres=NULL;
    void *smaller_elem_adress=NULL;

    pivot =(void *)((char *)arr_to_sort+(elem_size*right));

    for(j=left;j<right;++j)
    {
        elem_addres=(void *)((char *)arr_to_sort+(j*elem_size));
        
        if(is_before(elem_addres,pivot))
        {
            ++i;
            smaller_elem_adress=(char *)arr_to_sort+(i*elem_size);
            Swap(smaller_elem_adress,elem_addres,tmp_to_swap, elem_size);
        }
    }

    smaller_elem_adress=(char *)arr_to_sort+((i+1)*elem_size);

    Swap(smaller_elem_adress, pivot, tmp_to_swap, elem_size);

    pivot_index=i+1;

    return pivot_index;
}


static void Swap(void *a, void *b, void *tmp, size_t elem_size)
{
    assert(a);
    assert(b);
    assert(tmp);
    memcpy(tmp,a,elem_size);
    memcpy(a,b,elem_size);
    memcpy(b,tmp,elem_size);
}