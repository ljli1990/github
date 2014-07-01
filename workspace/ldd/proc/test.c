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
//
//

#include <linux/proc_fs.h>
#include <linux/printk.h>


static int read_count = 0;
static struct proc_dir_entry *root = NULL;

int read_proc_func(char *page, char **start, off_t off,int count, int *eof, void *data)
{
    printk(KERN_DEBUG "page = %p off = %ld, count = %d",page,off,count);	

    sprintf(page,"\ntest_read_proc_func %d, off = %ld, count = %d \n",read_count++,off,count);

	*eof = 1;

	return 0;
}

static __init int test_init(void)
{
	struct proc_dir_entry *parent = NULL,*node = NULL;

	printk(KERN_DEBUG "Hello,test!\n");

	
	parent = proc_mkdir("test_ming",NULL);
	root = parent;	
	node = create_proc_read_entry("test_proc", 0,parent,read_proc_func,NULL);
    
    printk(KERN_DEBUG "node->uid = %d",node->uid);

	return 0;
}

static __exit void test_exit(void)
{
	printk(KERN_DEBUG "Bye, test!\n");
	remove_proc_entry("test_proc",root);
	remove_proc_entry("test_ming",NULL);
}

//EXPORT_SYMBOL (symbol);
//EXPORT_SYMBOL_GPL (symbol);
//

module_init(test_init);
module_exit(test_exit);

