#include <sys/time.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void alarm_handler (int signo)
{
    printf ("Timer hit!\n");
}

void foo (void) 
{
    struct itimerval delay;
    int ret;

    signal (SIGALRM, alarm_handler);

    delay.it_value.tv_sec = 5;
    delay.it_value.tv_usec = 0;

    delay.it_interval.tv_sec = 2;
    delay.it_interval.tv_usec = 0;

    ret = setitimer (ITIMER_REAL, &delay, NULL);

    if (ret) {
        perror ("setitimer");
        return;
    }
    while(1);
    pause();
}


int main(void)
{
    foo();
    return 0;
}

