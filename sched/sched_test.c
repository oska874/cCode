#include<stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<time.h>
#define __USE_GNU
#include<sched.h>
#include<ctype.h>
#include<string.h>
#include <signal.h> 


/*
 * #define SCHED_OTHER 0
 * #define SCHED_FIFO 1
 * #define SCHED_RR 2
 * #ifdef __USE_GNU
 * # define SCHED_BATCH 3
 * #endif
 * 
 */
 
uint64_t sum=0;
uint64_t max=0;
uint64_t min=0;
uint64_t avg=0;
uint64_t num=0;

void voidvoid()
{
}

void calcute()
{
    printf("max %llu min %llu avg %llu num %llu sum %llu\n",max,min,avg,num,sum);
    fprintf(stderr," PID = %d\t scheduler %d priority: %d\tEND TIME is %ld\n",getpid(),sched_getscheduler(getpid()),getpriority(0,0),time(NULL));
    exit(0);
}
int test_func()
{
    printf("sched test\n");
    struct sigaction act; 
    sigemptyset(&act.sa_mask);
    act.sa_flags=SA_SIGINFO; 

    int ret;
    struct timeval cur_time;
    uint64_t time_u=0,told=0,div=0;;
    uint64_t over = 2000;

    ret = setpriority(PRIO_PROCESS,0,-10);
    if(ret <0){
        perror("set error:");
        exit(-2);
    }

    while(1){
        ret = gettimeofday(&cur_time,NULL);       

        if(ret != 0){
            perror("get time error:");
            goto error1;
        }
        time_u = cur_time.tv_sec*1000000+cur_time.tv_usec;

        if (told == 0)
            goto next;

//    printf("max %llu min %llu avg %llu num %llu sum %llu div %llu\n",max,min,avg,num,sum,div);


        div=time_u - told;

#if 1
        if( div > over ){
            printf("div large %llu %llu now %llu %llu\n",div,over,time_u,told);
        }
        else{
        }
#endif

#if 0
    act.sa_sigaction=voidvoid; 
    if(sigaction(SIGINT,&act,NULL) < 0) 
    { 
        printf("install signal error\n"); 
    } 
#endif
    //printf("new %llu old %llu div %llu\n",time_u,told,div);
        num+=1;
        sum+=div;
        avg=sum/num;
        if (max < div)
            max = div;
        if (min == 0 || min > div )
            min = div;
#if 0
    act.sa_sigaction=calcute; 
    if(sigaction(SIGINT,&act,NULL) < 0) 
    { 
        printf("install signal error\n"); 
    } 
#endif
next:
        told = time_u;
        usleep(1000);
    }

error1:
    return 0;
}



int main(int argc,char* argv[])
{
    struct sigaction act; 
    sigemptyset(&act.sa_mask);
    act.sa_flags=SA_SIGINFO; 
    act.sa_sigaction=calcute; 
    if(sigaction(SIGINT,&act,NULL) < 0) 
    { 
        printf("install signal error\n"); 
    } 


    int i;
    long interval;
    struct timeval tend,tstart;
    struct tm lcltime = {0};
    struct sched_param param;
    int ret = 0;
    if(argc != 3)
    {
        fprintf(stderr,"usage:./test sched_method  sched_priority\n");
        return -1;
    }
    cpu_set_t mask ;
    CPU_ZERO(&mask);
    CPU_SET(1,&mask);
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
    {  
        printf("warning: could not set CPU affinity, continuing...\n");
    }

    int sched_method = atoi(argv[1]);
    int sched_priority = atoi(argv[2]);

    printf("pri %d method %d\n",sched_priority,sched_method);


    if (sched_method == SCHED_OTHER){
        param.sched_priority = 0;
    }
    else{
        param.sched_priority = sched_priority;
    }
    ret = sched_setscheduler(getpid(),sched_method,&param);
    if(ret)
    {
        perror("set scheduler error:");
        return -4;
    }
    if (sched_method == SCHED_OTHER){
        ret = setpriority(0,0,sched_priority);
        if(ret <0){
            perror("set priority error:");
            exit(-5);
        }
    }

    fprintf(stderr,"the  scheduler of PID(%ld) is %d, priority (%d),BEGIN time is :%ld\n",
            getpid(),sched_getscheduler(0),getpriority(0,0),time(NULL));
    test_func();
    fprintf(stderr," PID = %d\t priority: %d\tEND TIME is %ld\n",getpid(),getpriority(0,0),time(NULL));
    return 0;
}
