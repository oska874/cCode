#include <linux/module.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/time.h>
#include <asm/io.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
/* 必要的头文件*/




#define MEM_MAJ 234
#define MEM_MIN 97

#define MEM1_NAME   "mem5"

typedef struct mem_dev {
    struct cdev cdev;
    void *private;
} mem_dev_t;



mem_dev_t mem1;
int mem1_maj=0;
int mem1_min=0;

struct class *mem1_class;
struct device *dev;
dev_t devno;


int mem1_open(struct inode* inode, struct file *filp)
{
    printk("enter mem1_open!\n");
    return 0;
}

int mem1_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
    printk("enter mem1_read!\n");
    return 0;
}

int mem1_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
    printk("enter mem1_write!\n");
    return 0;
}

int mem1_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long data)
{
    printk("enter mem1_ioctl!\n");
    return 0;
}

int mem1_release(struct inode *inode, struct file *filp)
{
    printk("enter mem1_release!\n");
    return 0;
}

struct file_operations mem1_fops = {
    .owner = THIS_MODULE,
    .open = mem1_open,
    .read = mem1_read,
    .write = mem1_write,
    .unlocked_ioctl = mem1_ioctl,
    .release = mem1_release,
};

static int __init mem1_init( void )
{
    printk("<3>Hello,World! from the kernel space…\n");
    int ret=-1;



    if(mem1_maj) {
        devno = MKDEV(MEM_MAJ,MEM_MIN);
        ret = register_chrdev_region(devno,1,MEM1_NAME);
    } else {
        ret = alloc_chrdev_region(&devno,0,1,MEM1_NAME);
        printk("devno %d %d %d\n",devno,MAJOR(devno),MINOR(devno));
    }

    if(ret <0) {
        printk("reg chrdev fail\n");
        goto reg_err;
    }

    mem1_maj = MAJOR(devno);
    cdev_init(&mem1.cdev,&mem1_fops);
//    mem1.cdev.owner = THIS_MODULE;


    ret = cdev_add(&mem1.cdev,devno,1);
    if (ret) {
        printk("cdev add fail\b");
        goto ca_err;
    }

    mem1_class = class_create(THIS_MODULE,MEM1_NAME);
    if(IS_ERR(mem1_class)) {
        printk("class create fail\n");
        goto cls_err;
    }

    dev = device_create(mem1_class,NULL,devno,NULL,MEM1_NAME);
    if(IS_ERR(dev)) {
        printk("dev create fail\n");
        goto dc_err;
    }
    printk("init done\n");
    return 0;
dc_err:

cls_err:

ca_err:

reg_err:

    return ret;

}

static void __exit mem1_cleanup(void )
{
    printk("<2>Goodbye, World! leaving kernel space…\n");
    device_destroy(mem1_class,devno);
    class_destroy(mem1_class);
    cdev_del(&mem1.cdev);
    unregister_chrdev_region(devno,1);
}
module_init(mem1_init);
module_exit(mem1_cleanup);
MODULE_LICENSE("GPL");
