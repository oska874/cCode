/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 1024

int shmem_test(void)
{
    int mid;
    char *shmaddr ;
    int flag=0;
    struct shmid_ds buf ;
    printf("share mem\n");
    mid = shmget(IPC_PRIVATE,0x100000,IPC_CREAT|IPC_EXCL);
    if(mid <0){
        perror("get share mem fail ");
        exit(-1);
    }
    int pid = fork();
    
    if(pid == 0){
        shmaddr = (char *)shmat(mid, NULL, 0);
        if ( shmaddr == (char *)-1 ){
            perror("shmat addr error ") ;
            exit(-1);
        }
        strcpy( shmaddr, "Hi, I am child process!\n") ;
        shmdt( shmaddr ) ;
        exit(0);
    } 
    else if ( pid > 0) {
        sleep(3 );
        flag = shmctl( mid, IPC_STAT, &buf) ;
        if ( flag == -1 ){
            perror("shmctl shm error ") ;
            exit(-1) ;
        }
        printf("shm_segsz =%d bytes\n",(int) buf.shm_segsz ) ;
        printf("parent pid=%d, shm_cpid = %d \n", getpid(), buf.shm_cpid ) ;
        printf("chlid pid=%d, shm_lpid = %d \n",pid , buf.shm_lpid ) ;
        
        shmaddr = (char *) shmat(mid, NULL, 0) ;
        if (shmaddr == (char *)-1 ){
            perror("shmat addr error ") ;
            exit(-2);
        }

        printf("recv :%s", shmaddr) ;
        shmdt( shmaddr ) ;
        shmctl(mid, IPC_RMID, NULL) ;
    }
    else{
        perror("fork error") ;
        shmctl(mid, IPC_RMID, NULL) ;
        exit(-3);
    }
    return 0 ;
}
