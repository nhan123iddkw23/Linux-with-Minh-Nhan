#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>

#define DRIVER_AUTHOR "hoangminhnhan203@gmail.com Hoang Minh Nhan"
#define DRIEVR_DESCRIPTION "Pin control"
#define DRIVER_VERSION "1.0"
#define DRIVER_LICENSE "GPL"

#define LOW 0
#define HIGH 1
static struct gpio_desc *gpio1_16;

static const struct of_device_id gpio_dt_ids[] = {
    {.compatible = "gpio_description_base", },
    {                            }
};

static int led_probe(struct platform_device *pdev){
    struct device *dev = &pdev->dev;
    gpio1_16 = gpiod_get(dev,"led",GPIOD_OUT_LOW);
    gpiod_set_value(gpio1_16,HIGH);
    pr_info("Hello, LED 16 HIGH\n");
    pinctrl_get_select(dev,"default");
    return 0;
}

static int led_remove(struct platform_device *pdev){
     gpiod_set_value(gpio1_16,LOW);
    gpiod_put(gpio1_16);
    pr_info("Goodbye, LED 16 LOW\n");
    pinctrl_get_select(dev,"sleep");
    return 0;
}


static struct platform_driver my_led = {
    .probe = led_probe,
    .remove = led_remove,
    .driver = {
        .name = "gpio_description_base",
        .of_match_table = of_match_ptr(gpio_dt_ids),
        .owner = THIS_MODULE,
    },
};

module_platform_driver(my_led);

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_DESCRIPTION(DRIEVR_DESCRIPTION);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_VERSION(DRIVER_VERSION);

