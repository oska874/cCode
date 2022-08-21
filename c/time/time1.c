#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void time3_test()
{
    int ct = time(NULL);
    struct tm *time_utc=gmtime((time_t *)&ct);
    struct tm *time_local=localtime((time_t *)&ct);
    int ct2 = mktime(time_utc);
    
    printf("current time %s\n",ctime((time_t*)&ct));
    
    printf("year %d %d h %d %d \n",time_utc->tm_year,time_local->tm_year,
        time_utc->tm_hour,time_local->tm_hour);
    printf("mktime %d %d\n",ct2,ct);
    
}

void time1_test()
{
    clock_t clk1=clock();
    printf("clk now %ld\n",clk1);    
}
int time2_test(void)
{
    struct timeval tv0;
    struct timespec tp0;
    struct tms tms0;
    time_t te0;
    int ret;
    int i;
    struct timespec timeres[10];
    struct timespec timeres2[10];
        
    clockid_t clocks[] = {
        CLOCK_REALTIME,
        CLOCK_MONOTONIC,/*单调时间，但是受ntp影响（adjtime）*/
        CLOCK_MONOTONIC_RAW,/*基于硬件时间的原始时间，绝对单调*/
        CLOCK_MONOTONIC_COARSE,/*低精度单调时间*/
        CLOCK_PROCESS_CPUTIME_ID,/*本进程到当前代码系统CPU花费的时间*/
        CLOCK_THREAD_CPUTIME_ID,
        (clockid_t) -1 };

    te0 = time(NULL);

    ret = gettimeofday(&tv0,NULL);
    if (ret){
        perror("gettimeofday fail ");
    }

    ret = clock_gettime(CLOCK_REALTIME,&tp0);
    if ((clock_t)ret == -1)
        perror("clock gettime fail ");

    printf("clk per sec %ld\n",sysconf(_SC_CLK_TCK));
    ret = times(&tms0);
    if(ret<0)
        perror("times fail ");
    
    printf("current time %d\n",(int)te0);
    printf("tv sec %ld usec %ld\n",tv0.tv_sec,tv0.tv_usec);
    printf("tp sec %ld nsec %ld\n",tp0.tv_sec,tp0.tv_nsec);
    printf("tms sec %ld usec %ld\n",tms0.tms_utime,tms0.tms_stime);

    for (i = 0; clocks[i] != (clockid_t) -1; i++) {
       struct timespec res;
       int ret;
       ret = clock_getres (clocks[i], &res);
       if (ret)
           perror ("clock_getres");
       else
           printf ("%d clock=%d sec=%ld nsec=%ld\n", i, clocks[i], res.tv_sec, res.tv_nsec);
    }
    for (i = 0; clocks[i] != (clockid_t) -1; i++) {
        ret = clock_gettime(clocks[i],&timeres[i]);
        if((clock_t)ret == -1){
            perror("gettime fail");
            printf("%d %d\n",i,ret);
        }
    }
    sleep(5);
    for (i = 0; clocks[i] != (clockid_t) -1; i++) {
        ret = clock_gettime(clocks[i],&timeres2[i]);
        if((clock_t)ret == -1){
            perror("gettime fail");
            printf("%d %d\n",i,ret);
        }
    }

    for (i = 0; clocks[i] != (clockid_t) -1; i++) {
        printf("%d | %d | %ld %ld \n",i,clocks[i],timeres2[i].tv_sec-timeres[i].tv_sec,timeres2[i].tv_nsec-timeres[i].tv_nsec);
    }

    return 0;
}

int main()
{
    time1_test();
    time2_test();
    time3_test();
    time1_test();
    return 0;
}
