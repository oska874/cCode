/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAP_SIZE 0x4000
#define MAP_OFSET 0

static void *mp;

int open_mmap()
{
    int fd;        
    fd = open("./tests",O_RDWR); //open a normal file or /dev/mem
    if(fd <0) {
        perror("open fail ");
        exit(-1);
    }
    mp = mmap(0,MAP_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,MAP_OFSET);//length and offset must aligin with 4k
    if (mp == MAP_FAILED){
        perror("map failed ");
        exit(-2);
    }
    printf("opened ok\n");
    return 0;
}

int open_anony_mmap()
{
    mp = mmap(0,MAP_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,MAP_OFSET);//length and offset must aligin with 4k
    if (mp == MAP_FAILED){
        perror("map failed ");
        exit(-2);
    }
    printf("opened ok\n");
    return 0;
}

int close_mmap()
{
    int ret;
    ret = munmap(mp,MAP_SIZE);
    if (ret){
        perror("unmap fail ");
        exit(-3);
    }
    return 0;
}
void read_mem(void)
{
    for(int i=0;i<100;i++){
        printf("%x ",*((unsigned char*)mp+i));
    }
    printf("\n");
}

void write_mem(void)
{
    for(int i=0;i<100;i++){
        *((unsigned char *)mp+i) = i;
    }
    printf("\n");
}