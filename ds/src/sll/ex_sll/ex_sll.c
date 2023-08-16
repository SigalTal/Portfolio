/*********************************
 * Reviewer: Yohai				
 * Author: Sigal Tal			
 * File: ex_sll.c				
 * ******************************/

#include <stddef.h>/*NULL*/
#include <assert.h>
#include "ex_sll.h"

node_t *Flip(node_t *head)
{
    node_t *next_node=head->next;
    node_t *new_next=head->next->next;

    assert(head);

    head->next=NULL;

    while(NULL!=new_next)
    {
        next_node->next=head;
        head=next_node;
        next_node=new_next;
        new_next=new_next->next;
    }

    next_node->next=head;

    return next_node;
}

int HasLoop(const node_t *head)
{
    node_t *slow_ptr=(node_t *)head, *fast_ptr=(node_t *)head;

    assert(head);

    while(slow_ptr && fast_ptr && fast_ptr->next)
    {
        slow_ptr=slow_ptr->next;
        fast_ptr=fast_ptr->next->next;
        if(slow_ptr==fast_ptr)
        {
            return 1;
        }
    }

    return 0;
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
    node_t *ptr1=head_1, *ptr2=head_2;

    assert(head_1);
    assert(head_2);

    while(ptr1!=ptr2)
    {
        ptr1=ptr1->next;
        ptr2=ptr2->next;

        if(ptr1==ptr2)
        {
            return ptr1;
        }

        if(NULL==ptr1)
        {
            ptr1=head_2;
        }

        if(NULL==ptr2)
        {
            ptr2=head_1;
        }
    }

    return NULL;
}