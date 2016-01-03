#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    void *p;
    int fd = open("/dev/zero",O_RDONLY);
    if (fd <0) {
        perror ("open failed ");
        exit(-1);
    }

    p = mmap(NULL,getpagesize(),PROT_READ,MAP_PRIVATE,fd,0);
    if (p <0) {
        perror("map failed ");
        exit(-2);
    }
    for(int i = 0;i<16;i++) {
        printf("%x ",*(unsigned int *)((unsigned int *)p+i));
    }
    printf("\n");
    int ret = munmap(p,getpagesize());
    if (ret <0)
        perror("umap fail ");
    return 0;
}

