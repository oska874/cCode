#include <stdio.h>



void swap(int *m,int*n)
{
    int temp = *m;
    *m=*n;
    *n=temp;
}
void insert_sort(int *base, int num)
{
    int i,j;

    for(i=1;i<num;i++){
        for(j=i;j>0;j--){
            if(base[j]<base[j-1]){
                swap(&base[j],&base[j-1]);
            }
            else{
                break;
            }
        }
    }
}


int main()
{
    int i;
    int x[]={1,2,3,4,5,6,7};
    int y[]={7,6,5,4,3,2,1};
    int z[]={4,2,6,7,5,1,3};

    insert_sort(x,7);
    for(i=0;i<7;i++){
        printf("%d ",x[i]);
    }
    printf("\n");

    insert_sort(y,7);
    for(i=0;i<7;i++){
        printf("%d ",y[i]);
    }
    printf("\n");

    insert_sort(z,7);
    for(i=0;i<7;i++){
        printf("%d ",z[i]);
    }
    printf("\n");

    return 0;
}
