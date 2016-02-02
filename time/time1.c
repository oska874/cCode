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
        
    te0 = time(NULL);

    ret = gettimeofday(&tv0,NULL);
    if (ret){
        perror("gettimeofday fail ");
    }

    ret = clock_gettime(CLOCK_REALTIME,&tp0);
    if ((clock_t)ret == -1)
        perror("clock gettime fail ");

    printf("clk per sec %d\n",sysconf(_SC_CLK_TCK));
    ret = times(&tms0);
    if(ret<0)
        perror("times fail ");
    
    printf("current time %d\n",(int)te0);
    printf("tv sec %ld usec %ld\n",tv0.tv_sec,tv0.tv_usec);
    printf("tp sec %ld nsec %ld\n",tp0.tv_sec,tp0.tv_nsec);
    printf("tms sec %ld usec %ld\n",tms0.tms_utime,tms0.tms_stime);

    clockid_t clocks[] = {
        CLOCK_REALTIME,
        CLOCK_MONOTONIC,
        CLOCK_PROCESS_CPUTIME_ID,
        CLOCK_THREAD_CPUTIME_ID,
        (clockid_t) -1 };

    int i;

    for (i = 0; clocks[i] != (clockid_t) -1; i++) {
       struct timespec res;

       int ret;

       ret = clock_getres (clocks[i], &res);

       if (ret)

           perror ("clock_getres");

       else

           printf ("clock=%d sec=%ld nsec=%ld\n", clocks[i], res.tv_sec, res.tv_nsec);

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
