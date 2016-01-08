#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void alarm_handler (int signum)
{
    printf ("Five seconds passed!\n");
}

void func (void)
{
    signal (SIGALRM, alarm_handler);
    alarm (5);
    pause ();
}

int main()
{
    func();
    printf("end\n");
    return 0;
}
