#include <stdio.h>/*printf*/
#include <stdlib.h>/*maaloc*/
#include "comparison_sorts.h"

static void PrintArr(int *arr, size_t size);
void BasicTest();
int IsSorted(int *arr, size_t size);
int ComperInt(const void *a, const void *b);

int main(int argc, char const *argv[])
{
	size_t i=0, size=0;
	int *array=NULL;

	if(argc<3)
	{
		printf("error");
	}

	size=atoi(argv[2]);
	array=(int *)malloc(sizeof(int)*size);

	for(i=0; i<size;i++)
	{
		array[i]=rand();
	}

	switch(argv[1][0])
	{
	case 'b':
		BubbleSort(array, size);
		break;
	case 'i':
		InsertionSort(array, size);
		break;
	case 's':
		SelectionSort(array, size);
		break;
	case 'q':
		qsort(array, size, sizeof(int),ComperInt);
		break;
	default:
		break;
	}

	if(!IsSorted(array, size))
	{
		printf("error\n");
	}

	free(array);

	/*BasicTest();*/

	return 0;
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

void BasicTest()
{
	int arr1[]={12,11,13,5,6};
	int arr2[]={12,11,13,5,6};
	int arr3[]={12,11,13,5,6};

	BubbleSort(arr1, 5);
	PrintArr(arr1, 5);

	InsertionSort(arr2, 5);
	PrintArr(arr2, 5);

	SelectionSort(arr3, 5);
	PrintArr(arr3, 5);
}

int IsSorted(int *arr, size_t size)
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

int ComperInt(const void *a, const void *b)
{
	return (*(int *)a-*(int *)b);
}
