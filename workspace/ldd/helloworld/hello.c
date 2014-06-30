#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ming");
MODULE_DESCRIPTION("For my task 01 of the Eudyptula Challenge");

static __init int hellomod_init(void)
{
	printk(KERN_DEBUG "Hello,i'm task 01!\n");

	return 0;
}

static __exit void hellomod_exit(void)
{
	printk(KERN_DEBUG "Goodbye, i'm task 01!\n");
}

module_init(hellomod_init);
module_exit(hellomod_exit);

