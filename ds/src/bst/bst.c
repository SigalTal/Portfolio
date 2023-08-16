/*********************************
 * Reviewer: 
 * Author: 		
 * File: bst.c
 * ******************************/

#include <stdlib.h>/*malloc - free*/
#include <assert.h>
#include "bst.h"


typedef struct bst_node
{
    void *data;
    struct bst_node *perent;
    struct bst_node *children[2];

}bst_node_t;

struct bst
{
    bst_compare_func_t compare_func;
    void *user_param;
    struct bst_node *root;   
};

static int IsNextDummy(bst_iterator_t iter);
static bst_iterator_t NextPrevWhithChild(bst_iterator_t iter, int index);
static bst_iterator_t NextPrevWhithOutChild(bst_iterator_t iter, int index);

bst_t *BSTCreate(bst_compare_func_t compare_func, void *user_param)
{
    bst_t *new_bst=NULL;
    bst_node_t *end=NULL;
    assert(compare_func);

    new_bst=(bst_t *)malloc(sizeof(bst_t));
    if(!new_bst)
    {
        return NULL;
    }

    new_bst->compare_func=compare_func;
    new_bst->user_param=user_param;

    end=(bst_node_t *)malloc(sizeof(bst_node_t));
    if(!end)
    {
        return NULL;
    }
    end->data=NULL;
    end->perent=NULL;
    end->children[0]=NULL;
    end->children[1]=NULL;

    new_bst->root=end;

    return new_bst;
}

bst_iterator_t BSTInsert(bst_t *bst, const void *data)
{
    bst_iterator_t new_node;
    bst_iterator_t curr;
    int index=0;

    assert(bst);
    assert(data);

    new_node.bst_node=(bst_node_t *)malloc(sizeof(bst_node_t));
    if(!new_node.bst_node)
    {
        return BSTEnd(bst);
    }

    new_node.bst_node->data=NULL;
    new_node.bst_node->children[0]=NULL;
    new_node.bst_node->children[1]=NULL;
    new_node.bst_node->perent=NULL;
    curr.bst_node=bst->root;

    if(BSTIsEmpty(bst))
    {
        bst->root->data=(void *)data;
        bst->root->children[1]=new_node.bst_node;
        new_node.bst_node->perent=bst->root;

        return new_node;
    }

    new_node.bst_node->data=(void *)data;

    index=(bst->compare_func(curr.bst_node->data,data,NULL)>0);

    while(curr.bst_node->children[index] && !IsNextDummy(curr) && !(bst->compare_func(curr.bst_node->data,data,NULL)==0))
    {
        curr.bst_node=curr.bst_node->children[index];
        index=(bst->compare_func(curr.bst_node->data,data,NULL)>0);
    }

    if(bst->compare_func(curr.bst_node->data,data,NULL)==0)
    {
        free(new_node.bst_node);
        return BSTEnd(bst);
    }

    if(IsNextDummy(curr))
    {
        curr.bst_node->children[1]->perent=new_node.bst_node;
        new_node.bst_node->children[1]=curr.bst_node->children[1];
    }

    curr.bst_node->children[index]=new_node.bst_node;
    new_node.bst_node->perent=curr.bst_node;

    return new_node;

}

static int IsNextDummy(bst_iterator_t iter)
{
    return (NULL==iter.bst_node->children[1]->data);
}

int BSTIsEmpty(bst_t *bst)
{
    assert(bst);

    return (NULL==bst->root->data);
}


void *BSTGetData(bst_iterator_t iter)
{
    assert(iter.bst_node);

    return iter.bst_node->data;
}


bst_iterator_t BSTEnd(bst_t *bst)
{
    bst_iterator_t curr;
    assert(bst);

    curr.bst_node=bst->root;

    while(curr.bst_node->children[1])
    {
      curr.bst_node = curr.bst_node->children[1]; 
    }

    return curr;
} 

bst_iterator_t BSTBegin(bst_t *bst)
{
    bst_iterator_t curr;
    assert(bst);

    curr.bst_node=bst->root;

    while(curr.bst_node->children[0])
    {
      curr.bst_node = curr.bst_node->children[0]; 
    }

    return curr;
} 

bst_iterator_t BSTFind(bst_t *bst, const void *data)
{
    bst_iterator_t curr;
    int index=0;

    assert(bst);
    assert(data);

    curr.bst_node=bst->root;

    if(BSTIsEmpty(bst))
    {
        return BSTEnd(bst);
    }

    index=bst->compare_func(curr.bst_node->data,data,NULL)>0;

    while(curr.bst_node->children[index] && !(bst->compare_func(curr.bst_node->data,data,NULL)==0))
    {        
        curr.bst_node=curr.bst_node->children[index];
        index=bst->compare_func(curr.bst_node->data,data,NULL)>0;
    }

    if((bst->compare_func(curr.bst_node->data,data,NULL)==0))
    {
        return curr;
    }

    return BSTEnd(bst);
}


int BSTIsSameIter(bst_iterator_t f_iter, bst_iterator_t s_iter)
{
    return f_iter.bst_node==s_iter.bst_node;
}

bst_iterator_t BSTNext(bst_iterator_t iter)
{
    if(NULL==iter.bst_node->children[1])
    {
       return NextPrevWhithOutChild(iter, 1);
    }

    return NextPrevWhithChild(iter, 1);
    
}

bst_iterator_t BSTPrev(bst_iterator_t iter)
{
    if(NULL==iter.bst_node->children[0])
    {
       return NextPrevWhithOutChild(iter, 0);
    }

    return NextPrevWhithChild(iter, 0);

}

static bst_iterator_t NextPrevWhithChild(bst_iterator_t iter, int index)
{
    bst_iterator_t curr;

    curr.bst_node=iter.bst_node->children[index];
    index=!index;

    while(curr.bst_node->children[index])
    {
      curr.bst_node = curr.bst_node->children[index]; 
    }

    return curr;
}

static bst_iterator_t NextPrevWhithOutChild(bst_iterator_t iter, int index)
{
    bst_iterator_t curr;

    curr.bst_node=iter.bst_node->perent;
    index=!index;

    while(curr.bst_node->children[index]!=iter.bst_node && NULL!=curr.bst_node->perent)
    {
      iter.bst_node=iter.bst_node->perent;
      curr.bst_node=curr.bst_node->perent;
    }

    return curr;
}






