#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>
 
 
#define NETLINK_NETLINKTEST     22
#define NETLINK_TEST_ECHO   0x10
 
int main(int argc, char *argv[])
{
    int fd;
    int res;
    int len;
    struct nlmsghdr *nlh = NULL;
    struct sockaddr_nl  saddr, daddr;
    char    *msg = "hello world";
 
    len = strlen(msg);
    fd = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_NETLINKTEST);
    if (!fd) {
        printf("socket() error.\n");
        return -1;
    }
 
    memset(&saddr, 0, sizeof(saddr));
    saddr.nl_family = AF_NETLINK;
    saddr.nl_pid = getpid();
 
    memset(&daddr, 0, sizeof(daddr));
    daddr.nl_family = AF_NETLINK;
    daddr.nl_pid = 0;
 
    res = bind(fd, (const struct sockaddr *)&saddr, sizeof(saddr));
    if (res == -1) {
        printf("bind() error.\n");
        goto error;
    }
 
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(len + 1));
    if (!nlh) {
        printf("malloc() error.\n");
        goto error;
    }
    nlh->nlmsg_type = NETLINK_TEST_ECHO;
    nlh->nlmsg_flags = NLM_F_REQUEST;
    nlh->nlmsg_seq = 0;
    nlh->nlmsg_pid = getpid();
    strcpy(NLMSG_DATA(nlh), msg);
    nlh->nlmsg_len = NLMSG_LENGTH(len + 1);
 
    res = sendto(fd, nlh, NLMSG_SPACE(len + 1), 0, (struct sockaddr *)&daddr, sizeof(daddr));
    if (res == -1)
        printf("send() error.\n");
error:
    free(nlh);
    close(fd);
    return res;
}

