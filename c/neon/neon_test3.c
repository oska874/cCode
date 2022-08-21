#include <arm_neon.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>


int add_normal(uint8_t *vec1, uint8_t *vec2, uint8_t *res,uint32_t row, uint32_t col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            *(res+i*row+j) = *(vec2+i*row+j)+*(vec1+i*row+j);
//            printf("%d ",*(res+i*row+j));
        }
    }
    return 0;
}

int add_vect(uint8_t *vec1, uint8_t *vec2, uint8_t *res,uint32_t row, uint32_t col)
{
    uint8x16_t v1,v2,sum;

    sum = vdupq_n_u8(0);
    for(int i=0;i<row*col;i+=16){
        v1 = vld1q_u8(vec1+i);
        v2 = vld1q_u8(vec2+i);
        sum = vaddq_u8(v1,v2);

        res[i+0]=vgetq_lane_u8(sum,0);
        res[i+1]=vgetq_lane_u8(sum,1);
        res[i+2]=vgetq_lane_u8(sum,2);
        res[i+3]=vgetq_lane_u8(sum,3);
        res[i+4]=vgetq_lane_u8(sum,4);
        res[i+5]=vgetq_lane_u8(sum,5);
        res[i+6]=vgetq_lane_u8(sum,6);
        res[i+7]=vgetq_lane_u8(sum,7);
        res[i+8]=vgetq_lane_u8(sum,8);
        res[i+9]=vgetq_lane_u8(sum,9);
        res[i+10]=vgetq_lane_u8(sum,10);
        res[i+11]=vgetq_lane_u8(sum,11);
        res[i+12]=vgetq_lane_u8(sum,12);
        res[i+13]=vgetq_lane_u8(sum,13);
        res[i+14]=vgetq_lane_u8(sum,14);
        res[i+15]=vgetq_lane_u8(sum,15);
    }
    
    return 0;
}


int main()
{
    const uint32_t row = 1000,col=1000;
    uint8_t *m1,*m2,*m3;
    struct timespec start,end;


    m1=malloc(sizeof(uint8_t)*1000*1000);
    m2=malloc(sizeof(uint8_t)*1000*1000);
    m3=malloc(sizeof(uint8_t)*1000*1000);
    memset(m1,5,row*col);
    memset(m2,9,row*col);
    memset(m3,0,row*col);

    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    add_normal(m1,m2,m3,1000,1000);
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);

    printf("normal cost %ld %ld\n",end.tv_sec - start.tv_sec,end.tv_nsec - start.tv_nsec);

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(*(m3+i*row+j) != 14){
                printf("%d ",*(m3+i*row+j));
            }
        }
    }
    printf("\n");

    memset(m1,5,row*col);
    memset(m2,9,row*col);
    memset(m3,0,row*col);
    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    add_vect(m1,m2,m3,1000,1000);
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);

    printf("vect cost %ld %ld\n",end.tv_sec - start.tv_sec,end.tv_nsec - start.tv_nsec);

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(*(m3+i*row+j) != 14){
                printf("%d ",*(m3+i*row+j));
            }
        }
    }
    printf("\n");

    return 0;
}

    

