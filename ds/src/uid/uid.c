/*********************************
 * Reviewer:           
 * Author: Sigal Tal       
 * File: uid.c          
 * ******************************/

#include <sys/types.h>/*getpid*/
#include <unistd.h>/*getpid*/
#include <time.h>/*time*/
#include "uid.h"

const ilrd_uid_t g_bad_uid={-1,-1,-1};

ilrd_uid_t UIDGet(void)
{
	static size_t count=0;
	ilrd_uid_t new_uid;
	new_uid.count=count;
	new_uid.time = time(NULL);
	new_uid.pid=getpid();
	++count;

	return new_uid; 
}


int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (uid1.count==uid2.count && uid1.time==uid2.time && uid1.pid==uid2.pid);
	
}

ilrd_uid_t UIDGetNull(void)
{
	ilrd_uid_t null_uid;
	null_uid.count=0;
	null_uid.time = 0;
	null_uid.pid=0;

	return null_uid;
}