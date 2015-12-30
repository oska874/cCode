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
    pid_t pid;
    pid = fork();
    if (pid != 0) {//parent
        printf("in p\n");
    }
    else if (pid == 0) { //child
        hello();
        exit(0);
    }
    printf("done\n");
    return 0;
}
