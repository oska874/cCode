#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SVR_PATH "/tmp/svr_path"
#define CLI_PATH "/tmp/cli_path"

struct sockaddr_un server_addr;
int fd;
int clifd;
socklen_t addrlen;

void udp_cb(int fd )
{
    char buf[65536];
    char addr_buf_[sizeof(struct sockaddr_un)];

    struct sockaddr_un* cli_addr_ = (struct sockaddr_un*)addr_buf_;
    socklen_t socklen = sizeof(addr_buf_);
    int ret_ = recvfrom(
                   fd,
                   (void*)buf,
                   sizeof(buf),
                   0,
                   (struct sockaddr*)cli_addr_,
                   &socklen);
    if(ret_ > 0) {
        // 注意根据长度来设置零字符
        cli_addr_->sun_path[socklen - 2] = '\0';
        printf("recv '%s' from '%s'\n",buf,cli_addr_->sun_path + 1);
    }
}

void udp_timer(int fd)
{
    const char* msg_ = "hello world";
    printf("send msg %s\n",msg_);
    sendto(clifd,
           msg_,
           strlen(msg_) + 1,
           0,
           (const struct sockaddr*)(&server_addr),
           addrlen);
}


int main()
{
    struct timeval tv1 = {500,0};

    fd = socket(AF_UNIX,SOCK_DGRAM,0);
    server_addr.sun_family = AF_UNIX;
    server_addr.sun_path[0]=0;
    strcpy(server_addr.sun_path + 1,SVR_PATH);
    // 注意计算长度
    addrlen = sizeof(server_addr.sun_family) + sizeof(SVR_PATH);
    bind(fd, (struct sockaddr*)&server_addr, addrlen);

    clifd = socket(AF_UNIX,SOCK_DGRAM,0);
    struct sockaddr_un client_addr;
    client_addr.sun_family = AF_UNIX;
    client_addr.sun_path[0]=0;
    strcpy(client_addr.sun_path + 1,CLI_PATH);
    // 注意计算长度
    socklen_t addrlen_ = sizeof(client_addr.sun_family) + sizeof(CLI_PATH);
    bind(clifd, (struct sockaddr*)&client_addr, addrlen_);


    return 0;
}
