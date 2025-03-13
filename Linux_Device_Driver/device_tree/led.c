#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>

#define DRIVER_AUTHOR "hoangminhnhan203@gmail.com Hoang Minh Nhan"
#define DRIEVR_DESCRIPTION "Device tree"
#define DRIVER_VERSION "1.0"
#define DRIVER_LICENSE "GPL"

static struct gpio_desc *LED;

static const struct of_device_id gpio_dt_ids[] = {
    {.compatible = "bbb-led,dt", },
    {                            }
};

static int led_probe(struct platform_device *pdev){
    struct device *dev = &pdev->dev;
    LED = gpiod_get(dev,"mled",GPIOD_OUT_HIGH);
    pr_info("Hello, LED 31 HIGH\n");
    return 0;
}

static int led_remove(struct platform_device *pdev){
    gpiod_put(LED);
    pr_info("Goodbye, LED 32 LOW\n");
    return 0;
}


static struct platform_driver my_led = {
    .probe = led_probe,
    .remove = led_remove,
    .driver = {
        .name = "bbb-led,dt_sample",
        .of_match_table = of_match_ptr(gpio_dt_ids),
        .owner = THIS_MODULE,
    },
};

module_platform_driver(my_led);

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_DESCRIPTION(DRIEVR_DESCRIPTION);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_VERSION(DRIVER_VERSION);

