/*********************************
 * Reviewer:           
 * Author: Sigal Tal       
 * File: test_uid.c          
 * ******************************/
#include <stdio.h>/*printf*/
#include "uid.h"


int main(void)
{

    ilrd_uid_t uid1 = UIDGetNull();
    ilrd_uid_t uid2 = UIDGetNull();
    ilrd_uid_t uid11 = UIDGetNull();
    uid1 = UIDGet();
    uid2 = UIDGet();
    uid11 = uid1;

    printf("Testing UIDIsSame: %d\n", UIDIsSame(uid1, uid2));
    printf("Testing UIDIsSame: %d\n", UIDIsSame(uid1, uid11));

    printf("\nuid1.count = %lu\n", uid1.count);
    printf("uid1.time_stamp = %s", ctime(&uid1.time));
    printf("uid1.pid = %d\n", uid1.pid);
    
    printf("\nuid2.count = %lu\n", uid2.count);
    printf("uid2.time_stamp = %s", ctime(&uid2.time));
    printf("uid2.pid = %d\n", uid2.pid);

    return 0;
}
