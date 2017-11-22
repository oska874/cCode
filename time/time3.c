#include <stdio.h>
#include <unistd.h> 
#include <time.h>  
#include <string.h>


int main()
{
    //sleep 非线程安全
    //usleep 线程安全
    //nanosleep 纳秒级

    int ret;
    struct timespec timeres[2];
    struct timespec req,rem;
    req.tv_sec=1;
    req.tv_nsec=5000000;
    memset(&rem,0,sizeof(struct timespec));

    clock_gettime(CLOCK_MONOTONIC_RAW,&timeres[0]);
    ret = nanosleep(&req,&rem);
    if(ret != 0){
        perror("fail1");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&timeres[1]);
    printf("%ld %ld\n",timeres[1].tv_sec-timeres[0].tv_sec,
            timeres[1].tv_nsec-timeres[0].tv_nsec);
    printf("%ld %ld\n",rem.tv_sec,rem.tv_nsec);

    printf("------------------\n");

    clock_gettime(CLOCK_MONOTONIC_RAW,&timeres[0]);
    ret = clock_nanosleep(CLOCK_MONOTONIC,0,&req,&rem);
    if(ret != 0){
        printf("fail\nno errno\n");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&timeres[1]);
    printf("%ld %ld\n",timeres[1].tv_sec-timeres[0].tv_sec,
            timeres[1].tv_nsec-timeres[0].tv_nsec);
    printf("%ld %ld\n",rem.tv_sec,rem.tv_nsec);
    return 0;
}


    
