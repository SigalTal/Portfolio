/*********************************
 * Reviewer: Sarah 
 * Author: Sigal Tal
 * File Name: dhcp_test.c
 * ******************************/

#include <stdio.h>
#include <assert.h>
#include <arpa/inet.h> /*inet_addr*/
#include "dhcp.h"

void BasicTest();
void AdvencedTest();

int main()
{

	BasicTest();
	AdvencedTest();
	

	return 0;
}

void BasicTest()
{
	char *net_address="129.254.1.0";
	char *test_address="129.254.1.1";
	int net_mask=24;
	dhcp_t *dhcp=NULL;

	ip_address_t ip_adder=0;

	dhcp=DHCPCreate(net_address,net_mask);

	ip_adder=DHCPAllocateIp(dhcp);
	assert(ip_adder==inet_network(test_address));

	assert(252==DHCPCountFree(dhcp));

	assert(0==DHCPRenewIP(dhcp, inet_network(net_address)));

	DHCPFreeIp(dhcp, inet_network(test_address));

	assert(1==DHCPRenewIP(dhcp, inet_network(test_address)));

	DHCPDestroy(dhcp);
}

void AdvencedTest()
{

	char *net_address="129.254.1.0";
	char *test_address="129.254.1.1";
	int net_mask=24;
	dhcp_t *dhcp=NULL;
	int i=0;

	ip_address_t ip_adder=0;

	dhcp=DHCPCreate(net_address,net_mask);

	for(i=0; i<253; ++i)
	{
		ip_adder=DHCPAllocateIp(dhcp);
	}

	assert((int)ip_adder!=-1);

	ip_adder=DHCPAllocateIp(dhcp);
	assert((int)ip_adder==-1);

	assert(0==DHCPCountFree(dhcp));

	DHCPFreeIp(dhcp, inet_network(test_address));

	assert(1==DHCPCountFree(dhcp));

	DHCPDestroy(dhcp);
	
}


