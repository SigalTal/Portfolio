/*********************************
 * Reviewer:           
 * Author: Sigal Tal       
 * File: task.c          
 * ******************************/

#include <stdlib.h>/*malloc - free*/
#include <assert.h>
#include <time.h>/*time_t*/
#include "task.h"

struct task                    
{
    size_t interval;
    time_t exe_time;
    void *arg;
    task_action_t action_func;
};

task_t *TaskCreate(size_t interval, void *arg, task_action_t action_func)
{
    task_t *new_task=NULL;
    assert(action_func);
    new_task=(task_t *)malloc(sizeof(task_t));
    if(!new_task)
    {
        return NULL;
    }
    new_task->interval=interval;
    new_task->exe_time=time(NULL)+new_task->interval;
    new_task->arg=arg;
    new_task->action_func=action_func;

    return new_task;
}

void TaskDestroy(task_t *task)
{
    assert(task);
    task->interval=0;
    task->exe_time=0;
    task->arg=NULL;
    task->action_func=NULL;

    free(task);
    task=NULL;
}

size_t TaskGetInterval(task_t *task)
{
    assert(task);
    return task->interval;
}

size_t TaskGetExaTime(task_t *task)
{
    assert(task);
    return task->exe_time;
}

void TaskSetTimeInterval(task_t *task, size_t interval)
{
    assert(task);
    task->interval=interval;
}

void TaskSetTimeExe(task_t *task)
{
    assert(task);
    task->exe_time=time(NULL)+(task->interval);
}

int TaskExec(task_t *task)
{
    assert(task);
    return task->action_func(task->arg);
}
