#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
//#include <linux/fs.h>
#include <linux/limits.h>
int main (void)
{
    pid_t pid;
    int i;
    /* create new process */
    pid = fork ( );
    if (pid == -1){
        perror("fail fork");
        return -1;
    }
    else if (pid != 0) {
        printf("exit parent\n");
        exit (EXIT_SUCCESS);
    }
    /* create new session and process group */
    if (setsid ( ) == -1){
        perror("fail setsid");
        return -1;
    }
    /* set the working directory to the root
    directory */
    if (chdir ("/") == -1) {
        perror("fail chdir");
        return -1;
    }
    /* close all open files--NR_OPEN is overkill,
    but works */
    printf("close files\n");
    for (i = 0; i < NR_OPEN; i++)
        close (i);
    printf("redirect 012\n");
    /* redirect fd’s 0,1,2 to /dev/null */
    open ("/dev/null", O_RDWR); /* stdin */
    dup (0); /* stdout */
    dup (0); /* stderror */
    /* do its daemon thing... */
    while(1);
    return 0;
}
