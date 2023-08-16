/*********************************
 * Reviewer:           
 * Author: Sigal Tal       
 * File: task.h          
 * ******************************/

#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h>/*size_t*/

typedef int (*task_action_t)(void *arg);
typedef struct task task_t;

task_t *TaskCreate(size_t interval, void *arg, task_action_t action_func);
/*
param: time_t exec_time(absolut time since epoch in seconds), void *arg(arg for parameters),
*/

void TaskDestroy(task_t *task);


size_t TaskGetInterval(task_t *task);

size_t TaskGetExaTime(task_t *task);

void TaskSetTimeInterval(task_t *task, size_t interval);

void TaskSetTimeExe(task_t *task);


int TaskExec(task_t *task);/*0 for sucsess*/


#endif /* __TASK_H__ */