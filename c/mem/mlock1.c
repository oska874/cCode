#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    char vec=0;
    void *a;
    a=mmap(0,getpagesize()*8,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
    if(a<0) {
        perror("mmap failed ");
        exit(-1);
    }
    int ret = mlock(a,getpagesize()*2);
    if (ret ) {
        perror("lock failed ");
        munmap(a,getpagesize()*2);
        exit(-1);
    }

    printf("vec0 %x\n",vec);
    ret = mincore(a,getpagesize()*2,&vec);
    if (ret ) {
        perror("test failed ");
        munmap(a,getpagesize()*2);
        exit(-2);
    }
    printf("vec1 %x\n",vec);

    ret = munlock(a,getpagesize()*2); //or munlockall()
    if (ret) {
        perror("unlock failed ");
        munmap(a,getpagesize()*2);
        exit(-3);
    }
    ret = mincore(a,getpagesize()*2,&vec);
    if (ret ) {
        perror("test2 failed ");
        munmap(a,getpagesize()*2);
        exit(-2);
    }
    printf("vec2 %x\n",vec);

    return 0;
}

