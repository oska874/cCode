#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <linux/limits.h>
#include <unistd.h>

void hello(void)
{
    printf("bye1\n");
    exit(1);
}

int main(void)
{
    int ret = 0;

    if (ret ==-1){
        perror("open fail\n");
        exit(0);
    }
    atexit(hello);

    long atexit_max;
    atexit_max = sysconf (_SC_ATEXIT_MAX);
    printf ("atexit_max=%ld\n", atexit_max);

    return 0;
}
