/*********************************
 * Reviewer: 
 * Author: Sigal
 * File Name: fsa.h
 * ******************************/
/*#include <stdio.h>
#include <stdlib.h>
#include "fsa.h"

void QuiqTest(void);

int main()
{
    QuiqTest();


    return 0;
}


void QuiqTest(void)
{
    void *pool=malloc(40);
    void *alloc1=NULL;
    void *alloc2=NULL;
    void *alloc3=NULL;
    fsa_t *fsa=NULL;
    printf("pool:%p\n",pool);

    fsa=FSAInit(pool, 40, 12);
    printf("size:%lu\n",FSACountFree(fsa));
    printf("fsa: %p\n",fsa);
    printf("suggested time:%lu\n",FSASuggestSize(12, 10));

    alloc1=FSAAlloc(fsa);
    printf("alloc1: %p\n",alloc1);
    printf("size:%lu\n",FSACountFree(fsa));
    alloc2=FSAAlloc(fsa);
    printf("alloc2: %p\n",alloc2);
    printf("size:%lu\n",FSACountFree(fsa));

    printf("diff: %lu",(size_t)alloc2-(size_t)alloc1);

    FSAFree(fsa, alloc2);
    FSAFree(fsa, alloc1);

   alloc3=FSAAlloc(fsa);
    printf("alloc3 affter free: %p\n",alloc3);

    free(pool);
}*/

#include <stdlib.h>
#include <stdio.h>
#include "fsa.h"


static void *Align(size_t what, size_t to)
{
    return (void *)((what - 1 + to) & -to);
}


void SuggestTest();
void InitTest();
void AllocTest();
void CountFreeTest();
void FreeTest();


int main()
{
    SuggestTest();
    InitTest();
    AllocTest();
    AllocTest();
    CountFreeTest();
    FreeTest();

    printf("the end\n");
    return 0;
}


void SuggestTest()
{
    size_t size=0;

    printf("___SuggestTest___\n");

    size=FSASuggestSize(10,5);
    if(95 != size)
    {
        printf("suggest error, got %lu, expected 95\n", size);
    }

    size=FSASuggestSize(14,5);
    if(95 != size)
    {
        printf("suggest error, got %lu, expected 95\n", size);
    }

    size=FSASuggestSize(5,2);
    if(31 != size)
    {
        printf("suggest error, got %lu, expected 31\n", size);
    }
}


void InitTest()
{
    void *pool1=malloc(31);
    fsa_t *fsa1=NULL;

    void *pool2=malloc(40);
    fsa_t *fsa2=NULL;
 
    printf("___InitTest___\n");

    fsa1=FSAInit(pool1,31,5);

    fsa2=FSAInit(pool2,20,12);

    if((fsa_t *)Align((size_t)pool1,sizeof(size_t)) != fsa1)
    {
        printf("init error,  got: %p\nexpected address: %p\n",(void*)fsa1,Align((size_t)pool1,sizeof(size_t)));
    }   

    if(NULL != fsa2)
    {
        printf("init error, got address: %p, expected NULL\n",(void*)fsa1);

    }   
    free(pool1);
    free(pool2);
}


void AllocTest()
{
    void *pool=malloc(31);
    fsa_t *fsa=FSAInit(pool,31,5);
    size_t aligned_admin_struct_size = 8;
    size_t start_address = (size_t)fsa + aligned_admin_struct_size;

    void *block1=NULL;  
    void *block2=NULL;  
    void *block3=NULL;  

    printf("___AllocTest___\n");
    block1=FSAAlloc(fsa);   
    block2=FSAAlloc(fsa);   
    block3=FSAAlloc(fsa);   
    
    if(0 != (size_t)block1-start_address)
    {
        printf("alloc error 1,got offset=%lu, expected 0\n",(size_t)block1-start_address);
    }
    if(8 != (size_t)block2-start_address)
    {
        printf("alloc error 2,got offset=%lu, expected 0\n",(size_t)block2-start_address);
    }
    if(NULL != block3)
    {
        printf("alloc error 3, expected NULL\n");
    }

    free(pool);

}


void CountFreeTest()
{
    void *pool=malloc(31);
    fsa_t *fsa=FSAInit(pool,31,5);
    size_t count=-1;

    printf("___CountFreeTest___\n");

    count=FSACountFree(fsa);
    if(2 != count)
    {
        printf("count error 1, got =%lu, expected 2\n",count);
    }

    FSAAlloc(fsa);
    count=FSACountFree(fsa);
    if(1 != count)
    {
        printf("count error 2, got =%lu, expected 1\n",count);
    }

    FSAAlloc(fsa);  
    count=FSACountFree(fsa);
    if(0 != count)
    {
        printf("count error 3, got =%lu, expected 0\n",count);
    }

    free(pool);

}

 
void FreeTest()/*write test*/
{
    void *pool=malloc(100);
    fsa_t *fsa=FSAInit(pool,100,5);

    void *block1=NULL;  
    void *block2=NULL;  
    void *block3=NULL;  

    printf("___FreeTest___\n");
    block1=FSAAlloc(fsa);   
    block2=FSAAlloc(fsa);   
    block3=FSAAlloc(fsa);


    FSAFree(fsa,block1);
    FSAFree(fsa,block2);
    FSAFree(fsa,block3);

    free(pool);
}