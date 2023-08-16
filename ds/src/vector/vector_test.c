/*********************************
 * Reviewer:            
 * Author: Sigal Tal       
 * File: vector_test.c          
 * ******************************/
#include <stddef.h>/*size_t*/
#include <assert.h>
#include "vector.h"

void TestVectorInit();
void TestVectorAddElement();
void TestVectorResize();
void TestVectorPop();
void TestVectorShrinkToFit();
void TestVectorReserve();
void TestVectorChangeElement();


int main()
{
    TestVectorInit();
    TestVectorAddElement();
    TestVectorResize();
    TestVectorPop();
    TestVectorShrinkToFit();
    TestVectorReserve();
    TestVectorChangeElement();
    
    return 0;
}

void TestVectorInit()
{
    size_t capacity=5;
    size_t element_size=4;
    vector_t *vec_test=VectorCreate(capacity, element_size);

    assert(1==VectorIsEmpty(vec_test));
    assert(0==VectorSize(vec_test));
    assert(capacity==VectorCapacity(vec_test));

    VectorDestroy(vec_test);
}

void TestVectorAddElement()
{
    size_t capacity=5;
    size_t element_size=4;
    int element_to_push1=1;
    int element_to_push2=2;
    vector_t *vec_test=VectorCreate(capacity, element_size);

    VectorPush(vec_test, &element_to_push1);
    VectorPush(vec_test, &element_to_push2);

    assert(0==VectorIsEmpty(vec_test));
    assert(2==VectorSize(vec_test));
    assert(element_to_push1==*(int *)(VectorGetAccess(vec_test, 0)));
    assert(element_to_push2==*(int *)(VectorGetAccess(vec_test, 1)));

    VectorDestroy(vec_test);
}

void TestVectorResize()
{
    size_t capacity=2;
    size_t element_size=4;
    int element_to_push1=1;
    int element_to_push2=2;
    int element_to_push3=3;
    vector_t *vec_test=VectorCreate(capacity, element_size);

    VectorPush(vec_test, &element_to_push1);
    VectorPush(vec_test, &element_to_push2);
    VectorPush(vec_test, &element_to_push3);

    assert(0==VectorIsEmpty(vec_test));
    assert(3==VectorSize(vec_test));
    assert(capacity*2==VectorCapacity(vec_test));
    assert(element_to_push3==*(int *)(VectorGetAccess(vec_test, 2)));

    VectorDestroy(vec_test);
}

void TestVectorPop()
{
    size_t capacity=2;
    size_t element_size=4;
    int element_to_push1=1;
    int element_to_push2=2;
    int element_to_push3=3;
    vector_t *vec_test=VectorCreate(capacity, element_size);

    VectorPush(vec_test, &element_to_push1);
    VectorPush(vec_test, &element_to_push2);
    VectorPush(vec_test, &element_to_push3);

    VectorPop(vec_test);

    assert(0==VectorIsEmpty(vec_test));
    assert(2==VectorSize(vec_test));
    assert(capacity*2==VectorCapacity(vec_test));
    assert(element_to_push2==*(int *)(VectorGetAccess(vec_test,(int)VectorSize(vec_test)-1)));

    VectorDestroy(vec_test);
}

void TestVectorShrinkToFit()
{
    size_t capacity=2;
    size_t element_size=4;
    int element_to_push1=1;
    int element_to_push2=2;
    int element_to_push3=3;
    vector_t *vec_test=VectorCreate(capacity, element_size);

    VectorPush(vec_test, &element_to_push1);
    VectorPush(vec_test, &element_to_push2);
    VectorPush(vec_test, &element_to_push3);

    VectorShrinkToFit(vec_test);
    assert(0==VectorIsEmpty(vec_test));
    assert(VectorSize(vec_test)==VectorCapacity(vec_test));
    assert(element_to_push3==*(int *)(VectorGetAccess(vec_test,(int)VectorSize(vec_test)-1)));

    VectorDestroy(vec_test);
}

void TestVectorReserve()
{
    size_t capacity=2;
    size_t new_capacity=5;
    size_t element_size=4;
    int element_to_push1=1;
    int element_to_push2=2;
    vector_t *vec_test=VectorCreate(capacity, element_size);

    VectorPush(vec_test, &element_to_push1);
    VectorPush(vec_test, &element_to_push2);

    VectorReserve(vec_test,new_capacity);

    assert(new_capacity==VectorCapacity(vec_test));
    assert(element_to_push2==*(int *)(VectorGetAccess(vec_test,(int)VectorSize(vec_test)-1)));

    VectorDestroy(vec_test);
}

void TestVectorChangeElement()
{
    size_t capacity=2;
    size_t element_size=4;
    int element_to_push1=1;
    int element_to_push2=2;
    int element_to_push3=3;
    vector_t *vec_test=VectorCreate(capacity, element_size);

    VectorPush(vec_test, &element_to_push1);
    VectorPush(vec_test, &element_to_push2);
    VectorPush(vec_test, &element_to_push3);
    *(int *)(VectorGetAccess(vec_test,1))=9;

    assert(0==VectorIsEmpty(vec_test));
    assert(3==VectorSize(vec_test));
    assert(capacity*2==VectorCapacity(vec_test));
    assert(9==*(int *)(VectorGetAccess(vec_test,1)));

    VectorDestroy(vec_test);
}

