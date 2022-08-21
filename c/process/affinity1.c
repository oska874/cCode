#define _GNU_SOURCE
#include <sched.h>
#include <sched.h>
//typedef struct cpu_set_t;
//size_t CPU_SETSIZE;

#include <stdio.h>

int main(void)
{
    cpu_set_t set;
    int ret, i;
    CPU_ZERO(&set); /* clear all CPUs */
    CPU_SET(0, &set); /* allow CPU #0 */
    CPU_CLR(1, &set); /* forbid CPU #1 */
    ret = sched_setaffinity (0, sizeof(cpu_set_t),&set);
    if (ret == -1)
        perror ("sched_setaffinity");
    ret = sched_getaffinity (0, sizeof(cpu_set_t),&set);
    if (ret == -1)
        perror ("sched_getaffinity");
    for (i = 0; i< 2; i++) {
        int cpu;
        cpu = CPU_ISSET (i, &set);
        printf ("cpu=%i is %s\n", i, cpu ? "set" :"unset" );
    }
    while(1);
}
