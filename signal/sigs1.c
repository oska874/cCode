	#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

/*sigprocmsk的使用*/
void msg(int signo)
{
    if(signo==SIGINT)
        printf("Get SIGINT!\n");
    else
        printf("Get SIGQUIT!\n");
}

int main()
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
