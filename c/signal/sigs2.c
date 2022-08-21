#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/signal.h>


void sig_usr2_handler(int signo,siginfo_t *info,void *p)
{
    printf("usr2 %d\n",signo);
    printf("int %d si_code %d si_queue %d signo %d\n",info->si_int,info->si_code,SIGUSR2,info->si_signo);
}


int main(void)
{
    union sigval value;
    int ret;

    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction=sig_usr2_handler;
    act.sa_flags=SA_SIGINFO;
    sigaction(SIGUSR2,&act,NULL);

    value.sival_int = 404;
    ret = sigqueue (getpid(), SIGUSR2, value);
    if (ret)
        perror("sigqueue");
    return 0;
}
