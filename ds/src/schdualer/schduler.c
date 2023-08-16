/*********************************
 * Reviewer:           
 * Author: Sigal Tal       
 * File: Schdualer.c          
 * ******************************/

#include <stdlib.h>/*malloc  - free*/
#include <assert.h>
#include <unistd.h>/*sleep*/
#include <time.h>/*defftime*/
#include "schduler.h"
#include "priority_queue.h"
#include "task.h"

struct scheduler
{
    pri_queue_t *pq;
    char is_stop;
    task_t *running_task;   
};

static int TimePri(const void *data1, const void *data2, void *user_param)
{
    task_t *task1=NULL;
    task_t *task2=NULL;

    assert(data1);
    assert(data2);

    task1=(task_t *)data1;
    task2=(task_t *)data2;
    (void)(user_param);

    return (TaskGetExaTime(task2)<TaskGetExaTime(task1)?-1:1);
}

scheduler_t *SchedulerCreate(void)
{
    scheduler_t *sch=NULL;
    sch=(scheduler_t *)malloc(sizeof(scheduler_t));
    if(!sch)
    {
        return NULL;
    }

    sch->pq=PQueueCreate(TimePri, NULL);
    sch->is_stop=0;
    sch->running_task=NULL;

    if(!sch->pq)
    {
        free(sch);
        sch=NULL;
        return NULL;
    }

    return sch;
}

void SchedulerDestroy(scheduler_t *scdlr)
{
    assert(scdlr);
    SchedulerClearAll(scdlr);
    PQueueDestroy(scdlr->pq);
    free(scdlr);
    scdlr=NULL;
}

ilrd_uid_t SchedulerAddTask(scheduler_t *scdlr,  
            scheduler_action_t action_func,
            void *arg,
            size_t interval_in_sec)

{
    task_t *task=NULL;
    ilrd_uid_t uid=UIDGetNull();

    assert(scdlr);
    assert(action_func);

    task=TaskCreate(interval_in_sec, arg, action_func);
    if(!task)
    {
        return g_bad_uid;
    }

    uid=PQueueEnQueue(scdlr->pq, task);

    if(UIDIsSame(uid,g_bad_uid))
    {
        TaskDestroy(task);
        task=NULL;
    }
    
    return uid;   
}

int SchedulerRemoveTask(scheduler_t *scdlr, ilrd_uid_t uid)
{
    task_t *task=NULL;

    assert(scdlr);

    task=PQueueErase(scdlr->pq,uid);
    if(task)
    {
        TaskDestroy(task);
    }

    return 0;
}

void SchedulerClearAll(scheduler_t *scdlr)
{
    task_t *task=NULL;
    assert(scdlr);

    while(!SchedulerIsEmpty(scdlr))
    {
        task=PQueuePeek(scdlr->pq);
        TaskDestroy(task);
        PQueueDeQueue(scdlr->pq);
        task=NULL;
    }
}

int SchedulerIsEmpty(scheduler_t *scdlr)
{
    assert(scdlr);
    if(scdlr->running_task)
    {
        return 0;
    }

    return PQueueIsEmpty(scdlr->pq);
}

size_t SchedulerSize(scheduler_t *scdlr)
{
    assert(scdlr);
    if(scdlr->running_task)
    {
        return PQueueSize(scdlr->pq)+1;
    }
    return PQueueSize(scdlr->pq);
}

int SchedulerRun(scheduler_t *scdlr)
{
    
    int flag=0;
    double sleep_time=0;
    ilrd_uid_t old_uid=UIDGetNull();

    assert(scdlr);

    scdlr->is_stop=0;
    while(!(scdlr->is_stop) && !SchedulerIsEmpty(scdlr))
    {
        scdlr->running_task=PQueuePeek(scdlr->pq);
        sleep_time=difftime(TaskGetExaTime(scdlr->running_task),time(NULL));
        while(sleep_time>0)
        {
            sleep_time=(double)sleep(sleep_time);  
        }
        
        old_uid=PQueueDeQueue(scdlr->pq);
        flag=TaskExec(scdlr->running_task);

        if(flag)
        {
            TaskDestroy(scdlr->running_task);
        }
        else
        {
            TaskSetTimeExe(scdlr->running_task);
            if(PQueueReEnQueue(scdlr->pq, scdlr->running_task, old_uid))
            {
                return 1;
            }
        }
    scdlr->running_task=NULL;
    }


    return 0;
}

void SchedulerStop(scheduler_t *scdlr)
{
    assert(scdlr);

    scdlr->is_stop=1;
}
