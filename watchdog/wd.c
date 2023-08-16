/*********************************
 * Reviewer:
 * Author: Sigal
 * File Name: wd.c
 * ******************************/

#include <stdio.h>/*printf*/
#include <unistd.h>/*sleep*/
#include "wdlib.h"

int main(int argc, char **argv)
{
    void *info=NULL;

    info = MakeMeImortal();
    
    printf("the dog is sleeping\n");
    sleep(5);

    DoNotResuscitate(info);    
    

    printf("Watchdog shutting down\n");
    return 0;
}