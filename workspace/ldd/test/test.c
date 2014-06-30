#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <asm/current.h>
MODULE_LICENSE("Dual BSD/GPL");

static char *whom = "world";
static int howmany = 1;

module_param(whom, charp, S_IRUGO);
module_param(howmany, int, S_IRUGO);

static int arr[3] = {0}; 
static int arr_len = 3;
module_param_array(arr, int, &arr_len, S_IRUGO);

static __init int test_init(void)
{
	int i = 0;
	//struct task_struct *current_task = NULL;

	printk(KERN_DEBUG "hello,test!\n");
	

	//printK(KERN_DEBUG "UTS_RELEASE = %s\n",UTS_RELEASE);





	printk(KERN_DEBUG "%s %d\n", whom, howmany);
	for(i = 0; i < 3; i++) 
	{
		printk(KERN_DEBUG "arr[%d]=%d\n",i,arr[i]);
	}

	printk(KERN_DEBUG "sizeof task_struct = %ld",sizeof(struct task_struct));

	printk(KERN_DEBUG "cur pid = %d , %s",current->pid,current->comm);
	
	return 0;
}

static __exit void test_exit(void)
{
	printk(KERN_DEBUG "Goodbye, test\n");
}

module_init(test_init);
module_exit(test_exit);

