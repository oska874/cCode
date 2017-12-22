#include <stdio.h>

void swap(int *m,int*n)
{
    int temp = *m;
    *m=*n;
    *n=temp;
}

void simple_sort(int *base,int num)
{
    int i,j,k;

    for(i=0;i<num;i++){
        k=i;
        for(j=i+1;j<num;j++){
            if(base[j] < base[k]){
               k=j; 
            }
        }
        swap(&base[i],&base[k]);
    }

}

int main()
{
    int i;
    int x[]={1,2,3,4,5,6,7};
    int y[]={7,6,5,4,3,2,1};
    int z[]={4,2,6,7,5,1,3};

    simple_sort(x,7);
    for(i=0;i<7;i++){
        printf("%d ",x[i]);
    }
    printf("\n");

    simple_sort(y,7);
    for(i=0;i<7;i++){
        printf("%d ",y[i]);
    }
    printf("\n");

    simple_sort(z,7);
    for(i=0;i<7;i++){
        printf("%d ",z[i]);
    }
    printf("\n");


    return 0;
}
