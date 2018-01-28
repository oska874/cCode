#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <time.h>

void critical1(void)
{
    #pragma omp parallel
    {
        printf( "All threads run this\n");
        #pragma omp sections
        {
            #pragma omp section
            {
                printf( "This executes in parallel\n");
            }
            #pragma omp section
            {
                printf( "Sequential statement 1\n");
                printf( "This always executes after statement 1\n");
            }
            #pragma omp section
            {
                printf( "This also executes in parallel\n");
            }
        }
    }
}

void gettime (void)
{
    int i, nthreads;
    clock_t clock_timer;
    double wall_timer;
    double c[1000000];

    for (nthreads = 1; nthreads <=8; ++nthreads) {
        clock_timer = clock();
        wall_timer = omp_get_wtime();
        #pragma omp parallel for private(i) num_threads(nthreads)
        for (i = 0; i < 1000000; i++)
            c[i] = sqrt(i * 4 + i * 2 + i);
        printf("threads: %d %f %f\n",
               nthreads, (double) (clock() - clock_timer) / CLOCKS_PER_SEC, omp_get_wtime() - wall_timer);
    }
}
static void sequencs(void)
{
    #pragma omp parallel for
    for (int i = 0; i < 10; i++ ) {
        printf("i = %d\n", i);
    }
    printf("\n");
}

static void multi(void)
{
    #pragma omp parallel
    {
        printf("Hello World!\n");
    }
}

static void seq1(void)
{
    int a[100000], b[100000];
    // ... some initialization code for populating arrays a and b;
    int c[100000];
    for(int i=0; i<100000; i++) {
        a[i]=i%256;
        b[i]=i%256;
    }
    #pragma omp parallel for
    for (int i = 0; i < 100000; ++i) {
        c[i] = a[i] * b[i] + a[i-1] * b[i+1];
        //printf("%d ",c[i]);
    }
    // ... now do some processing with array c
    printf("\n");
}


int main()
{
    sequencs();
    multi();
    seq1();
    gettime();
    critical1();
    return 0;
}
