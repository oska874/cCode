#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/mii.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <netinet/in.h>
#include <unistd.h>

#define checkret(ret) \
    if(ret < 0) {     \
        printf("%m! \"%s\" : line: %d\n", __func__, __LINE__);    \
        goto err_;    \
    }

#define help() \
    printf("gcc mdio.c -o mdio\n");\
    printf("read all : mdio\n");\
    printf("read : mdio reg_addr\n");\
    printf("write : mdio reg_addr value\n");\
    return -1;

/*
 * 详细的ioctl 选项参见 kernel/include/uapi/linux/sockios.h 定义
 */
int sockfd;

int main(int argc, char *argv[])
{
    struct mii_ioctl_data *mii = NULL;
    struct ifreq ifr;
    int ret;
    int16_t i;

    if(argc < 2 || !strcmp(argv[1], "-h")) {
        help();
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, argv[1], IFNAMSIZ - 1);
    sockfd = socket(PF_LOCAL, SOCK_DGRAM, 0);
    checkret(sockfd);
    ret = ioctl(sockfd, SIOCGMIIPHY, &ifr);
    checkret(ret);
    
    mii = (struct mii_ioctl_data*)&ifr.ifr_data;
    switch(argc){
        case 2:
            printf("read all phy reg\n");
            for(i=0;i<32;i++){
                mii->reg_num = i;
                ret = ioctl(sockfd, SIOCGMIIREG, &ifr);
                checkret(ret);
                printf("phy_id : 0x%x reg: 0x%x value : 0x%x\n", mii->phy_id, mii->reg_num, mii->val_out);
            }
            break;
        case 3:
            printf("read one reg\n");
            mii->reg_num = (uint16_t)strtoul(argv[2], NULL, 0);
            ret = ioctl(sockfd, SIOCGMIIREG, &ifr);
            checkret(ret);
            printf("phy_id : 0x%x reg: 0x%x value : 0x%x\n\n", mii->phy_id, mii->reg_num, mii->val_out);
            break;
        case 4:
            printf("write one reg\n");
            mii->reg_num = (uint16_t)strtoul(argv[2], NULL, 0);
            mii->val_in = (uint16_t)strtoul(argv[3], NULL, 0);
            ret = ioctl(sockfd, SIOCSMIIREG, &ifr);
            checkret(ret);
            printf("phy_id : 0x%x reg: 0x%x value : 0x%x\n\n", mii->phy_id, mii->reg_num, mii->val_in);
            mii->reg_num = (uint16_t)strtoul(argv[2], NULL, 0);
            ret = ioctl(sockfd, SIOCGMIIREG, &ifr);
            checkret(ret);
            printf("read phy_id : 0x%x reg: 0x%x value : 0x%x\n\n", mii->phy_id, mii->reg_num, mii->val_out);
            break;
        default:
            help();
            break;
    }
err_:
    close(sockfd);
    return 0;
}
