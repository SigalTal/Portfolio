/*********************************
 * Reviewer:           
 * Author: Sigal Tal       
 * File: priority_queue_test.c         
 * ******************************/
#include <string.h>/*strcmp*/
#include <stdlib.h>/*malloc - free*/
#include <assert.h>
#include <stdio.h>/*printf*/
#include "priority_queue.h"

typedef struct student
{
    char *name;
    int id;
    
}student_t;

static int PQIntCompare(const void *data1,const void *data2, void *user_param);
static int CompareID(const void *data1, const void *data2, void *user_param);
void TestCreate();
pri_queue_t * TestCreateStu();
void TestEnQueue(pri_queue_t *pq);
void TestDeQueue(pri_queue_t *pq);
void TestPeek();


int main()
{
    pri_queue_t *pq=TestCreateStu();
    TestCreate();
    TestEnQueue(pq);
    TestDeQueue(pq);
    PQueueDestroy(pq);
    TestPeek();



    
    return 0;
}

static int PQIntCompare(const void *data1,const void *data2, void *user_param)
{
    (void)(user_param);
    return (*(int*)data2 - *(int*)data1);
}

static int CompareID(const void *data1, const void *data2, void *user_param)
{
    student_t s1 = *(student_t*)data1;
    student_t s2 = *(student_t*)data2;
    (void)user_param;
    return (s1.id - s2.id);
}


void TestCreate()
{
    int a=1;

    pri_queue_t *new_q=PQueueCreate(PQIntCompare, "sigal");

    PQueueEnQueue(new_q, &a);

    PQueueDeQueue(new_q);

    PQueueDestroy(new_q);
}

pri_queue_t * TestCreateStu()
{
    pri_queue_t *new_q=PQueueCreate(CompareID, "sigal");

    return new_q;
}

void TestEnQueue(pri_queue_t *pq)
{
    ilrd_uid_t uid=UIDGetNull();
    student_t st1={"Sigal",1};
    student_t st2={"Shani",3};
    student_t st3={"Ariel",4};
    student_t st4={"Carmitall",5};
    student_t st5;
    student_t *st6=NULL;


    assert(1==PQueueIsEmpty(pq));

    PQueueEnQueue(pq, &st1);
    uid=PQueueEnQueue(pq, &st2);
    assert(2==PQueueSize(pq));
    PQueueEnQueue(pq, &st3);
    PQueueEnQueue(pq, &st4);
    assert(0==PQueueIsEmpty(pq));
    assert(4==PQueueSize(pq));

    st5=*(student_t *)PQueueErase(pq, uid);
    st6=PQueueErase(pq, g_bad_uid);
    assert(NULL==st6);
    assert(st2.name==st5.name);
    assert(3==PQueueSize(pq));


}

void TestDeQueue(pri_queue_t *pq)
{
  
    PQueueDeQueue(pq);
  
    PQueueDeQueue(pq);
   
    PQueueDeQueue(pq);
}


void TestPeek()
{
    pri_queue_t *pq=PQueueCreate(CompareID, "sigal");
    student_t student={0};

    student_t st1={"Sigal",166};
    student_t st2={"Shani",38};
    student_t st3={"Ariel",4};
    student_t st4={"Carmitall",5};


    assert(1==PQueueIsEmpty(pq));

    PQueueEnQueue(pq, &st1);
    PQueueEnQueue(pq, &st2);
    PQueueEnQueue(pq, &st3);
    PQueueEnQueue(pq, &st4);
    assert(0==PQueueIsEmpty(pq));
    assert(4==PQueueSize(pq));

    student=*(student_t *)PQueuePeek(pq);
    printf("name: %s\n",student.name);
    printf("id: %d\n",student.id);
    PQueueDeQueue(pq);
    student=*(student_t *)PQueuePeek(pq);
    printf("name: %s\n",student.name);
    printf("id: %d\n",student.id);
    PQueueDeQueue(pq);
    student=*(student_t *)PQueuePeek(pq);
    printf("name: %s\n",student.name);
    printf("id: %d\n",student.id);
    PQueueDeQueue(pq);
    assert(0==PQueueIsEmpty(pq));

    PQueueDestroy(pq);
   
}
