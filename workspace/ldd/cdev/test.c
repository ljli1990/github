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
#include <linux/types.h> //dev_t
#include <linux/fs.h>  
#include <linux/cdev.h>

#include <linux/slab.h>

static dev_t dev = 0;
static struct cdev * mydev = NULL;
static char *buf = NULL;


int my_open(struct inode *inode, struct file *filp)
{
	dev_t i_rdev = inode->i_rdev;
	printk(KERN_DEBUG "my_open cdev = %p,major = %d minor = %d\n",imajor(inode),iminor(inode),inode->i_cdev);
	if (buf) 
	{
		
		printk(KERN_DEBUG "err buf is not NULL\n");
		return -1;
	}
	buf = kmalloc(2048,GFP_KERNEL);
	printk(KERN_DEBUG "buf = %x\n", buf);

	return 0;
}
int my_release(struct inode *inode, struct file *filp)
{
	dev_t i_rdev = inode->i_rdev;
	printk(KERN_DEBUG "my_open cdev = %p,major = %d minor = %d\n",imajor(inode),iminor(inode),inode->i_cdev);

	kfree(buf);
	buf = NULL;
	return 0;
}
int my_read()
{


}
struct file_operations my_opt = {
	.owner = THIS_MODULE;
	.open = my_open;
	.read = my_read;
	.write = my_Write; 
	.unlocked_ioctl = my_ioctl;
	.llseek = my_seek;
	.release = my_release;
}
static __init int test_init(void)
{
	int res = 0;

	printk(KERN_DEBUG "Hello,test!\n");

	//res = alloc_chrdev_region(&dev, 0, 1,"test_cdev");
	dev = MKDEV(248,0);
	res = register_chrdev_region(dev,1,"test_cdev");
	if (res < 0)
	{
		printk(KERN_DEBUG "err");	
		goto FAIL;
	}
	printk(KERN_DEBUG "major = %d minor = %d \n",MAJOR(dev),MINOR(dev));


	mydev = cdev_alloc();
	mydev->ops = &my_opt;
    mydev->owner = THIS_MODULE;	

	cdev->add(mydev, 0, 1);

FAIL:
	return 0;
}

static __exit void test_exit(void)
{
	printk(KERN_DEBUG "Bye, test!\n");
	cdev->del(mydev);
	unregister_chrdev_region(dev,1);
}

//EXPORT_SYMBOL (symbol);
//EXPORT_SYMBOL_GPL (symbol);
//

module_init(test_init);
module_exit(test_exit);

