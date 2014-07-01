# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.

# module name
OBJ = TEMPLATE

# module execute objs
$(OBJ)-objs = test.o 

ifneq ($(KERNELRELEASE),)
	obj-m := $(OBJ).o
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
install:
	sudo insmod $(OBJ).ko
uninstall:
	sudo rmmod $(OBJ)
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
endif

#multi files
#obj-m := module.o
#module-objs := file1.o file2.o
#
