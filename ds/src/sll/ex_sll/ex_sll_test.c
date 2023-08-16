/*********************************
 * Reviewer: Yohai  				
 * Author: Sigal Tal			
 * File: ex_sll_test.c				
 * ******************************/

#include <stdio.h>/*printf*/
#include "ex_sll.h"

void TestFlip();
void TestHasLoop();
void TestFindIntersection();

int main()
{

    TestFlip();
    TestHasLoop();
    TestFindIntersection();

    return 0;
}

void TestFlip()
{
    node_t node1,node2,node3,node4,node5,node6 ;
    node_t *new;
    
    int num1 = 1,num2 = 2,num3 = 3,num4 = 4,num5 = 5,num6 = 6;
   
    node1.data = &num1;
    node1.next = &node2;
    
    node2.data = &num2;
    node2.next = &node3;
    
    node3.data = &num3;
    node3.next = &node4;
    
    node4.data = &num4;
    node4.next = &node5;
    
    node5.data = &num5;
    node5.next = &node6;
    
    node6.data = &num6;
    node6.next = NULL;
    
    printf("before reverse list elements are:\n");
    
    printf("%d\n", *(int*)node1.data);
    printf("%d\n", *(int*)node2.data);
    printf("%d\n", *(int*)node3.data);
    printf("%d\n", *(int*)node4.data);
    printf("%d\n", *(int*)node5.data);
    printf("%d\n", *(int*)node6.data);
    
    new = Flip((node_t *)&node1);
    
    printf("after reverse list elements are:\n");
    
    while(new != NULL)
    {
        printf("%d\n",*(int*)new->data);
        new = new->next;
    }
}

void TestHasLoop()
{
    node_t node1,node2,node3,node4,node5,node6 ;
    
    int num1 = 1,num2 = 2,num3 = 3,num4 = 4,num5 = 5,num6 = 6;
    
    node1.data = &num1;
    node1.next = &node2;
    
    node2.data = &num2;
    node2.next = &node3;
    
    node3.data = &num3;
    node3.next = &node4;
    
    node4.data = &num4;
    node4.next = &node5;
    
    node5.data = &num5;
    node5.next = &node6;
    
    node6.data = &num6;
    node6.next = &node4;
    
    printf("has_loop: %d\n",HasLoop((node_t *)&node1));

}

void TestFindIntersection()
{
    node_t node1,node2,node3,node4,node5,node6 ;
    node_t *new;
    
    int num1 = 1,num2 = 2,num3 = 3,num4 = 4,num5 = 5,num6 = 6;
   
    node1.data = &num1;
    node1.next = &node2;
    
    node2.data = &num2;
    node2.next = &node3;
    
    node3.data = &num3;
    node3.next = &node5;
    
    node4.data = &num4;
    node4.next = &node5;
    
    node5.data = &num5;
    node5.next = &node6;
    
    node6.data = &num6;
    node6.next = NULL;

    new=FindIntersection((node_t *)&node1,(node_t *)&node4);
    
    printf("Intersection: %d\n",*(int *)new->data);

}