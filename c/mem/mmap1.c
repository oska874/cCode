#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//anonymous mmap
int main()
{
    void *p;
    int i;
    p = mmap(NULL,0x100000,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
    if (p <0) {
        perror("map failed ");
        exit(-1);
    }
    memset((unsigned char *)p,0xac,1024);
    for(i = 0;i<16;i++) {
        printf("%x ",*(unsigned char *)((unsigned char *)p+i));
    }
    printf("\n");
    int ret = munmap(p,0x100000);
    if (ret <0)
        perror("umap fail ");
    return 0;
}

