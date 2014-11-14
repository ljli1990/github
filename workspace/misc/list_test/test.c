#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/sem.h>

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



static __init int test_init(void)
{
	printk(KERN_DEBUG "Hello,test!\n");
	
    struct task_struct *pos;
    struct list_head *current_head;
    int count=0;

    printk("Traversal module is working..\n");
    current_head=&(current->tasks);
    list_for_each_entry(pos,current_head,tasks)
    {
           count++;
         printk("[process %d]: %s\'s pid is %d\n",count,pos->comm,pos->pid);
    }
    printk(KERN_ALERT"The number of process is:%d\n",count);

	return 0;
}

static __exit void test_exit(void)
{
	printk(KERN_DEBUG "Bye, test!\n");
}

//EXPORT_SYMBOL (symbol);
//EXPORT_SYMBOL_GPL (symbol);
//

module_init(test_init);
module_exit(test_exit);

