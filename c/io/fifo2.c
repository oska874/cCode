#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define SER_IO "/tmp/ser1"
int main(void)
{
    if(mkfifo(SER_IO,S_IRUSR|S_IWUSR|S_IWGRP) ==-1&& errno != EEXIST)
        exit(-1);

    int sfd = open(SER_IO, O_WRONLY);//|O_NONBLOCK);
    if (sfd <0)
        exit(-2);

    printf("done\n");
    close(sfd);
    unlink(SER_IO);

    return 0;
}

