/*********************************
 * Reviewer:           
 * Author: Sigal Tal       
 * File: task_test.c          
 * ******************************/

#include <stdio.h>/*printf*/
#include "task.h"

int Action(void *arg)
{
    printf("%s\n", (char *)arg);

    return 0;
}

int main()
{
    task_t *task = NULL;
    task = TaskCreate(((size_t)10), "Roy", Action);
    if(TaskGetInterval(task) != ((size_t)10))
    {
        printf("Error TaskGetTime\n");
    }

    TaskSetTimeInterval(task, ((size_t)20));
    if(TaskGetInterval(task) != ((size_t)20))
    {
        printf("Error TaskSetTime\n");
    }

    TaskExec(task);
    
    TaskDestroy(task);

    return 0;
}
    
