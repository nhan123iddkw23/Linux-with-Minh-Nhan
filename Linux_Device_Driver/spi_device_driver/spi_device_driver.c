#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/spi/spi.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <asm/uaccess.h>

struct spi_device *stm32_spi;


char *data = "Hello Minh Nhan";

static int stm32_probe(struct spi_device *spi){
    pr_err("spiex: %s, %d\n", __func__, __LINE__);
    stm32_spi = spi;
    while(1){
        spi_write(stm32_spi,&data,sizeof(data));
        msleep(1000);  // Delay 100ms
    }
    return 0;
}


static int stm32_remove(struct spi_device *spi)
{
	pr_err("spiex: %s, %d\n", __func__, __LINE__);

	return 0;
}

struct of_device_id stm32_of_match[] = {
    { .compatible = "stm32_bbb"},
    {                           }

};


MODULE_DEVICE_TABLE(of,stm32_of_match);

static struct spi_driver my_spi_driver = {
    .probe = stm32_probe,
    .remove = stm32_remove,
    .driver = {
        .name = "stm32_bbb",
        .owner = THIS_MODULE,
        .of_match_table = stm32_of_match,
    },
};

module_spi_driver(my_spi_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hoangminhnhan203@gmail.com>");
MODULE_DESCRIPTION("SPI connect to STM32");
MODULE_VERSION("1.0");

