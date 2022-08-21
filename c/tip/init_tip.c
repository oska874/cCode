#include <stdio.h>


#define MAX 12

typedef struct {
    int a,b,c;
}init_struct;

int main()
{
    printf("init arry: \n");
    int8_t ary[] = {
        [0]=1,
        [2]=3,
        [10]=100
    };

    for(int i=0;i<MAX;i++)
        printf("%d ",ary[i]);
    printf("\n");
    ary[11]=99;
    for(int i=0;i<MAX;i++)
        printf("%d ",ary[i]);
    printf("\n");

    printf("init struct:\n");

    init_struct suct = {
        .a =9,
        .b=10
    };

    printf("struct %d %d %d\n",suct.a,suct.b,suct.c);


    return 0;
}
