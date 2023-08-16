/*********************************
 * Reviewer: 
 * Author: 
 * File Name: hash_table_test.c
 * ******************************/


#include <assert.h>
#include "hash_table.h"

typedef struct person
{
    int idNum;
    int age;

}person_t;

static int NumHash(void* data);
static int  IsMatchId(const void *list_data, const void *data);
void QuiqTest();

int main()
{
    QuiqTest();
    return 0;

}

static int NumHash(void* data)
{
  person_t* p = (person_t*)data;
  return p->idNum;
}

static int IsMatchId(const void *list_data, const void *data)
{
    if(list_data==data)
    {
        return 1;
    }

    return 0;
}

void QuiqTest()
{
    hash_t *hash=HashCreate(IsMatchId,NumHash,10);

    person_t sigal={19,28};
    person_t shani={3,20};
    person_t almog={33,29};
    person_t faund={0};

    assert(1==HashIsEmpty(hash));

    HashInsert(hash, &sigal);
    HashInsert(hash, &shani);
    HashInsert(hash, &almog);

    assert(3==HashSize(hash));

    assert(0==HashIsEmpty(hash));

    HashRemove(hash, &sigal);

    assert(2==HashSize(hash));

    faund=*(person_t*)HashFind(hash,&shani);
    assert(faund.idNum==shani.idNum);

    assert(HashFind(hash,&sigal)==NULL);
    
    HashDestroy(hash);


}

