#ifndef __LED_MODULE_H__
#define __LED_MODULE_H__

#define GPIO0_ADDR_BASE     0x4804C000
#define GPIO0_ADDR_END      0x4804CFFF
#define GPIO0_ADDR_SIZE     (GPIO0_ADDR_END - GPIO0_ADDR_BASE)

#define GPIO_OE_OFFSET			    0x134
#define GPIO_CLEARDATAOUT_OFFSET	0x190
#define GPIO_SETDATAOUT_OFFSET		0x194

#define GPIO0_30                    (1 << 17)       /* P9_11 */

#endif  /* __LED_MODULE_H__ */