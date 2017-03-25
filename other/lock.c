#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>


int main()
{
    int fd = open("xx",O_RDWR|O_SYNC);
    if(fd <0){
        exit(-1);
    }
    printf("%d\n",fd);

    if (flock(fd,LOCK_EX)<0)
        exit(-2);

    sleep(10);

    if (flock(fd,LOCK_UN)<0)
        exit(-2);

    return 0;
}
