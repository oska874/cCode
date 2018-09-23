
#ifdef NEON
#include <arm_neon.h>
#endif
#include <stdio.h>
#include <time.h>
#include <sys/time.h> 


    int m3[40]={0};
#ifdef NEON
void neon_float_matrix_vec_mul(const float *matrix, const float *vec, float *vec_ret, int row, int col)
{
    float32x4_t sum, a, x;
    for (int i = 0; i < row; i++) {
        sum = vdupq_n_f32(0);
        for (int j = 0; j < col; j += 4) {
            a = vld1q_f32(matrix + i*col + j);
            x = vld1q_f32(vec + j);
            sum = vmlaq_f32(sum, a, x);
        }
        vec_ret[i] = vgetq_lane_f32(sum, 0)
                     +vgetq_lane_f32(sum, 1)
                     +vgetq_lane_f32(sum, 2)
                     +vgetq_lane_f32(sum, 3);
    }
}


void neon_float_matrix_mul(const float *matrix, const float *vec, float *vec_ret, int row, int col,int col2)
{
    float32x4_t va,vb;
    float32x4_t vc[20];//malloc uses too much time
    
    for(int i =0;i<12;i++){
        vc[i] = vdupq_n_f32(0.0f);
    }

    for(int i=0;i<col;i++){
        vb = vld1q_f32(vec+col2*i);
        for(int j=0;j<row;j++){
            va = vdupq_n_f32(matrix[i+j*col]);
            vc[j] = vmlaq_f32(vc[j],va,vb);
        }
    }

    for(int i=0;i<row;i++){
        vst1q_f32(&vec_ret[i*col2], vc[i]);
    }
}
#endif

void float_matrix_vec_mul(const float *mat, const float *vec, float *vec_ret, int row, int col)
{
    for(int i=0;i<row;i++){
        float sum = 0;
        for(int j=0;j<col;j++)
        {
            sum += mat[i*col+j] * vec[j];
        }
        vec_ret[i] = sum;
    }
}

void matrix_transp(const float *mat1, float *mat2, int row, int col)
{
    printf("old\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%f ",mat1[i*col+j]);
        }
        printf("\n");
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            mat2[j+i*row] = mat1[j*row +i];
        }
    }
    printf("new\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%f ",mat2[i*col+j]);
        }
        printf("\n");
    }
}



void float_matrix_mul(const float *mat, const float *vec, float *vec_ret, int row1, int col, int col2)
{
    float temp;
    for(int i=0;i<row1;i++){
        for(int j=0;j<col2;j++){
            temp=0;
            for(int k=0;k<col;k++){
                temp += mat[i*col +k] * vec[j + k*col2];
            }
            vec_ret[i*col2+j] = temp;
        }
    }
}

void int_matrix_mul(int *mat, int *vec, int *vec_ret, int row1, int col, int col2)
{
    int temp,i,j,k;
    for(i=0;i<row1;i++){
        for(j=0;j<col2;j++){
            temp=0;
            for(k=0;k<col;k++){
                temp += mat[i*col+k] * vec[j + k*col2];
            }

            *(vec_ret+i*col2+j) = temp;
            printf("%d-%d-%d %d\n",i,j,k,temp,*(vec_ret+i*col2+j),vec_ret,m3);
        }
    }
    printf("lllll\n");
}

