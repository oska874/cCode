#include <stdio.h>
#include <sys/time.h>

float sum_array(float *arr, int len)
{
    if(NULL == arr || len < 1)
    {
        printf("input error\n");
        return 0;
    }
    float sum = 0.0;
    for(int i=0; i<len; ++i)
    {
        sum += *arr++;
    }
    return sum;
}

int main()
{
    float xx[0x1000];
    for(int i=0;i<0x1000;i++){
        xx[i]=i;
    }
    float sum ;
    struct timeval start, end;

    gettimeofday( &start, NULL );
    sum= sum_array(xx,0x1000);
    gettimeofday( &end, NULL );
    printf("end   : %d.%d\n", 
            end.tv_sec - start.tv_sec, 
            end.tv_usec - start.tv_usec);

    printf("sum %f\n",sum);
}

