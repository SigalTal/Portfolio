/*********************************
 * Reviewer:Sivan            
 * Author: Sigal Tal       
 * File: stack_test.c          
 * ******************************/

#include <assert.h>
#include <string.h>/*memcmp*/
#include "stack.h"

typedef struct stack_test
{
    char* stack;
    size_t element_size;
    size_t capacity;
    int size;
}stack_test_t;

void TestStackCreateAndStackDestroy(void)
{
	size_t capacity=5;
	size_t  element_size=4;

	stack_t *stack_ptr=StackCreate(capacity, element_size);
	stack_test_t *stack_local=(stack_test_t *)stack_ptr;
	assert(stack_local);
	assert(stack_local->element_size==element_size);
	assert(stack_local->capacity==capacity);
	assert(stack_local->size==0);
	(void)(stack_local);

	StackDestroy(stack_ptr);
}

void TestStackSize(void)
{
	size_t capacity=5;
	size_t  element_size=4;

	stack_t *stack_ptr=StackCreate(capacity, element_size);
	stack_test_t *stack_local=(stack_test_t *)stack_ptr;

	assert(stack_local->size==0);
	(void)(stack_local);

	StackDestroy(stack_ptr);
}

void TestStackCapacity(void)
{
	size_t capacity=5;
	size_t  element_size=4;

	stack_t *stack_ptr=StackCreate(capacity, element_size);
	stack_test_t *stack_local=(stack_test_t *)stack_ptr;

	assert(stack_local->capacity==capacity);
	(void)(stack_local);

	StackDestroy(stack_ptr);
}

void TestStackIsEmpty(void)
{
	size_t capacity=5;
	size_t  element_size=4;

	stack_t *stack_ptr=StackCreate(capacity, element_size);
	stack_test_t *stack_local=(stack_test_t *)stack_ptr;

	assert(stack_local->size==0);
	(void)(stack_local);

	StackDestroy(stack_ptr);
}
stack_t *CreatAndPushAndAssert(void)
{
	size_t capacity=5;
	size_t  element_size=4;
	int element_to_push=3;


	stack_t *stack_ptr=StackCreate(capacity, element_size);
	stack_test_t *stack_local=(stack_test_t *)stack_ptr;
	StackPush(stack_ptr,&element_to_push);

	assert(*(stack_local->stack)==element_to_push);
	(void)(stack_local);

	return stack_ptr;
}

void TestStackPush(void)
{
	stack_t *stack_ptr=CreatAndPushAndAssert();

	StackDestroy(stack_ptr);
}

void TestStackPeek(void)
{
	int store_element=0;

	stack_t *stack_ptr=CreatAndPushAndAssert();
	stack_test_t *stack_local=(stack_test_t *)stack_ptr;

	StackPeek(stack_ptr, &store_element);

	assert(0==memcmp(&store_element,stack_local->stack+((stack_local->size-1)*stack_local->element_size),stack_local->element_size));
	(void)(stack_local);
	
	StackDestroy(stack_ptr);
}

void TestStackPop(void)
{
	stack_t *stack_ptr=CreatAndPushAndAssert();
	stack_test_t *stack_local=(stack_test_t *)stack_ptr;

	StackPop(stack_ptr);

	assert(0==stack_local->size);
	(void)(stack_local);

	StackDestroy(stack_ptr);
}

int main()
{
	TestStackCreateAndStackDestroy();
	TestStackSize();
	TestStackCapacity();
	TestStackIsEmpty();
	TestStackPush();
	TestStackPeek();
	TestStackPop();

	
	return 0;
}