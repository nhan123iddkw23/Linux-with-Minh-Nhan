# Gpio Driver Legacy
BBB_KERNEL := /home/nhan_pro/bbb/kernelbuildscripts/KERNEL
TOOLCHAIN := /home/nhan_pro/bbb/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

EXTRA_CFLAGS=-Wall
obj-m := main.o

all:
	make ARCH=arm CROSS_COMPILE=$(TOOLCHAIN) -C $(BBB_KERNEL) M=$(shell pwd) modules
	
clean:
	make -C $(BBB_KERNEL) M=$(shell pwd) clean