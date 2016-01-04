#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

static int timers0 = 0;
static timer_t timer;

void alarm_handler (int signo)
{
    printf ("Timer hit!\n");
    timers0++;
    if(timers0==5){
      int ret = timer_delete(timer);
      if(ret)
          perror("timer delete fail ");
    }
}

int main(void)
{
    int ret;
    struct itimerspec ts;
    struct sigevent se0;

    se0.sigev_notify = SIGEV_SIGNAL;
    se0.sigev_value.sival_ptr=&timer;
    se0.sigev_signo=SIGUSR1;

    signal (SIGUSR1, alarm_handler);

    ret = timer_create(CLOCK_REALTIME,&se0,&timer);
    if (ret)
        perror("timer create fail ");
    

    ts.it_interval.tv_sec = 2;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = 2;
    ts.it_value.tv_nsec = 0;

    ret = timer_settime(timer, 0, &ts, NULL);
    if (ret)
        perror ("timer_settime");

    while(1);
    printf("end\n");
    return 0;
}
