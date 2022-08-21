#include <stdio.h>
#include <stdlib.h>



int main()
{
    void *p;
    p=calloc(1,1024);
    *(char *)p=0xac;
    printf("%x\n",*(char *)p);
    free(p);
    return 0;
}
