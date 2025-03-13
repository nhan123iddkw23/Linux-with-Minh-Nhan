#include "linux/module.h"  // define module_init() and module_exit()
#include "linux/fs.h"      // define alloc_chrdev_region(), registor_chrdev_region()

#define DRIVE_AUTHOR "Minh Nhan hoangminhnhan203@gmail.com"
#define DRIVE_DESC "Hello kernel module"
#define DRIVE_VER "1.0"

struct m_dev_foo{
    dev_t dev_num;
}mdev;

/* Init */
static int __init init_dev(void){
    if(alloc_chrdev_region(&mdev.dev_num,0,1,"m_cdev") < 0){
        pr_err("Failded to alloc chrdev region\n");
        return -1;
    }
    pr_info("Major = %d Minor = %d\n",MAJOR(mdev.dev_num),MINOR(mdev.dev_num));
    pr_info("Hello world kernel module\n");
    return 0;
}


static void __exit exit_dev(void){
    unregister_chrdev_region(mdev.dev_num,1);
    pr_info("Goodbye\n");
}


module_init(init_dev);
module_exit(exit_dev);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVE_AUTHOR);
MODULE_DESCRIPTION(DRIVE_DESC);
MODULE_VERSION(DRIVE_VER);




