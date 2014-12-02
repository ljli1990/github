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

#include <linux/time.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/types.h>
#include <linux/semaphore.h>
#include <linux/string.h>
/*
 * a test module with proc entry ,dev ,and work thread
 *
 *
 */

#include <linux/proc_fs.h>


static struct proc_dir_entry *test = NULL;
static const char *proc_entry_name = "test";
static mode_t proc_mod = 0666;
static char * proc_buf = NULL;
static const char *MODULE_TAG = "MING_TEST";
static struct semaphore sem;

static char tmp[4096] = {0};
static const char *CMD_EXIT = "EXIT";
#define PROC_BUF_SIZE 2048

static int proc_open (struct inode * inode, struct file * file)
{
	printk (KERN_DEBUG "[%s] [%s] ...",MODULE_TAG,__FUNCTION__);

	return 0;
}

static int proc_release (struct inode * inode, struct file * file)
{
	printk (KERN_DEBUG "[%s] [%s] ...",MODULE_TAG,__FUNCTION__);

	return 0;
}
static ssize_t proc_read (struct file * file, char __user * buf, size_t size, loff_t * foff)
{
	struct timeval tv = {0};
	int count = 0;

	printk (KERN_DEBUG "[%s] [%s] ...",MODULE_TAG,__FUNCTION__);

	down(&sem);

	//use strncmp to avoid echo newline 
	//also you can use echo -n EXIT to avoid this 
	if (!strncmp(CMD_EXIT,proc_buf,strlen(CMD_EXIT)))
	{
		printk(KERN_DEBUG "CMD = %s, will goto exit",proc_buf);
		goto EXIT;
	}

	do_gettimeofday(&tv);

	count = sprintf(tmp,"[%ld.%ld] %s",tv.tv_sec, tv.tv_usec,proc_buf);

	if (copy_to_user(buf,tmp,count))
	{
		return -EFAULT;
	}
	*foff = count;

EXIT:
	return count;
}
static ssize_t proc_write (struct file *file, const char __user *buf, size_t size, loff_t *foff)
{
	printk (KERN_DEBUG "[%s] [%s] ...",MODULE_TAG,__FUNCTION__);

	if (copy_from_user(proc_buf,buf,size))
	{
		return -EFAULT;
	}
	
	proc_buf[size] = '\0';
	*foff = size;
	up(&sem);

	return size;
}

static struct file_operations proc_fops = {
	.owner = THIS_MODULE,
	.open = proc_open,
	.read = proc_read,
	.write = proc_write,
	.llseek = NULL,
	.release = proc_release

};


static void proc_init(void)
{
	test = create_proc_entry(proc_entry_name, proc_mod, NULL);
	
	if (test)
	{
		test->proc_fops = &proc_fops;
		test->data = NULL;
	}

	proc_buf = kmalloc(PROC_BUF_SIZE,GFP_KERNEL);

	printk (KERN_DEBUG "proc_buf = %p \n", proc_buf);

}
static void proc_del(void)
{
	remove_proc_entry(proc_entry_name, NULL);
	kfree(proc_buf);
}
static void dev_init(void)
{


}

static void thread_init(void)
{

}


static __init int test_init(void)
{
	printk(KERN_DEBUG "Hello,test!\n");

	sema_init(&sem,0);
	proc_init();
	
	return 0;
}

static __exit void test_exit(void)
{
	printk(KERN_DEBUG "Bye, test!\n");
	proc_del();
}

//EXPORT_SYMBOL (symbol);
//EXPORT_SYMBOL_GPL (symbol);
//

module_init(test_init);
module_exit(test_exit);

