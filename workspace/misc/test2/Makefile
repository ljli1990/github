# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.

#module name
#OBJ = TEMPLATE


PWD?=$(shell PWD)

#auto get the module name by dir
OBJ?=$(notdir $(PWD))
#$(info "OJB = "$(OBJ))
C_SOURCES = $(shell find $(PWD) -name "*.c")
C_FILES = $(notdir $(C_SOURCES))
C_OBJECTS = $(patsubst %.c, %.o, $(C_FILES))
#S_SOURCES = $(shell find . -name "*.s")
#S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

# module execute objs
#$(OBJ)-objs = $(OBJ) 

#multi files
obj-m := $(OBJ).o
module-objs := $(C_OBJECTS)


ifneq ($(KERNELRELEASE),)
	obj-m :=  $(C_OBJECTS) 
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
install:
	sudo insmod $(OBJ).ko
uninstall:
	sudo rmmod $(OBJ)
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
check:
	@sudo lsmod |grep $(OBJ) ||echo no module $(OBJ)
endif

