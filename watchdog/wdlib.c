/*********************************
 * Reviewer:
 * Author: Sigal
 * File Name: wdlib.c
 * ******************************/

#define _POSIX_C_SOURCE 200112L

#include <string.h> /*strcmp*/
#include <stdlib.h>/*getenv, setenv, malloc, free*/
#include <stdio.h>/*sprintf*/
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>/*O_CREAT*/
#include <errno.h>
#include "wdlib.h"
#include "schduler.h"

#define TIMED_WAIT 3

int ImAlive(void *a);
int CheckLife(void *data);
void *StartScheduler(void *data);
void LifeSigHandler(int sig);
void ShutDownSigHandler(int sig);
int Resurrection();
void CleanUp(void *info);

int g_life=0;
int g_shut_down=0;
pid_t g_pid;
sem_t *sem_ready_for_signals;
char *sem_name= "/ready_for_signals";

typedef struct info
{
    scheduler_t *schd;
    pthread_t thread;
    
}info_t;

void *MakeMeImortal(int argc, char **argv)
{
    struct sigaction life_signal={0};
    struct sigaction shutdown_signal={0};
    pthread_t HeartBit;
    char *env_var=NULL;
    char env_wd_pid[20]={'\0'};
    scheduler_t *sch= NULL;
    info_t *info=malloc(sizeof(info));

    life_signal.sa_handler = LifeSigHandler;
    shutdown_signal.sa_handler = ShutDownSigHandler;

    sigaction(SIGUSR1, &life_signal, NULL);
    sigaction(SIGUSR2, &shutdown_signal, NULL);

    sem_ready_for_signals = sem_open(sem_name,O_CREAT, 0666,0);

    sch= SchedulerCreate();
    if(!sch)
    {
        return NULL;
    }
    info->schd=sch;

    SchedulerAddTask(sch, ImAlive, NULL ,1);
    SchedulerAddTask(sch, CheckLife, sch ,3);

    env_var=getenv("WD_PID");

    if(NULL == env_var)
    {
        g_pid = fork();
        if(0 > g_pid)
        {
            return NULL;
        }

        else if(0 == g_pid)
        {
            sprintf(env_wd_pid,"%d",getpid());
            setenv("WD_PID",env_wd_pid,1);
            execlp("wd.Debug.out", "wd.Debug.out");
        }    
    }

    else 
    {
        g_pid = getppid();
    }

    pthread_create(&HeartBit, NULL ,StartScheduler, sch);
    info->thread=HeartBit;

    return (void *)info;   
}

int ImAlive(void *a)
{
    (void)(a);

    printf("Im Alive\n");

    __atomic_add_fetch(&g_life, 1, __ATOMIC_SEQ_CST);

    printf("ImAlive %d sends to pid: %d\n",getpid() ,g_pid);

    kill(g_pid ,SIGUSR1);

    return 0;
}

int CheckLife(void *data)
{
    scheduler_t *schd = (scheduler_t *)data;
    if(__atomic_load_n(&g_life, __ATOMIC_SEQ_CST) > 3 || 1 == g_shut_down)
    {
        printf("To Long No Signal\n");
        g_life=0;
        SchedulerStop(schd);
    }

    printf("Still Living\n");

    return 0;
}

void LifeSigHandler(int sig)
{
    (void)(sig);
    __atomic_store_n(&g_life, 0, __ATOMIC_SEQ_CST);
}

void ShutDownSigHandler(int sig)
{
    (void)(sig);
    __atomic_store_n(&g_shut_down, 1, __ATOMIC_SEQ_CST);
}

void *StartScheduler(void *data)
{
    scheduler_t *schd = (scheduler_t *)data;
    int sem_val=0;

    printf("start schd\n");

    if(NULL == getenv("WD_PID"))
    {
        printf("Im 247\n");
        sem_wait(sem_ready_for_signals);
        
    }
    else
    {
        printf("sending Post\n");
        sem_getvalue(sem_ready_for_signals, &sem_val);
        printf("sem_val : %d\n",sem_val);
        sem_post(sem_ready_for_signals);
    }

    while(1)
    {
        while(0 != SchedulerRun(schd))
        {
            printf("Try again\n");
        }

        if(1 == g_shut_down)
        {
            sem_post(sem_ready_for_signals);
            break;
        }

        Resurrection();

        printf("new g_pid: %d", g_pid);
        printf("env_var: %s",getenv("WD_PID"));

        sem_wait(sem_ready_for_signals);
    }

    return NULL;
}

int Resurrection()
{
    char env_wd_pid[20]={'\0'};

    if(NULL!=getenv("WD_PID") && atoi(getenv("WD_PID")) == getpid())
    {
        printf("reserr 247\n");
        g_pid = fork();
        if(0 > g_pid)
        {
            return 1;
        }

        else if(0 == g_pid)
        {
            execlp("247.Debug.out", "247.Debug.out");
        }    
    }

    else
    {
        printf("reserr WD\n");
        g_pid = fork();
        printf("after fork g_pid: %d\n",g_pid);
        if(0 > g_pid)
        {
            return 1;
        }
        printf("before else if\n");
        if(0 == g_pid)
        {
            sprintf(env_wd_pid,"%d",getpid());
            setenv("WD_PID",env_wd_pid,1);
            execlp("wd.Debug.out", "wd.Debug.out");
        } 
    }

    return 0;   
}

void DoNotResuscitate(void *info)
{
    int i=0, sem_wait_res=-1;

    struct timespec abs_timeout = {0};

    abs_timeout.tv_sec = TIMED_WAIT + time(NULL);

    if(NULL==getenv("WD_PID") || atoi(getenv("WD_PID")) != getpid())
    {
        g_shut_down=1;

        for (i = 0; i < 3 && sem_wait_res; ++i)
        {
            kill(g_pid, SIGUSR2);
            while (-1 == (sem_wait_res = sem_timedwait(sem_ready_for_signals, &abs_timeout))
                && errno == EINTR);
        }
    }

    pthread_join(((info_t *)info)->thread, NULL);

    CleanUp(info);

}

void CleanUp(void *info)
{
    sem_unlink(sem_name);

    SchedulerDestroy(((info_t *)info)->schd);

    free(info);

}