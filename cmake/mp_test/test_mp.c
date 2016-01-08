/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void mp_example0(void)
{
    pid_t cid ;
    pid_t pid;
    pid_t tid;
    
    tid = fork();
    if( tid ==0){
        usleep(1000);
        printf("i'm child\n");
        usleep(1000);
        printf("i'm running\n");
        usleep(1000);
        printf("i'm leaving\n");
            
    }
    else if (tid == -1){
        perror("fork fail ");
    }
    else {
        pid=getpid();
        printf("i'm father %d\n",pid);
    }
}
