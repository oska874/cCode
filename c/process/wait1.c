#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (void)
{
    int status;
    pid_t pid=1;
    pid = fork();
    printf("pid %d\n",pid);

    if (pid == 0) {
        for(int i=0;i<10;i++) {
            printf("in child \n");
        }
        return 1;
    }
    else if (pid >0){
        printf("in parent\n");
    }
    else {
        perror("fork error\n");
    }

    pid = wait(&status);
    if (pid == -1)
        perror ("wait");

    printf("pid=%d\n", pid);

//    if (WIFSIGNALED (status))
//        printf ("Killed by signal=%d%s\n", WTERMSIG(status), WCOREDUMP(status) ? " (dumpedcore)" : "");
    if (WIFSTOPPED (status))
        printf ("Stopped by signal=%d\n", WSTOPSIG(status));
    if (WIFCONTINUED (status))
        printf ("Continued\n");
    if (WIFEXITED (status))
        printf ("Normal termination with exit status=%d\n", WEXITSTATUS(status));

    return 0;
}
