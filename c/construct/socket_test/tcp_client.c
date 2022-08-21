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
#include <pthread.h>

#define PACK_BUF_SIZE       1000
#define TCP_PORT            6000
#define SER_IP              "192.168.0.111"

static int tcpsocket = -1;
static int tcpcli = -1;
static struct sockaddr_in tcpservaddr;
static int len_sock=sizeof(struct sockaddr);

int tcp_client_setup()
{    
    int ret;
	memset(&tcpservaddr,0,sizeof(tcpservaddr)); //数据初始化--清零  
	tcpservaddr.sin_family=AF_INET; //设置为IP通信  
	tcpservaddr.sin_addr.s_addr=inet_addr(SER_IP);//服务器IP地址  
	tcpservaddr.sin_port=htons(TCP_PORT); //服务器端口号  

    tcpcli=socket(AF_INET,SOCK_STREAM,0);
    if (tcpcli<0) {
        perror("A tcp client  socket fail ");
        exit(-1);
    }
    
    ret = connect(tcpcli,(struct sockaddr *)&tcpservaddr,len_sock);
    if (ret){
        perror("tcp client  connect fail ");
        exit(-2);
    }
    return 0;
}

int tcp_client_work()
{
    unsigned char buf[PACK_BUF_SIZE];
    int len;
    int i=0;
    
    len = recv(tcpcli,buf,PACK_BUF_SIZE,0);
    if (len < PACK_BUF_SIZE) {
        buf[len]='\0';
        printf("0 recv %s\n",buf);
    }
    else
        printf("recv too much %d\n",len);
   
    while(1){
        memset(buf,0xac,PACK_BUF_SIZE);
        
        len = send(tcpcli,buf,PACK_BUF_SIZE,0);
        if(len<PACK_BUF_SIZE){
            perror("1 tcp cli send fail ");
        }
        
        len = recv(tcpcli,buf,PACK_BUF_SIZE,0);
        printf("recv len %d\n",len);
        buf[len]='\0';
        
        printf("recv %d : %s\n",i,buf);        
        i++;
        
    }
    close(tcpsocket);
    close(tcpcli);
    return 0;
}
