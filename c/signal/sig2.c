#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void my_handler(int sig)
{
    printf("sig %d\n",sig);
    exit(EXIT_SUCCESS);
}

int main(void)
{
    if(signal(SIGINT,my_handler) == SIG_ERR) {
        perror("register signal fail ");
        exit(-1);
    }

    for(int i=0;i<10;i++) {
    //    raise(SIGINT);
        kill(getpid(),SIGINT);
        pause();
    }

    return 0;
}
