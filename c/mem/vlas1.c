#include <stdio.h>

int main(void)
{
    int i=0;
    scanf("%d",&i);
    printf("%d\n",i);
    char va[i];
    for(int j=0;j<i;j++)
        va[j]=j;
    for(int j=0;j<i;j++)
        printf("%d ",va[j]);
    printf("\n");
    return 0;
}

