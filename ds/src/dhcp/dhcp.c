/*********************************
 * Reviewer: Sarah 
 * Author: Sigal Tal
 * File Name: dhcp.c
 * ******************************/

#include <stddef.h>	/* size_t */
#include <stdlib.h>	/* malloc free */
#include <assert.h>	/* assert */
#include <arpa/inet.h> /*inet_addr*/
#include <math.h>
#include "dhcp.h"

typedef struct trie_node
{
    struct trie_node *child[2];
    int is_taken;

}trie_node_t;

struct dhcp
{
    ip_address_t net_address;
    int free_bits;
    trie_node_t *root;
};

static trie_node_t *CreateNode();
static int InitTrie(dhcp_t *dhcp);
static void DHCPDestroyRec(trie_node_t *root);
static ip_address_t DHCPAllocateIpRec(trie_node_t *node, int level, ip_address_t ip_addr);
static int IsTaken(trie_node_t *node);
static size_t DhcpCountTakenRec(trie_node_t *node, int level);
static trie_node_t *FindIPRec(trie_node_t *node, int level ,ip_address_t ip);
static int NumOfChildren(trie_node_t *node);
int DHCPFreeIpRec(trie_node_t *node, int level, ip_address_t ip);
static void FreeNode(trie_node_t *node);

dhcp_t *DHCPCreate(const char *net_address, int net_mask)
{
    dhcp_t *dhcp=NULL;
    trie_node_t *root=NULL;
    ip_address_t  address=0;

    assert(net_address);

    address = inet_network(net_address);
    if((int)address==-1)
    {
        return NULL;
    }

    dhcp = malloc(sizeof(dhcp_t));
    if(!dhcp)
    {
        return NULL;
    }
   
    root=CreateNode();
    if(!root)
    {
        free(dhcp);
        return NULL;
    }

    dhcp->net_address=address;
    dhcp->free_bits=32-net_mask;
    dhcp->root=root;

    if(1==InitTrie(dhcp))
    {
        DHCPDestroy(dhcp);
        return NULL;
    }

    return dhcp;    
}

static trie_node_t *CreateNode()
{
    trie_node_t *new_node=NULL;
    new_node=malloc(sizeof(trie_node_t));
    if(!new_node)
    {
        return NULL;
    }
    new_node->child[0]=NULL;
    new_node->child[1]=NULL;
    new_node->is_taken=0;

    return new_node;
} 

static int InitTrie(dhcp_t *dhcp)
{
     trie_node_t *curr_node=NULL;
    int i=0;

    curr_node=dhcp->root;

    for(i=0; i<dhcp->free_bits; ++i)
    {
        curr_node->child[0]=CreateNode();
        if(!curr_node->child[0])
        {
            return 1;
        }
        curr_node=curr_node->child[0];
    }

    curr_node->is_taken=1;

    curr_node=dhcp->root;

    for(i=0; i<dhcp->free_bits-1; ++i)
    {
        curr_node->child[1]=CreateNode();
        if(!curr_node->child[1])
        {
            return 1;
        }
        curr_node=curr_node->child[1];
    }
    
    curr_node->child[0]=CreateNode();
    if(!curr_node->child[0])
    {
        return 1;
    }
    curr_node->child[0]->is_taken=1;
    curr_node->child[1]=CreateNode();
    if(!curr_node->child[0])
    {
        return 1;
    }
    curr_node->child[0]->is_taken=1;
    curr_node->is_taken=1;

    return 0;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(dhcp);

    DHCPDestroyRec(dhcp->root);

    free(dhcp);
    dhcp=NULL;
}

static void DHCPDestroyRec(trie_node_t *root)
{
    if(!root)
    {
        return;
    }

    DHCPDestroyRec(root->child[0]);
    DHCPDestroyRec(root->child[1]);

    free(root);
    root=NULL;
}

ip_address_t DHCPAllocateIp(dhcp_t *dhcp)
{
    ip_address_t ip_addr=0;
    assert(dhcp);

    ip_addr=DHCPAllocateIpRec(dhcp->root, dhcp->free_bits, ip_addr);

    ip_addr = dhcp->net_address | ip_addr;

    return ip_addr; 
}

static ip_address_t DHCPAllocateIpRec(trie_node_t *node, int level, ip_address_t ip_addr)
{
    int index=0;
    trie_node_t *child_node=NULL;

    index = (node->child[0] && node->child[0]->is_taken);

    if(!level)
    {
        node->is_taken=1;
        return ip_addr;
    }

    if(node->child[index] && !node->child[index]->is_taken)
    {
        child_node= node->child[index];
        ip_addr=DHCPAllocateIpRec(child_node, level-1 , ip_addr<<1|index);
        node->is_taken= IsTaken(node);
        return ip_addr;
    }

    if(!node->child[index])
    { 
        child_node=CreateNode();
        node->child[index]=child_node;
        ip_addr=DHCPAllocateIpRec(child_node, level-1 , ip_addr<<1|index);
        node->is_taken= IsTaken(node);
        return ip_addr;
    }

    return -1;
}

static int IsTaken(trie_node_t *node)
{
    return (node->child[0] && node->child[0]->is_taken) &&
            (node->child[1] && node->child[1]->is_taken);
}

size_t DHCPCountFree(dhcp_t *dhcp)
{
    assert(dhcp);

    return pow(2,dhcp->free_bits)-DhcpCountTakenRec(dhcp->root, dhcp->free_bits);
}

static size_t DhcpCountTakenRec(trie_node_t *node, int level)
{
    
      if(!node)
    {
        return 0;
    }

    if(!level)
    {
      return 1;  
    }

    return DhcpCountTakenRec(node->child[0],level-1)+DhcpCountTakenRec(node->child[1],level-1);    
}

int DHCPRenewIP(dhcp_t *dhcp, ip_address_t ip)
{
    assert(dhcp);

    if(!FindIPRec(dhcp->root, dhcp->free_bits ,ip))
    {
        return 1;
    }

    return 0;
}

static trie_node_t *FindIPRec(trie_node_t *node, int level ,ip_address_t ip)
{
    int index=0;

    if(!node)
    {
        return NULL;
    }

    if(!level)
    {
        return node;
    }

    index=ip>>(level-1)&1;

    return FindIPRec(node->child[index], level-1 ,ip);
}


int DHCPFreeIp(dhcp_t *dhcp, ip_address_t ip)
{
    assert(dhcp);

    return DHCPFreeIpRec(dhcp->root, dhcp->free_bits, ip);
}

int DHCPFreeIpRec(trie_node_t *node, int level, ip_address_t ip)
{
    int index=0;

    if(!node)
    {
        return 1;
    }

    if(!level)
    {
        return 0;
    }

    index=ip>>(level-1)&1;

    if(DHCPFreeIpRec(node->child[index], level-1 ,ip))
    {
        return 1;
    }

    if(!NumOfChildren(node->child[index]))
    {
        FreeNode(node->child[index]);
        node->child[index]=NULL;
    }

    node->is_taken=0;

    return 0;   
}

static int NumOfChildren(trie_node_t *node)
{   
    return (!!node->child[0])+(!!node->child[1]);
}

static void FreeNode(trie_node_t *node)
{
    node->child[0]=NULL;
    node->child[1]=NULL;
    node->is_taken=0;

    free(node);
    node=NULL;
}








