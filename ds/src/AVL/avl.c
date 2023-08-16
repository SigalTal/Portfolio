/*********************************
 * Reviewer: Daniel Natan
 * Author: Sigal Tal    
 * File: AVL.c
 * ******************************/
#include <assert.h>
#include <stddef.h>/*size_t*/
#include <stdlib.h>/*malloc - free*/
#include "avl.h"

enum children_index {LEFT, RIGHT};

typedef struct avl_node
{
    void *data;
    int hight;
    struct avl_node *children[2];

}avl_node_t;

struct avl
{
    avl_compare_func_t compare_func;
    void *user_param;
    struct avl_node *root;   
};

static avl_node_t *AvlFindRecursive(avl_t *avl, avl_node_t *curr ,const void *data);
static void UpdateHight(avl_node_t *curr);
static avl_node_t* BalancedInsert(avl_t *avl ,avl_node_t *root, avl_node_t *new_node);
static avl_node_t *Rotation(avl_node_t *unbalanced_node);
static int CheckesBalance(avl_node_t *curr);
static avl_node_t* Rotate(avl_node_t* root, int direction);
static avl_node_t* DoubleRotate(avl_node_t* root, int direction);
static avl_node_t *BalancedRemove(avl_t *avl ,avl_node_t *root, void *data);
static avl_node_t *RemoveNode(avl_node_t *remove_node);
static avl_node_t *RemoveNoChildren(avl_node_t *remove_node);
static avl_node_t *RemoveOneChild(avl_node_t *remove_node);
static avl_node_t *RemoveTwoChildren(avl_node_t *remove_node);
static size_t RecurciveSize(avl_node_t *root);
static int RecurciveForEach(avl_node_t *root, avl_action_func_t action_func, void *param);
static void RecurciveDestroy(avl_t *avl,avl_node_t *root);


/*******************CREATE********************************/
avl_t *AvlCreate(avl_compare_func_t compare_func, void *user_param)
{
    avl_t *new_avl=NULL;

    assert(compare_func);

    new_avl=malloc(sizeof(avl_t));
    if(!new_avl)
    {
        return NULL;
    }
    new_avl->compare_func=compare_func;
    new_avl->user_param=user_param;
    new_avl->root=NULL;

    return new_avl;
}
/**********************************************************/

/*******************DESTROY********************************/
void AvlDestroy(avl_t *avl)
{
    assert(avl);

    RecurciveDestroy(avl, avl->root);

    free(avl);
    avl=NULL;
}
/**********************************************************/
    
static void RecurciveDestroy(avl_t *avl,avl_node_t *root)
{
    if(!root)
    {
        return;
    }

    RecurciveDestroy(avl, root->children[LEFT]);
    RecurciveDestroy(avl, root->children[RIGHT]);

    RemoveNoChildren(root);    
}

/*******************IS_EMPTY********************************/
int AvlIsEmpty(avl_t *avl)
{
    assert(avl);

    return (avl->root==NULL);
}
/**********************************************************/

/*******************INSERT********************************/
int AvlInsert(avl_t *avl, const void *data)
{
    /*avl_node_t *curr=NULL;*/
    avl_node_t *new_node=NULL;
    
    assert(avl);
    assert(data);

    new_node=malloc(sizeof(avl_node_t));
    if(!new_node)
    {
        return 2;
    }
    new_node->data=(void *)data;
    new_node->children[LEFT]=NULL;
    new_node->children[RIGHT]=NULL;
    new_node->hight=0;

    if (AvlFind(avl,data))
    {
        free(new_node);
        return 2;
    }
    
    avl->root = BalancedInsert(avl ,avl->root, new_node);

    return 0;  
}
/**********************************************************/

static avl_node_t* BalancedInsert(avl_t *avl ,avl_node_t *root, avl_node_t *new_node)
{
    int index=LEFT;

    if(!root)
    {
        return new_node;
    }

    index=(avl->compare_func(root->data,new_node->data,avl->user_param)>0);

    root->children[index] = BalancedInsert(avl, root->children[index],new_node);

    UpdateHight(root);

    return Rotation(root);
}

static void UpdateHight(avl_node_t *curr)
{
    int max_child_hight=0;
    int hight_left_chaild=-1;
    int hight_right_chaild=-1;

    if(curr->children[LEFT]!=NULL)
    {
         hight_left_chaild=curr->children[LEFT]->hight;
    }

    if(curr->children[RIGHT]!=NULL)
    {
       hight_right_chaild=curr->children[RIGHT]->hight;
    }

    max_child_hight = hight_left_chaild > hight_right_chaild ? hight_left_chaild:hight_right_chaild;

    curr->hight = max_child_hight+1;
}


static avl_node_t *Rotation(avl_node_t *unbalanced_node)
{
    if(CheckesBalance(unbalanced_node)<-1 && CheckesBalance(unbalanced_node->children[RIGHT])<0)
    {  
        /*Rotate Right*/ 
        return Rotate(unbalanced_node, 0);
    }

    if(CheckesBalance(unbalanced_node)<-1 && CheckesBalance(unbalanced_node->children[RIGHT])>0)
    {
        /*Rotate Right-Left*/
       return DoubleRotate(unbalanced_node, 0);
    }

    if(CheckesBalance(unbalanced_node)>1 && CheckesBalance(unbalanced_node->children[LEFT])>0)
    {
        /*Rotate Left*/
        return Rotate(unbalanced_node, 1);
    }

    if(CheckesBalance(unbalanced_node)>1 && CheckesBalance(unbalanced_node->children[LEFT])<0)
    {
        /*Rotate Left-Right*/
        return DoubleRotate(unbalanced_node, 1);
    }

    return unbalanced_node;
}

