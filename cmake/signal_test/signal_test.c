/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define _GNU_SOURCE


void my_handler(int sig)
{
    printf("sig %d\n",sig);
    exit(EXIT_SUCCESS);
}

int sig_test1(void)
{
    if(signal(SIGINT,my_handler) == SIG_ERR) {
        perror("register signal fail ");
        exit(-1);
    }

    char *msg={"abcd"};
    psignal(SIGINT,msg);
    printf("sig:%s",strsignal(SIGINT));

    return 0;
}


/*sigprocmsk的使用*/
void msg(int signo)
{
    if(signo==SIGINT)
        printf("Get SIGINT!\n");
    else
        printf("Get SIGQUIT!\n");
}

int sig_test2(void)
{
    sigset_t sigset,oset;/*sigset存放屏蔽信号，oset保存当前屏蔽信号*/

    sigemptyset(&sigset);/*清空信号集*/
    sigaddset(&sigset,SIGINT);/*添加SIGINT信号，信号集中仅有SIGINT*/


    sigprocmask(SIG_BLOCK,&sigset,&oset);/*加入屏蔽信号*/

    signal(SIGINT,msg);
    signal(SIGQUIT,msg);
    for (int i=0;i<900000000;i++)
        ;;
    raise(SIGINT);/*发送SIGINT信号*/
    raise(SIGQUIT);
    return 0;
}


void sig_usr2_handler(int signo,siginfo_t *info,void *p)
{
    printf("usr2 %d\n",signo);
    printf("int %d si_code %d si_queue %d signo %d\n",info->si_int,info->si_code,SIGUSR2,info->si_signo);
}


//prefered signal usage
int sig_test3(void)
{
    union sigval value;
    int ret;

    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction=sig_usr2_handler;
    act.sa_flags=SA_SIGINFO;
    sigaction(SIGUSR2,&act,NULL);

    value.sival_int = 404;
    ret = sigqueue (getpid(), SIGUSR2, value);//send signal
    if (ret)
        perror("sigqueue");
    return 0;
}

