/*********************************
 * Reviewer: Daniel Natan
 * Author: Sigal Tal    
 * File: AVL_test.c
 * ******************************/
#include <stdio.h>/*printf*/
#include <assert.h>
#include "avl.h"

typedef struct person
{
    int ID;
    int age;
}person_t;

static int IDCompare(const void *a_data, const void *b_data, void *user_param);
static int AddOne(void *data, void *user_param);
void TestQuiq();

int main()
{
    TestQuiq();

    
    return 0;
}

static int AddOne(void *data, void *user_param)
{
    (void)(user_param);
    ++((person_t *)data)->age;
    return 0;
}

static int IDCompare(const void *a_data, const void *b_data, void *user_param)
{
    assert(a_data);
    assert(b_data);

    (void)(user_param);

    return ((person_t*)b_data)->ID-((person_t*)a_data)->ID;
}

void TestQuiq()
{
    avl_t *avl=AvlCreate(IDCompare,NULL);

    person_t sigal={30,28};
    person_t shani={40,20};
    person_t ariel={20,1};
    person_t almog={45,29};
    person_t sheli={35,20};
    person_t tania={34,29};
    person_t moshe={4,29};
    person_t found={0};
    person_t *found_ptr=NULL;

    printf("sigal: %p\n",(void *)&sigal);
    printf("shani: %p\n",(void *)&shani);
    printf("ariel: %p\n",(void *)&ariel);
    printf("almog: %p\n",(void *)&almog);
    printf("sheli: %p\n",(void *)&sheli);
    printf("tania: %p\n",(void *)&tania);


    assert(1==AvlIsEmpty(avl));

    AvlInsert(avl,&sigal);
    AvlInsert(avl,&shani);
    AvlInsert(avl,&ariel);
    AvlInsert(avl,&almog);
    AvlInsert(avl,&sheli);
    AvlInsert(avl,&tania);

    assert(6==AvlSize(avl));

    assert(2==AvlHeight(avl));


    assert(0==AvlIsEmpty(avl));

    found_ptr=(person_t*)AvlFind(avl,&moshe);

    assert(found_ptr==NULL);

    AvlForEach(avl,AddOne,NULL);

    found=*(person_t*)AvlFind(avl,&sheli);

    assert(found.age==21);

    AvlRemove(avl,&sigal);

    assert(5==AvlSize(avl));

    AvlDestroy(avl);

}
