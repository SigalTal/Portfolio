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
    int i=5;
    printf("Start1\n");

    info = MakeMeImortal();

    printf("Start2\n");
    while(i)
    {
        printf("247 is sleeping\n");
        sleep(30);
        --i;      
    }

    DoNotResuscitate(info);
    printf("Killing 247\n");

    return 0;
}