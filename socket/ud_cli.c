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


int main(int argc, char *argv[])
{   
    struct sockaddr_un svaddr,claddr;
    int sfd,j;
    ssize_t numRead;
    size_t msgLen;
    char buf[BUF_SIZE];
 
    if(argc <2 || strcmp(argv[1],"--help") ==0)
        printf("%s msg ...\n",argv[0]);

    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1)
        exit(-1);

    memset(&claddr, 0, sizeof(struct sockaddr_un));
    claddr.sun_family = AF_UNIX;
    snprintf(claddr.sun_path,  sizeof(svaddr.sun_path), "/tmp/us_xfr.%ld",(long)getpid());

    if(bind(sfd, (struct sockaddr *)&claddr, sizeof(struct sockaddr_un))== -1)
        exit(-3);

    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path)-1);

    for(j=1; j<argc; j++) {
        msgLen = strlen(argv[j]);
        if (sendto(sfd, argv[j], msgLen, 0, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un )) != msgLen)
            perror("sendto ");
        numRead = recvfrom(sfd, buf, BUF_SIZE, 0, NULL, NULL);
        if(numRead == -1)
            exit(-4);
        printf("response %d: %.*s\n",j, (int)numRead, buf);
    }
    unlink(claddr.sun_path);
    return 0;
}
