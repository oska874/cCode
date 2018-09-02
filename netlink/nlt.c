#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/netlink.h>
#include <net/netlink.h>
#include <net/net_namespace.h>
 
MODULE_AUTHOR("Yanchuan Nian");
MODULE_LICENSE("GPL");
 
#define NETLINK_NETLINKTEST 22
static struct sock *nltest_sock;
 
static int nltest_rcv_msg(struct sk_buff *skb, struct nlmsghdr *nlh, struct netlink_ext_ack *nea)
{
    char    *data;
 
    data = nlmsg_data(nlh);
    printk(KERN_INFO"Receive msg from userspace: %s\n", data);
 
    return 0;
}
 
static void nltest_rcv(struct sk_buff *skb)
{
    netlink_rcv_skb(skb, &nltest_rcv_msg);
}
 
static int __init netlinktest_init(void)
{
    struct netlink_kernel_cfg cfg = {
        .input  = nltest_rcv,
    };
 
    nltest_sock = netlink_kernel_create(&init_net, NETLINK_NETLINKTEST, &cfg);
    if (!nltest_sock)
        return -ENOMEM;
    printk(KERN_INFO"Enter netlink test module.\n");
    return 0;
}
 
static void __exit netlinktest_exit(void)
{
    printk(KERN_INFO"Leave netlink test module.\n");
    netlink_kernel_release(nltest_sock);
}
 
module_init(netlinktest_init);
module_exit(netlinktest_exit);

