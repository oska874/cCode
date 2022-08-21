#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <linux/limits.h>
#include <wait.h>
#include <unistd.h>

void hello(void)
{
    for(int i=0;i<10;i++) 
        printf("bye1\n");
}

int main(void)
{
    int ret = 0;
    pid_t pid;
    pid = fork();
    if (pid != 0) {//parent
        wait(&ret);
        printf("c pid %d ret %d\n",pid,ret);
    }
    else if (pid == 0) { //child
        hello();
        exit(0);
    }
    printf("done\n");
    return 0;
}