int main()
{ 
    const int MATRIX_SIZE = 48;
    float mat1[]= {1.1,1.2,1.3,1.4,
                   1.5,1.6,1.7,1.8,
                   1.9,2.0,2.1,2.2,
                   1.5,1.6,1.7,1.8,
                   1.9,2.0,2.1,2.2,
                   2.3,2.4,2.5,2.6,
                   1.1,1.2,1.3,1.4,
                   1.5,1.6,1.7,1.8,
                   1.9,2.0,2.1,2.2,
                   1.5,1.6,1.7,1.8,
                   1.9,2.0,2.1,2.2,
                   2.3,2.4,2.5,2.6
                  };
    float mat2[]= {2.1,2.2,2.3,2.4,
                   2.5,2.6,2.7,2.8,
                   2.9,3.0,3.1,3.2,
                   3.3,3.4,3.5,3.6
                  };
    float vec1[]={2.1,2.2,2.3,2.4};
    float mat3[MATRIX_SIZE];
    float mat4[16];
#ifdef CGT
    struct timespec start,end;
#else
    struct timeval start, end;
#endif

    int y[100]={0};
    int sums=0;


    int m1[]={
        1,2,3,4,
        2,3,4,5,
        3,4,5,6,
        4,5,6,7,
        5,6,7,8,
        6,7,8,9,
        7,10,11,12,
        8,11,12,13,
    };
    int m2[]={
        2,3,4,5,
        3,4,5,6,
        4,5,6,7,
        5,6,7,8,
    };


    //int_matrix_mul(m1,m2,m3,8,4,4);

#if 0
    for(int x=0;x<100;x++){


#ifdef CGT
        clock_gettime(CLOCK_MONOTONIC_RAW,&start);
#else
        gettimeofday( &start, NULL );
#endif

        neon_float_matrix_vec_mul(mat1,vec1,&mat3[0],12,4);

#ifdef CGT
        clock_gettime(CLOCK_MONOTONIC_RAW,&end);
        printf("N1 vect cost %ld %ld\n",end.tv_sec - start.tv_sec,end.tv_nsec - start.tv_nsec);
        y[x]= end.tv_nsec - start.tv_nsec;
#else
        gettimeofday( &end, NULL );
        printf("1end   : %d.%d\n",end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
        y[x]= end.tv_usec - start.tv_usec;
#endif


#if 0
        for(int i=0; i<12; i++) {
            printf("%f\n",mat3[i]);
        }
        printf("end\n");
#endif

#ifdef CGT
        clock_gettime(CLOCK_MONOTONIC_RAW,&start);
#else
        gettimeofday( &start, NULL );
#endif

        float_matrix_vec_mul(mat1,vec1,&mat3[0],12,4);

#ifdef CGT
        clock_gettime(CLOCK_MONOTONIC_RAW,&end);
        printf("S1 vect cost %ld %ld\n",end.tv_sec - start.tv_sec,end.tv_nsec - start.tv_nsec);
#else
        gettimeofday( &end, NULL );
        printf("2end   : %d.%d\n",end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
#endif

#if 0
        for(int i=0; i<12; i++) {
            printf("%f\n",mat3[i]);
        }
        printf("end\n");
#endif

#ifdef CGT
        y[x]= end.tv_nsec - start.tv_nsec - y[x];
#else
        y[x]= end.tv_usec - start.tv_usec - y[x];
#endif
        sums+=y[x];
        printf("A %d\n",y[x]);
    }
    printf("%d\n",sums/100);
#endif


//    matrix_transp(mat2,mat4,4,4);

    for(int x=0;x<1;x++){

#ifdef NEON
#ifdef CGT
        clock_gettime(CLOCK_MONOTONIC_RAW,&start);
#else
        gettimeofday( &start, NULL );
#endif

        neon_float_matrix_mul(mat1,mat2,mat3,12,4,4);

#ifdef CGT
        clock_gettime(CLOCK_MONOTONIC_RAW,&end);
        printf("N2 vect cost %ld %ld\n",end.tv_sec - start.tv_sec,end.tv_nsec - start.tv_nsec);
        y[x]= end.tv_nsec - start.tv_nsec;
#else
        gettimeofday( &end, NULL );
        printf("1end   : %d.%d\n",end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
        y[x]= end.tv_usec - start.tv_usec;
#endif


#if 1
        for(int i=0; i<48; i++) {
            printf("%f\n",mat3[i]);
        }
        printf("end\n");
#endif
#endif

#ifdef CGT
        clock_gettime(CLOCK_MONOTONIC_RAW,&start);
#else
        gettimeofday( &start, NULL );
#endif

        float_matrix_mul(mat1,mat2,&mat3[0],12,4,4);

#ifdef CGT
        clock_gettime(CLOCK_MONOTONIC_RAW,&end);
        printf("S2 vect cost %ld %ld\n",end.tv_sec - start.tv_sec,end.tv_nsec - start.tv_nsec);
#else
        gettimeofday( &end, NULL );
        printf("2end   : %d.%d\n",end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
#endif

#if 1
        for(int i=0; i<48; i++) {
            printf("%f\n",mat3[i]);
        }
        printf("end\n");
#endif

#ifdef CGT
        y[x]= end.tv_nsec - start.tv_nsec - y[x];
#else
        y[x]= end.tv_usec - start.tv_usec - y[x];
#endif
        sums+=y[x];
        printf("A %d\n",y[x]);
    }
    return 0;
}
