/* 
 * File:   
 * Author: ezio
 *
 * Created on 2016年2月25日, 下午9:14
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/un.h>
#include <sys/socket.h>

#define SV_SOCK_PATH    "/tmp/us_xfr"
#define BUF_SIZE        100

#define BACKLOG         5


int main(void)
{   
    struct sockaddr_un addr;
    int sfd;
    ssize_t numRead;
    char buf[BUF_SIZE];
 
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        exit(-1);

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) -1);

    if(connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
        exit(-2);

    while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
        if(write(sfd, buf, numRead) != numRead)
            perror("parital/failed write ");

    if (numRead == -1)
        exit(-3);

    return 0;
}
