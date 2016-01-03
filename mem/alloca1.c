#include <alloca.h>
#include <stdio.h>


int main()
{
    void *p;
    p=alloca(1024);
    *(int *)p=0x12345678;
    printf("p %x\n",*(int *)p);
    //no need to free
    return 0;
}
