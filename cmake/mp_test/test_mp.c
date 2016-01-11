/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/msg.h>

//at exit call
void child_exit()
{
    printf("child %d exit\n",getpid());
}

void father_exit()
{
    printf("father %d exit\n",getpid());
}

//fork
void mp_example0(void)
{
    pid_t pid;
    pid_t tid;
    int ret;
    
    tid = fork();
    if( tid ==0){
        atexit(child_exit);
        usleep(1000);
        printf("i'm child %d\n",getpid());
        usleep(1000);
        printf("i'm running\n");
        usleep(1000);
        printf("i'm leaving\n");
        exit(0);    
    }
    else if (tid == -1){
        perror("fork fail ");
    }
    else {
        waitpid(tid,&ret,WUNTRACED);
        atexit(father_exit);
        pid=getpid();
        printf("i'm father %d\n",pid);    
        wait(NULL);
    }
}

//vfork
void mp_example1(void)
{;
    pid_t pid;
    pid_t tid;
    printf("vfork\n");
    tid = vfork();//make sure child run before father
    if( tid ==0){
        atexit(child_exit);
        usleep(1000);
        printf("i'm child %d\n",getpid());
        usleep(1000);
        printf("i'm running\n");
        usleep(1000);
        printf("i'm leaving\n");
        exit(0);   //child use this tell father his status
    }
    else if (tid == -1){
        perror("fork fail ");
    }
    else {
        pid=getpid();
        printf("i'm father %d\n",pid);
        wait(NULL);
    }
}

//匿名管道
void mp_example2(void)
{
    pid_t pid;
    pid_t tid;
    int ret;
    int pfd[2],pfd1[2];
    
    printf("pipe\n");
    ret = pipe(pfd);
    ret = pipe(pfd1);
    if(ret){
        perror("open pipe fail ");
        exit(-1);
    }
    tid = fork();
    if( tid ==0){
        printf("i'm child %d\n",getpid());
        usleep(2);
        close(pfd[0]);//child write,father read
        close(pfd1[1]);
        if (write(pfd[1],"hello father\n",strlen("hello father\n"))<strlen("hello father\n"))
            perror("not all data wrote");
        int len;
        char buf[128];
        len = read(pfd1[0],buf,sizeof(buf));
        buf[len]='\0';
        printf("c recv %s\n",buf);
        exit(0);    
    }
    else if (tid == -1){
        perror("fork fail ");
    }
    else {
        //waitpid(tid,&ret,WUNTRACED);
        pid=getpid();
        printf("i'm father %d\n",pid);   
        close(pfd[1]);
        close(pfd1[0]);
        int len;
        char buf[128];
        len = read(pfd[0],buf,sizeof(buf));
        buf[len]='\0';
        printf("f recv %s\n",buf);
        if (write(pfd1[1],"hello child\n",strlen("hello child\n")) <strlen("hello child\n"))
            perror("not all data wrote");
        wait(NULL);
    }
    close(pfd[0]);
    close(pfd[1]);
}

//有名管道mkfifo
void mp_example3(void)
{
    pid_t pid;
    pid_t tid;
    int ret;
    int pfd;
    
    printf("fifo\n");
    ret = mkfifo("./myfifo",0666);
    if(ret){
        perror("1 open fifo fail ");
        if(errno == EEXIST){
            remove("./myfifo");            
        }
        ret = mkfifo("./myfifo",0666);
        if(ret){
            perror("2 open fifo fail ");
            exit(-1);
        }
    }
   
    tid = fork();
    if( tid ==0){
        printf("i'm child %d\n",getpid());        
        int len;
        char buf[128];
        pfd = open("./myfifo",O_RDONLY);
        if (pfd <0){
            perror("open fifo fail ");
            exit(-1);
        }
        len = read(pfd,buf,sizeof(buf));
        buf[len]='\0';
        printf("c recv %s\n",buf);
        exit(0);    
    }
    else if (tid == -1){
        perror("fork fail ");
        exit(-1);
    }
    else {
        //waitpid(tid,&ret,WUNTRACED);
        pid=getpid();
        pfd = open("./myfifo",O_WRONLY);
        if (pfd <0){
            perror("open fifo fail ");
            exit(-2);
        }
        printf("i'm father %d\n",pid);   
        if (write(pfd,"hello child\n",strlen("hello child\n")) < strlen("hello child\n"))
            perror("not all data wrote ");
        wait(NULL);
    }
    close(pfd);
}

//kill process
void mp_example4(void)
{
    pid_t pid;
    pid_t tid;
    int ret;
    
    tid = fork();
    if( tid == 0){
        printf("i'm child %d\n",getpid());
        int i=0;
        while(1){
            printf("running child %d\n",i);
            i++;
            sleep(1);
        }        
        exit(0);    
    }
    else if (tid == -1){
        perror("fork fail ");
    }
    else {
        //waitpid(tid,&ret,WNOHANG);
        pid=getpid();
        printf("i'm father %d\n",pid);
        sleep(10);
        ret = waitpid(tid,NULL,WNOHANG); //check child process status
        if(!ret) //child process still running 
            kill(tid,SIGTERM); //using signal to kill child process
        printf("all done\n");
    }
}

//消息队列
void mp_example5(void)
{
    pid_t pid;
    pid_t tid;
    int ret;
    int msgid;
    
    
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT); 
    if (msgid == -1) {
        printf("msgget fail ");
        exit(-1);
    }
    
    tid = fork();
    if( tid == 0){
        printf("i'm child %d\n",getpid());
        char *histr="hello\n";
        ret = msgsnd(msgid,histr,6,MSG_NOERROR|IPC_NOWAIT);
        if(ret) {
            perror("send fail ");
            exit(-1);
        }
         
        exit(0);    
    }
    else if (tid == -1){
        perror("fork fail ");
    }
    else {
        //waitpid(tid,&ret,WNOHANG);
        pid=getpid();
        printf("i'm father %d\n",pid);
        sleep(2);
        char buf[100];
        ret = msgrcv(msgid,buf,10,0,MSG_NOERROR|IPC_NOWAIT);
        if(ret<0){
            perror("msg recv fail ");
            exit(-3);
        }
        buf[ret]='\0';
        printf("recv %s\n",buf);            
        ret = waitpid(tid,NULL,WNOHANG); //check child process status
        if(!ret) //child process still running 
            kill(tid,SIGTERM); //using signal to kill child process
        printf("all done\n");
    }
}