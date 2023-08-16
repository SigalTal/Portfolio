/*********************************
 * Reviewer: 
 * Author: 		
 * File: bst_test.c
 * ******************************/
#include <stdio.h>
#include <assert.h>
#include "bst.h"

typedef struct person
{
    int ID;
    int age;
}person_t;

void QuiqTest(void);
static int IDCompare(const void *a_data, const void *b_data, void *user_param);

int main()
{
    QuiqTest();
    
    return 0;
}

static int IDCompare(const void *a_data, const void *b_data, void *user_param)
{
    assert(a_data);
    assert(b_data);

    (void)(user_param);

    return ((person_t*)b_data)->ID-((person_t*)a_data)->ID;
}

void QuiqTest(void)
{
    bst_t *bst=BSTCreate(IDCompare,NULL);
    bst_iterator_t iter1, iter2, iter3;

    person_t Sigal={1234,28};
    person_t Shani={5678,19};
    person_t Ariel={27,1};
    person_t Almog={135,29};

    assert(1==BSTIsEmpty(bst));

    BSTInsert(bst,&Sigal);

    assert(0==BSTIsEmpty(bst));

    iter1=BSTInsert(bst,&Shani);

    BSTInsert(bst,&Ariel);

    iter2=BSTFind(bst,&Shani);

    assert(1==BSTIsSameIter(iter1,iter2));

    assert((person_t *)BSTGetData(BSTEnd(bst))==NULL);

    BSTInsert(bst,&Almog);

    iter2=BSTFind(bst,&Ariel);

    iter3=BSTNext(iter2);

    assert(((person_t *)BSTGetData(iter3))->ID==Almog.ID);



/*  printf("%d",(((person_t *)BSTGetData(BSTEnd(bst)))->ID));*/

}