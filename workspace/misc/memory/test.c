#include <linux/init.h>
#include <linux/module.h>


MODULE_AUTHOR("ming.li");
//MODULE_DESCRIPTION(description);
//MODULE_VERSION(version_string);
//MODULE_DEVICE_TABLE(table_info);
//MODULE_ALIAS(alternate_name);

MODULE_LICENSE("Dual BSD/GPL");

//#include <linux/moduleparam.h>
//module_param(variable, type, perm);
//module_param_array(name, type, nump, perm)

//#include <linux/sched.h>
//struct task_struct *current;
//current->pid
//current->comm

#include <linux/gfp.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

static unsigned long pagemem = 0;
static void * kmallocmem = NULL;
//kmem_cache_t 
static void * vmallocmem = NULL;
static struct page * page = NULL;

static __init int test_init(void)
{

	printk(KERN_DEBUG "Hello,test!\n");
	printk("mmshow module is working\n");

	pagemem = __get_free_page(GFP_KERNEL);
	if(!pagemem)
		goto gfp_fail;
	printk(KERN_INFO "pagemem = 0x%lx\n",pagemem);

	kmallocmem = kmalloc(100 * sizeof(char),GFP_KERNEL);
	if(!kmallocmem)
		goto kmalloc_fail;
	printk(KERN_INFO "kmallocmem = 0x%p\n",kmallocmem);

	vmallocmem = vmalloc(1000000 * sizeof(char));
	if(!vmallocmem)
		goto vmalloc_fail;
	printk(KERN_INFO "vmallocmem = 0x%p\n",vmallocmem);

	page = alloc_page(GFP_KERNEL);
	if (!page)
	{
		goto page_fail;
	}
	printk(KERN_INFO "page = 0x%p\n",page);


	return 0;

gfp_fail:
	free_page(pagemem);
kmalloc_fail:
	kfree(kmallocmem);
vmalloc_fail:
	vfree(vmallocmem);
page_fail:
  __free_page(page);
	
	return 0;
}

static __exit void test_exit(void)
{
	printk(KERN_DEBUG "Bye, test!\n");
	if (pagemem)
	{
		free_page(pagemem);
		pagemem = 0;
	}
	if (kmallocmem)
	{
		kfree(kmallocmem);
		kmallocmem = NULL;
	}
	if (vmallocmem)
	{
		vfree(vmallocmem);
		vmallocmem = NULL;
	}
}

//EXPORT_SYMBOL (symbol);
//EXPORT_SYMBOL_GPL (symbol);
//

module_init(test_init);
module_exit(test_exit);

