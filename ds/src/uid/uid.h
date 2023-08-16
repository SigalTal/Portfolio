/*********************************
 * Reviewer:           
 * Author: Sigal Tal       
 * File: uid.h          
 * ******************************/

#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h>
#include <time.h>


struct UID                                                                                                                                    
{                                                
  size_t count;
  time_t time;
  pid_t pid;
};

typedef struct UID ilrd_uid_t;

extern const ilrd_uid_t g_bad_uid;

/* description: gives the user a UID to use
   params: non
   return value: ilrd_uid_t 
   O(1) */
ilrd_uid_t UIDGet(void);

/* description: compare two UID's 
   params: two UID's
   return value: 1 if they are the same 0 if not
   undefined behavior:
   O(1) */
int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

/* description: initialize a ilrd_uid_t with value 0 
   params: non
   return value: ilrd_uid_t with value 0
   undefined behavior:
   O(n) */
ilrd_uid_t UIDGetNull(void);

#endif /*__UID_H__*/