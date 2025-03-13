#include "linux/module.h"  // define module_init() and module_exit()
#include "linux/fs.h"      // define alloc_chrdev_region(), registor_chrdev_region()
#include "linux/device.h"        // define device_create(), class_create()
#include "linux/cdev.h"     /* Define cdev_init(), cdev_add() */

#define DRIVE_AUTHOR "Minh Nhan hoangminhnhan203@gmail.com"
#define DRIVE_DESC "Hello kernel module"
#define DRIVE_VER "1.0"

struct m_dev_foo{
    dev_t dev_num;
    struct class *m_class;
    struct cdev m_cdev;
}mdev;



/*  Function Prototypes */
static int      __init init_dev(void);
static void     __exit exit_dev(void);
static int      m_open(struct inode *inode, struct file *file);
static int      m_release(struct inode *inode, struct file *file);
static ssize_t  m_read(struct file *filp, char __user *user_buf, size_t size,loff_t * offset);
static ssize_t  m_write(struct file *filp, const char *user_buf, size_t size, loff_t * offset);

static struct file_operations fops =
{
    .owner      = THIS_MODULE,
    .read       = m_read,
    .write      = m_write,
    .open       = m_open,
    .release    = m_release,
};


static int      m_open(struct inode *inode, struct file *file){
    pr_info("Open file\n");
    return 0;
}


static int      m_release(struct inode *inode, struct file *file){
    pr_info("Close file\n");
    return 0;
}

static ssize_t  m_read(struct file *filp, char __user *user_buf, size_t size,loff_t * offset){
    pr_info("Read file\n");
    return size;
}

static ssize_t  m_write(struct file *filp, const char *user_buf, size_t size, loff_t * offset){
    pr_info("Write file\n");
    return size;
}


/* Init */
static int __init init_dev(void){
    if(alloc_chrdev_region(&mdev.dev_num,0,1,"m_cdev") < 0){
        pr_err("Failded to alloc chrdev region\n");
        return -1;
    }
    pr_info("Major = %d Minor = %d\n",MAJOR(mdev.dev_num),MINOR(mdev.dev_num));

    if((mdev.m_class = class_create(THIS_MODULE,"m_class")) == NULL){
        pr_err("Cannot create the struct class for my device\n");
        goto class;
    }

    if(device_create(mdev.m_class,NULL,mdev.dev_num,NULL,"my_device") == NULL){
        pr_err("Cannot create device for my device\n");
        goto device;
    }

    cdev_init(&mdev.m_cdev,&fops);
    if(cdev_add(&mdev.m_cdev,mdev.dev_num,1) < 0){
        pr_err("Cannot add device for my system\n");
        goto add_device;
    }
    pr_info("Hello world kernel module\n");
    return 0;
add_device:
    device_destroy(mdev.m_class,mdev.dev_num);
class:
    class_destroy(mdev.m_class);
device:
    unregister_chrdev_region(mdev.dev_num, 1);
    return -1;
}


static void __exit exit_dev(void){
    cdev_del(&mdev.m_cdev);
    device_destroy(mdev.m_class, mdev.dev_num);             /* 3.0 */
    class_destroy(mdev.m_class);                            /* 2.0 */
    unregister_chrdev_region(mdev.dev_num,1);
    pr_info("Goodbye\n");
}


module_init(init_dev);
module_exit(exit_dev);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVE_AUTHOR);
MODULE_DESCRIPTION(DRIVE_DESC);
MODULE_VERSION(DRIVE_VER);