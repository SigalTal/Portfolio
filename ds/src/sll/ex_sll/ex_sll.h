/*********************************
 * Reviewer:Yohai    				
 * Author: Sigal Tal			
 * File: ex_sll.h				
 * ******************************/

#ifndef __EX_SLL_H__
#define __EX_SLL_H__

typedef struct node
{
    void *data;
    struct node *next;
}node_t;

/*Reverses the order of a given slist*/
node_t *Flip(node_t *head);

/*Tells whether a given slist has loop*/
int HasLoop(const node_t *head);

/*Returns a pointer to a first node mutual to bothe slists, if any*/
node_t *FindIntersection(node_t *head_1, node_t *head_2);



#endif /* __EX_SLL_H__ */