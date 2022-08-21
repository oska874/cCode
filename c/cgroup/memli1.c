#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void *mem1(void *tr)
{
    int size = 0;
    int chunk_size = 512;
    void *p = NULL;
    char cmd[128];
    sprintf (cmd, "echo %ld >> /sys/fs/cgroup/memory/zz/tasks " , syscall(SYS_gettid));
    system (cmd);

    while(1) {

        if ((p = malloc( chunk_size)) == NULL) {
            printf("out of memory!!\n");
            break;
        }
        memset(p, 1, chunk_size);
        size += chunk_size;
        printf("[%d] - memory is allocated [%8d] bytes \n", getpid(), size);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t tr1;
    long t;
    int ret;

    mkdir("/sys/fs/cgroup/memory/zz",755);
    system("echo 16k > /sys/fs/cgroup/memory/zz/memory.limit_in_bytes");

    ret = pthread_create(&tr1,NULL,mem1,(void*)t);
    if (ret) {
        printf ( "ERROR; return code from pthread_create() is %d\n" , ret);
        exit (-1);
    }

    pthread_exit(NULL);
    return 0;
}
