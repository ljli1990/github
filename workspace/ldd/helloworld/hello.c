#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hellomod_init(void)
{
	printk(KERN_ALERT "hello,world!\n");

	return 0;
}

static void hellomod_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hellomod_init);
module_exit(hellomod_exit);

