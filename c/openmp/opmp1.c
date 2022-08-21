#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <string.h>

#define MAX 800000000

int32_t calc_1(void)
{
    int32_t sum=0;
    int32_t i,j;
    for(i=0;i<MAX;i++){
        j=i*i;
        sum+=j;
    }
    return sum;
}


#define MAX_NTHREAD 8
int32_t calc_2(void)
{
    int32_t sum[MAX_NTHREAD]={0},total=0;
    int32_t i;
    int nthreads;

    nthreads = omp_get_num_procs();

    memset(sum,0,sizeof(int32_t)*MAX_NTHREAD);

#pragma omp parallel for
    for(i=0;i<MAX;i++){
        int32_t j=omp_get_thread_num();
        sum[j]+=i*i;
    }

#if 1
    for(i=0;i<nthreads;i++){
        total+=sum[i];
    }
#endif
    //total = sum[0]+sum[1]+sum[2]+sum[3];
    return total;
}



