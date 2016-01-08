#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <stdio.h>

int main(void)
{
    struct timeval tv0;
    struct timespec tp0;
    struct tms tms0;
    time_t te0;
    struct tm tm0;
    clock_t ck0;
    int ret;
    te0 = time(NULL);


    ret = gettimeofday(&tv0,NULL);
    if (ret){
        perror("gettimeofday fail ");
    }

    ret = clock_gettime(CLOCK_REALTIME,&tp0);
    if (ret)
        perror("clock gettime fail ");

    ret = times(&tms0);
    if(ret<0)
        perror("times fail ");
    
    printf("current time %d\n",(int)te0);
    printf("tv sec %d usec %d\n",tv0.tv_sec,tv0.tv_usec);
    printf("tp sec %d nsec %d\n",tp0.tv_sec,tp0.tv_nsec);
    printf("tms sec %d usec %d\n",tms0.tms_utime,tms0.tms_stime);

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
