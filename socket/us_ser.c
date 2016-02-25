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
#include <errno.h>

#include <sys/un.h>
#include <sys/socket.h>

#define SV_SOCK_PATH    "/tmp/us_xfr"
#define BUF_SIZE        100

#define BACKLOG         5

#define STDIO_FILENO    1
int main(void)
{   
    struct sockaddr_un addr;
    int sfd,cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];
    
    
    sfd = socket(AF_UNIX , SOCK_STREAM , 0);
    if (sfd == -1)
        exit(-1);
    
    if(unlink(SV_SOCK_PATH) == -1 && errno != ENOENT)
        exit(-2);
    
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) -1 );
    
    if(bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un))== -1)
        exit(-3);

    if(listen(sfd, BACKLOG) == -1)
        exit(-4);

    for(;;) {
        cfd = accept(sfd,NULL,NULL);
        if (cfd == -1)
            exit(-5);

        while( (numRead = read(cfd, buf, BUF_SIZE))>0)
            if(write(STDOUT_FILENO, buf, numRead) != numRead)
                perror("partial/failed write ");

        if (numRead == -1)
            exit(-6);
        if (close(cfd) == -1)
            perror("close ");
    }
    return 0;
}
            

