/*********************************
 * Reviewer: Viktor  
 * Author: Sigal Tal		
 * File: sll.c
 * ******************************/
#include <stdlib.h>/*malloc - free*/
#include <assert.h>
#include "sll.h"

struct node
{
	void *data;
	struct node *next;
};

struct sll
{
	node_t *head;
	node_t *tail;
};

static int CountNode (sll_iterator curr, void *param);

sll_t *SLLCreate()
{
	sll_t *new_sll=(sll_t *)malloc(sizeof(sll_t));
	if(!new_sll)
	{
		return NULL;
	}
	new_sll->tail=(node_t *)malloc(sizeof(node_t));
	if(!new_sll->tail)
	{
		free(new_sll);
		return NULL;
	}
	new_sll->tail->data=new_sll;
	new_sll->tail->next=NULL;
	new_sll->head=new_sll->tail;

	return new_sll;
}

sll_iterator SLLInsert(sll_iterator curr, void *new_data)
{
	node_t *new_node=(node_t *)malloc(sizeof(node_t));
	assert(curr);
	assert(new_data);
	if(!new_node)
	{
		while(curr->next)
		{
			curr=curr->next;
		}

		return curr;
	}

	new_node->data=curr->data;
	new_node->next=curr->next;

	curr->data=new_data;
	curr->next=new_node;

	if(NULL==new_node->next)
	{
		((sll_t *)new_node->data)->tail=new_node;
	}

	return curr;
}

sll_iterator SLLBegin(sll_t *slist)
{
	assert(slist);
	return slist->head;
}

sll_iterator SLLEnd(sll_t *slist)
{
	assert(slist);
	return slist->tail;
}

sll_iterator SLLNext(sll_iterator curr)
{
	assert(curr);
	return curr->next;
}

void *SLLGet(sll_iterator curr)
{
	assert(curr);
	return curr->data;
}

void SLLSetData(sll_iterator curr, void *data)
{
	assert(curr);
	assert(data);
	curr->data=data;
}

int SLLIteratorsIsEqual(sll_iterator iter1, sll_iterator iter2)
{
	assert(iter1);
	assert(iter2);

	if(iter2==iter1)
	{
		return 1;
	}

		return 0;
}

sll_iterator SLLRemove(sll_iterator curr)
{
	node_t *tmp_next=curr->next;

	/*cheks that we don't need to remove the tail*/
	if(!curr->next)
	{
		return curr;
	}

	curr->data=tmp_next->data;
	curr->next=tmp_next->next;

	free(tmp_next);

	/*cheks if curr is the new tail*/
	if(!curr->next)
	{
		((sll_t *)curr->data)->tail=curr;
	}

	return curr;
}

size_t SLLCount(const sll_t *slist)
{
	size_t count_node=0;
	/*sll_iterator curr=slist->head;*/
	assert(slist);

	SLLForEach(slist->head, slist->tail, &count_node, CountNode);

	/*while(curr->next)
	{
		++count_node;
		curr=curr->next;
	}*/

	return count_node;
}

static int CountNode(sll_iterator curr, void *param)
{
	(void)curr;
    *(int *)param+=1;
    
    return 0;
}

sll_iterator SLLFind(sll_iterator from, sll_iterator to,void *param,
					 int (*match)(sll_iterator curr,void *param))
{
	assert(from);
	assert(to);
	assert(param);

	while(from!=to)
	{
		if(!match(from,param))
		{
			return from;
		}

		from=from->next;
	}

	return to;
}

int SLLForEach(sll_iterator from, sll_iterator to, void *param, 
				int (*action)(sll_iterator curr,void *param))
{
	assert(from);
	assert(to);
	assert(param);

	while(from!=to)
	{
		if(action(from,param))
		{
			return 1;
		}

		from=from->next;
	}

	return 0;
}

void SLLDestroy(sll_t *slist)
{
	node_t *prev=slist->head;

	assert(slist);

	while(slist->head->next)
	{
		slist->head=slist->head->next;
		free(prev);
		prev=slist->head;
	}
	prev=NULL;

	free(slist->tail);
	slist->tail=NULL;

	free(slist);
	slist=NULL;
}

sll_t *SLLAppend(sll_t *slist1, sll_t *slist2)
{
	assert(slist1);
	assert(slist2);

	if(SLLBegin(slist2)==SLLEnd(slist2))
	{
		SLLDestroy(slist2);
		return slist1;
	}

	slist2->tail->data=slist1;

	slist1->tail->data=slist2->head->data;
	slist1->tail->next=slist2->head->next;

	slist1->tail = slist2->tail;

	free(slist2->head);

	free(slist2);

	return slist1;
}