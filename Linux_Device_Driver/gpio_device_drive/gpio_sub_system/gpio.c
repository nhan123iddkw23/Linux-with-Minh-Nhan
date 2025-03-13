#include <linux/module.h>
#include <linux/gpio.h>

#define GPIO0_30 30
#define LOW 0
#define HIGH 1

#define AUTHOR "Hoang Minh Nhan hoangminhnhan203@gmail.com"
#define DES    "Gpio subsystem"

static int __init init_t(void){
    gpio_request(GPIO0_30,"gpio_30");
    gpio_direction_output(GPIO0_30, LOW);
    gpio_set_value(GPIO0_30,HIGH);
    pr_info("Hello! gpio status: %d!\n", gpio_get_value(GPIO0_30));
    return 0;
}


static void __exit exit_t(void){
    gpio_set_value(GPIO0_30,LOW);
    gpio_free(GPIO0_30);
    pr_info("Good bye my fen !!!\n");
}


module_init(init_t);
module_exit(exit_t);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DES); 
MODULE_VERSION("1.0"); 