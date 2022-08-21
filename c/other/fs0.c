#include <sys/statvfs.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <stdlib.h>

int open_file(char *path)
{
    int fd;

    fd = open(path,O_RDWR|O_CREAT);
    if(fd <0){
        perror("open fail:");
        exit(-1);
    }
    return fd;
}

void getfstat1(void)
{
    int ret;
    struct statvfs sbuf;
    ret = statvfs("/workspace",&sbuf);
    if(ret <0){
        perror("get fail:");
        return ;
    }

    printf("fs size %ld blocks %ld \n",sbuf.f_bsize,sbuf.f_blocks);
}

void getfstat2(void)
{
    int ret;
    struct statvfs sbuf;
    int fd;
    fd = open("./a.out",O_RDONLY);
    if (fd <0){
        perror("open fail:");
        return ;
    }

    ret = fstatvfs(fd,&sbuf);
    if(ret <0){
        perror("get fail:");
        return ;
    }

    printf("fs size %ld blocks %ld \n",sbuf.f_bsize,sbuf.f_blocks);
    close(fd);
}

void getfistat1(void)
{
    int ret;
    int fd;
    struct stat sbuf;

    ret = stat("./a.out",&sbuf);
    if(ret < 0){
        perror("fstat fail:");
        return ;
    }
    printf("ino %ld\n",sbuf.st_ino);

    fd =open("./a.out",O_RDONLY);
    if(fd <0){
        perror("open fail:");
        return ;
    }
    ret = fstat(fd,&sbuf);
    if(ret < 0){
        perror("fstat fail:");
        return ;
    }
    printf("ino %ld\n",sbuf.st_ino);
}
        

void mod_ftime0()
{
    int fd;
    int ret;
    struct stat sbuf;
    struct utimbuf tbuf;
    char pname[]="test.exe";
    struct timeval tv0[2];

    fd = open_file(pname);
    close(fd);

    stat(pname,&sbuf);
    printf("atime %ld mtime %ld ctime %ld\n",sbuf.st_atime,sbuf.st_mtime,sbuf.st_ctime);

    tbuf.actime = sbuf.st_atime+10;
    tbuf.modtime = sbuf.st_mtime+10;
    ret = utime(pname,&tbuf);
    if (ret <0){
        perror("utime fail:");
        return ;
    }

    tv0[0].tv_sec = tbuf.actime;
    tv0[0].tv_usec = 88;

    tv0[1].tv_sec = tbuf.actime;
    tv0[1].tv_usec = 88;
    ret = utimes(pname,tv0);
    if (ret <0){
        perror("utimes fail:");
        return ;
    }

    stat(pname,&sbuf);
    printf("atime %ld mtime %ld ctime %ld\n",sbuf.st_atime,sbuf.st_mtime,sbuf.st_ctime);

    unlink(pname);

}
        
int main()
{
    mod_ftime0();
    getfstat1();
    getfstat2();
    getfistat1();
    return 0;
}


