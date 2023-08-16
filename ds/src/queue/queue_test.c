#include <stdio.h>/*printf*/
#include <string.h>
#include <assert.h>
#include "queue.h"

void TestNewQ();
void TestQSize();
void TestQueueAppend(void);

int main()
{
	TestNewQ();
	TestQSize();
	TestQueueAppend();
	
	return 0;
}

void TestNewQ()
{
	queue_t *q=QueueCreate();

	QueueDestroy(q);
}

void TestQSize()
{
	queue_t *q=QueueCreate();

	int a=1;
	int b=2;
	int c=3;

	QueueEnQueue(q, &a);
	QueueEnQueue(q, &b);
	QueueEnQueue(q, &c);

	assert(3==QueueSize(q));
	/*printf("is ampty:%d\n",QueueIsEmpty(q));*/
	assert(0==QueueIsEmpty(q));

	QueueDeQueue(q);

	assert(2==*(int *)QueuePeek(q));

	QueueDeQueue(q);
	assert(1==QueueSize(q));

	QueueDeQueue(q);
	assert(1==QueueIsEmpty(q));

	QueueDestroy(q);

}

/*void TestQAppend()
{
	queue_t *q1=QueueCreate();
	queue_t *q2=QueueCreate();

	int a=1;
	int b=2;
	int c=3;

	QueueEnQueue(q1, &a);
	QueueEnQueue(q1, &b);
	QueueEnQueue(q1, &c);


	QueueEnQueue(q2, &a);
	QueueEnQueue(q2, &b);
	QueueEnQueue(q2, &c);

	QueueAppend(q1,q2);

	assert(6==QueueSize(q1));

	QueueDestroy(q1);

}*/

void TestQueueAppend(void)
{
    queue_t *q1 = QueueCreate(), *q2 = QueueCreate();
    char *str1 = "12345", *str2 = "ABCD";
    size_t size_q1 = 0, size_q2 = 0;
    size_t i = 0;

    for (i = 0; i < strlen(str1); ++i)
    {
        if (QueueEnQueue(q1, str1+i))
        {
            printf("Error on EnQueue\n");
        }
    }

    size_q1 = QueueSize(q1);

    for (i = 0; i < strlen(str2); ++i)
    {
        if (QueueEnQueue(q2, str2+i))
        {
            printf("Error on EnQueue\n");
        }
    }

    size_q2 = QueueSize(q2);

    q1 = QueueAppend (q1, q2);
    if (QueueSize(q1) != (size_q1 + size_q2))
    {
        printf("Error on QueueAppend\n");
    }

/*  UnComment to see the print of the new appended list */
    while (!QueueIsEmpty(q1))
    {
        printf("%c\n", *(char *)QueuePeek(q1));
        QueueDeQueue(q1);
    }

    QueueDestroy(q1);
    q1 = NULL;

}