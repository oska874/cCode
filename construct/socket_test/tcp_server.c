/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

#define PACK_BUF_SIZE       1000
#define TCP_PORT            6000

static int tcpsocket = -1;
static int tcpcli = -1;
static struct sockaddr_in tcpservaddr;
static struct sockaddr_in tcpcliaddr;
static int len_sock=sizeof(struct sockaddr);

int tcp_server_setup()
{
    int ret=-1;
   
    memset(&tcpservaddr,0,sizeof(tcpservaddr));
#if 0  
    memset(&tcpcliaddr,0,sizeof(tcpcliaddr));
    
  
    tcpcliaddr.sin_port=htons(TCP_PORT);
    tcpcliaddr.sin_family=AF_INET;
    tcpcliaddr.sin_addr.s_addr=INADDR_ANY;
#endif        
    tcpservaddr.sin_family=AF_INET;
    tcpservaddr.sin_addr.s_addr=INADDR_ANY;
    tcpservaddr.sin_port=htons(TCP_PORT);
        
    tcpsocket = socket(AF_INET,SOCK_STREAM,0);
    if(tcpsocket < 0){
        perror("tcp ser  socket fail ");
        exit(-1);
    }
        
    ret=bind(tcpsocket,(struct sockaddr *)&tcpservaddr,sizeof(tcpservaddr));
    if (ret){
        perror("tcp ser bind fail ");
        exit(-2);
    }
    
    printf("server listening\n");
    ret = listen(tcpsocket,0);
    if(ret){
        perror("tcp ser listen fail ");
        close(tcpsocket);
        exit(-3);
    }
    
    tcpcli = accept(tcpsocket,(struct sockaddr *)&tcpcliaddr,(socklen_t*)&len_sock);
    if (ret <0) {
        perror("tcp server accept fail ");
        close(tcpsocket);
        close(tcpcli);
        exit(-4);
    }
    return 0;
}

int tcp_server_work()
{
    int len;
    int ret;
    int i=0;
    unsigned char buf[PACK_BUF_SIZE];
    char *got="got";
    
    len = send(tcpcli,got,3,0);
    printf("0 send %d\n",len);

    while((len=recv(tcpcli,buf,PACK_BUF_SIZE,0))>0){
        printf("recv %d: ",i);
        i++;
        for (int i=0;i<len;i++){
            printf("%x ",buf[i]);
        }
        printf("\n");
        ret = send(tcpcli,got,3,0);
        if(ret < 3){
            perror("ser reply fail ");
        }
    }
    close(tcpsocket);
    close(tcpcli);
    return 0;
}