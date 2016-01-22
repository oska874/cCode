#include <stdio.h>
#include <omp.h>

static void sequencs(void)
{
#pragma omp parallel for
     for (int i = 0; i < 10; i++ )
     {
         printf("i = %d\n", i);
     }
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
    for(int i=0;i<100000;i++) {
        a[i]=i%256;
        b[i]=i%256;
    }
    #pragma omp parallel for 
    for (int i = 0; i < 100000; ++i) {
      c[i] = a[i] * b[i] + a[i-1] * b[i+1];
      printf("%d ",c[i]);
    }
    // ... now do some processing with array c
 }


int main()
{
    sequencs();
    multi();
    seq1();
    return 0;
}