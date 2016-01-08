/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define WRITE_SIZE 1024
#define READ_SIZE 1024

void write_file(char *fname)
{
    int fd;
    int ret;
    char *wbuf;
    
    fd = open(fname,O_RDWR|O_CREAT);
    if (fd == -1 ){
        perror("open file fail ");
        exit(-1);
    }
    
    wbuf = (char *)malloc(WRITE_SIZE);
    
    for(int i = 0;i<1024;i++) {
        wbuf[i]=i%256;
    }
    
    ret = write (fd,wbuf,WRITE_SIZE);
    if(ret < WRITE_SIZE) {
        perror("write file unsuccessful  ");
        close(fd);
        exit(-2);
    }
    printf("write %d bytes to file %s\n",ret,fname);
    
    ret = close (fd);
    if (ret) {
        perror("close fail ");   
        exit(-3);
    }
   
}

void read_file(char *fname)
{
    int fd;
    int ret;
    char *rbuf;
    
    fd = open(fname,O_RDONLY);
    
    if (fd == -1 ){
        perror("open file  fail ");
        exit(-1);
    }
    
    rbuf = (char *)malloc(READ_SIZE);
    
    ret = read(fd,rbuf,READ_SIZE);
        
    if(ret < 0){
        perror("read file fail ");
        close(fd);
        exit(-2);
    }       
    printf("read %d bytes from file %s\n",ret,fname);
    
    for(int i=0;i<ret;i++){
        printf("%x ",rbuf[i]);   
    }        
    
    ret = close(fd);
    
    if (ret) {
        perror("close fail ");   
        exit(-2);
    }
    
}

