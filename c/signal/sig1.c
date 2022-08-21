#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define _GNU_SOURCE

#include <string.h>

//typedef void (*sighandler_t)(int);

//sighandler_t signal (int signo, sighandler_t handler);

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
    extern const char * const sys_siglist[];
    for(int i=0;i<10;i++) {
        printf("%s \n",sys_siglist[i]);
    }

    char *msg={"abcd"};
    psignal(SIGINT,msg);
    printf("a:%s",strsignal(SIGINT));
    for(;;)
        pause();

    return 0;
}
