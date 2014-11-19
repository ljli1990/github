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


#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/mm.h>

static void list_myvma(void)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;

	printk("list vma..\n");
        //print the current process's name and pid
	printk("current:%s pid:%d\n",current->comm,current->pid);

	down_read(&mm->mmap_sem);
	//vma is a linklist
	for(vma = mm->mmap; vma; vma = vma->vm_next)
	{
		//from the begining to the ending of a virtual memory area
		printk("0x%lx-0x%lx ",vma->vm_start,vma->vm_end);
		//check the flags of this VMA
		if(vma->vm_flags & VM_READ)
			printk("r");
		else
			printk("-");

		if(vma->vm_flags & VM_WRITE)
			printk("w");
		else
			printk("-");

		if(vma->vm_flags & VM_EXEC)
			printk("x");
		else
			printk("-");

		if(vma->vm_flags & VM_SHARED)
			printk("s");
		else
			printk("p");

	        printk("\n");

	}
	up_read(&mm->mmap_sem);
}


static __init int test_init(void)
{
	printk(KERN_DEBUG "Hello,test!\n");
	list_myvma();	

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

