#include <stdlib.h>

int main()
{
    int ar[10];
    int * restrict restar=(int *)malloc(10*sizeof(int));
    int *par=ar;

    for(int n=0;n<10;n++)
    {
        par[n]+=5;
        restar[n]+=5;
        ar[n]*=2;
        par[n]+=3;
        restar[n]+=3;
    }

    return 0;
}