static avl_node_t* Rotate(avl_node_t* root, int direction)
{ 
    avl_node_t* node1 = root->children[!direction]; 
    avl_node_t* node2 = node1->children[direction]; 

    /* Perform rotation */
    node1->children[direction] = root; 
    root->children[!direction] = node2; 

    /* Update heights */
    UpdateHight(root);
    UpdateHight(node1);

    return node1; 
} 

static avl_node_t* DoubleRotate(avl_node_t* root, int direction)
{
    root->children[!direction] = Rotate(root->children[!direction],!direction);
    return Rotate(root,direction);
}

static int CheckesBalance(avl_node_t *curr)
{
    int hight_left_chaild=-1;
    int hight_right_chaild=-1;

    if(curr->children[LEFT]!=NULL)
    {
         hight_left_chaild=curr->children[LEFT]->hight;
    }

    if(curr->children[RIGHT]!=NULL)
    {
       hight_right_chaild=curr->children[RIGHT]->hight;
    }

    return hight_left_chaild-hight_right_chaild;
}

/*******************FIND********************************/

void *AvlFind(avl_t *avl, const void *data)
{
    avl_node_t *curr=NULL;
    avl_node_t *found_node=NULL;

    assert(avl);
    assert(data);

    if(AvlIsEmpty(avl))
    {
        return NULL;
    }

    curr=avl->root;

    found_node=AvlFindRecursive(avl, curr ,data);

    if(0==avl->compare_func(found_node->data,data,avl->user_param))
    {
        return found_node->data;
    }

    return NULL;
}
/**********************************************************/

static avl_node_t *AvlFindRecursive(avl_t *avl, avl_node_t *curr ,const void *data)
{
    char index=LEFT;

    index=(avl->compare_func(curr->data,data,avl->user_param)>0);

    if(curr->children[(int)index]==NULL && 0!=(avl->compare_func(curr->data,data,avl->user_param)))
    {
        return curr;
    }

    if(0==(avl->compare_func(curr->data,data,avl->user_param)))
    {
        return curr;
    }

    curr=curr->children[(int)index];
    return AvlFindRecursive(avl,curr,data);
}

/*******************HEIGHT********************************/
size_t AvlHeight(const avl_t *tree)
{
    assert(tree);

    return tree->root->hight;
}
/**********************************************************/

/*******************REMOVE********************************/

void AvlRemove(avl_t *avl, void *data)
{
    assert(avl);
    assert(data);

    avl->root=BalancedRemove(avl ,avl->root, data);
}
/**********************************************************/

static avl_node_t *BalancedRemove(avl_t *avl ,avl_node_t *root, void *data)
{
    int index=LEFT;

    if(NULL==root) 
    {
        return NULL;
    }

    if(0==(avl->compare_func(data,root->data,avl->user_param)))
    {
        return RemoveNode(root);
    }

    index=(avl->compare_func(root->data,data,avl->user_param)>0);

    root->children[index] = BalancedRemove(avl, root->children[index],data);

    UpdateHight(root);

    return Rotation(root);
}

static avl_node_t *RemoveNode(avl_node_t *remove_node)
{
    int num_of_children = (!!remove_node->children[LEFT])+(!!remove_node->children[RIGHT]);

    switch (num_of_children)
    {
    case 0:
        return RemoveNoChildren(remove_node);

    case 1:
        return RemoveOneChild(remove_node);

    case 2:
        return RemoveTwoChildren(remove_node);
    }

    return remove_node;
}

static avl_node_t *RemoveNoChildren(avl_node_t *remove_node)
{
    free(remove_node);
    remove_node=NULL;
    return NULL;
}

static avl_node_t *RemoveOneChild(avl_node_t *remove_node)
{
    int index=LEFT;
    avl_node_t *tmp_removed_node=NULL;

    assert(remove_node);

    if(remove_node->children[RIGHT])
    {
        index=RIGHT;
    }

    tmp_removed_node=remove_node->children[index];

    free(remove_node);
    remove_node=NULL;

    return tmp_removed_node;
}

static avl_node_t *RemoveTwoChildren(avl_node_t *remove_node)
{
    avl_node_t *leaf_remove_node=remove_node->children[1];
    avl_node_t *perent_leaf=remove_node;
    int index=RIGHT;
    while (leaf_remove_node->children[LEFT])
    {
        index=LEFT;
        perent_leaf=leaf_remove_node;
        leaf_remove_node=leaf_remove_node->children[LEFT];

    }
    remove_node->data=leaf_remove_node->data;

    perent_leaf->children[index]=RemoveNode(leaf_remove_node);

    return remove_node;
}

/*******************SIZE********************************/

size_t AvlSize(avl_t *avl)
{
    assert(avl);

    if(AvlIsEmpty(avl))
    {
        return 0;
    }

    return RecurciveSize(avl->root);
}
/**********************************************************/

static size_t RecurciveSize(avl_node_t *root)
{
    if(root==NULL)
    {
        return 0;
    }

    return 1+RecurciveSize(root->children[LEFT])+RecurciveSize(root->children[RIGHT]);
}

/*******************FOR_EACH********************************/

int AvlForEach(avl_t *avl, avl_action_func_t action_func, void *param)
{
    assert(avl);
    assert(action_func);

    return RecurciveForEach(avl->root,action_func,param);
}
/**********************************************************/

int RecurciveForEach(avl_node_t *root, avl_action_func_t action_func, void *param)
{
    int action_res=0;

    if(!root)
    {
        return 0;
    }

    action_res=RecurciveForEach(root->children[LEFT],action_func,param);
    if(action_res)
    {
        return action_res;
    }

    action_res=action_func(root->data,param);
    if(action_res)
    {
        return action_res;
    }

    action_res=RecurciveForEach(root->children[RIGHT],action_func,param);

    return action_res;
}





