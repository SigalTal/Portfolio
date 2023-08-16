/*********************************
 * Reviewer: Sarah 
 * Author: Sigal Tal
 * File Name: dhcp.h
 * ******************************/

#ifndef __DHCP_H__
#define __DHCP_H__

#include<stddef.h>	/* size_t */

typedef struct dhcp dhcp_t;

typedef unsigned int ip_address_t;

dhcp_t *DHCPCreate(const char *net_address, int net_mask);
/*	Description: Creates the DHCP
	Parameters: Net address and number of used bits.
				for example : 192.168.111.0 , 24
	Return value: DHCP handler
	Undefined behavior: 
	Complexity: O(log(n))
*/

void DHCPDestroy(dhcp_t *dhcp);
/*	Description: Destroy the DHCP
	Parameters: DHCP handler
	Return value: 
	Undefined behavior: 
	Complexity: O(log(n)) 
*/

ip_address_t DHCPAllocateIp(dhcp_t *dhcp);
/*	Description: allocate an ip address
	Parameters: DHCP handler
	Return value: IP address as an integer
	Undefined behavior: 
	Complexity: O(log(n)) 
*/

int DHCPFreeIp(dhcp_t *dhcp, ip_address_t ip);
/*	Description: Free an IP address
	Parameters: DHCP handler, IP to free
	Return value: zero for success, non-zero for failure
	Undefined behavior: 
	Complexity: O(log(n)) 
*/

size_t DHCPCountFree(dhcp_t *dhcp);
/*	Description: Counts the available free IP addresses in DHCP
	Parameters: DHCP handler
	Return value: number of available IP addressess in DHCP
	Undefined behavior: 
	Complexity: O(n) 
*/

int DHCPRenewIP(dhcp_t *dhcp, ip_address_t ip);
/*	Description: Renew the lease on the IP address
	Parameters: DHCP handler, IP address to renew
	Return value: zero for success, non-zero for failure
	Undefined behavior: 
	Complexity: O(log(n)) 
*/

#endif /* __DHCP_H__ */
