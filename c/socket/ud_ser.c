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
#include <ctype.h>

#include <sys/un.h>
#include <sys/socket.h>

#define SV_SOCK_PATH    "/tmp/us_xfr"
#define BUF_SIZE        10

#define BACKLOG         5

int main(void)
{   
    struct sockaddr_un svaddr,claddr;
    int sfd,j;
    ssize_t numRead;
    socklen_t len;
    char buf[BUF_SIZE];
    
    
    sfd = socket(AF_UNIX , SOCK_DGRAM, 0);
    if (sfd == -1)
        exit(-1);
    
    if(unlink(SV_SOCK_PATH) == -1 && errno != ENOENT)
        exit(-2);
    
    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) -1 );
    
    if(bind(sfd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un))== -1)
        exit(-3);

    for(;;) {
        len = sizeof(struct sockaddr_un);
        numRead = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, &len);
        
        if(numRead == -1)
            exit(-4);
        printf("server recved %ld bytes from %s\n",(long) numRead, claddr.sun_path);

        for(j = 0; j<numRead; j++)
            buf[j] = toupper((unsigned char )buf[j]);

        if (sendto(sfd, buf, numRead, 0, (struct sockaddr *)&claddr, len) != numRead)
            perror("sendto ");
    }
    return 0;
}
            

