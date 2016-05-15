#include <stdio.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <unistd.h>


#define DEV_NAME "/dev/mem5"
int main()
{
    int fd;
    char buf[100];
    
    fd = open(DEV_NAME,O_RDWR);
    read(fd,buf,0);
    write(fd,buf,0);
    ioctl(fd,0,0);
    close(fd);
}
