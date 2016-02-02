/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void vread(int fd,const struct iovec *iov,int cnt )
{
    int ret=0;
    ret = readv(fd,iov,cnt);
    if(ret<=0)
        printf("read none %d\n",ret);
}

void vwrite(int fd,const struct iovec *iov,int cnt )
{
    int ret=0;
    ret = writev(fd,iov,cnt);
    if(ret <= 0)
        printf("write nond %d\n",ret);
}
int main()
{    
    struct iovec wiov[2],riov[2];
    char *buf;
    int fd ;
    int ret;
    char fname[]="/tmp/testvXXXXXX"; //must be XXXXXX
    ret = mkstemp(fname);
    if(ret <0) {
        perror("mkstemp fail");
        fd = open("/tmp/testv",O_RDWR|O_CREAT);
    }
    else{
        fd = open(fname,O_RDWR);
    }
    if (fd <0){
        perror("open fail");
        exit(-1);
    }
    buf =(char *) malloc(1024);
    
    memset(buf,0xac,512);
    memset(&buf[512],0x5b,512);
    
    riov[0].iov_base = &buf[0];
    riov[0].iov_len=100;
    
    riov[1].iov_base = &buf[512];
    riov[1].iov_len=100;
    
    wiov[0].iov_base = &buf[0];
    wiov[0].iov_len=100;
    
    wiov[1].iov_base = &buf[512];
    wiov[1].iov_len=100;
        
    vwrite(fd,wiov,2);
    
    memset(buf,0,1024);
   
    //readv after writev should close file ,or won't read anything
    close(fd);
   
    fd = open("/tmp/testv",O_RDONLY);
    if (fd <0){
        perror("open fail2");
        exit(-2);
    }
    vread(fd,riov,2);
    
    printf("%x %x \n",buf[0],buf[512]);    
    
    close(fd);
    free(buf);
    unlink(fname);
    return 0;
}