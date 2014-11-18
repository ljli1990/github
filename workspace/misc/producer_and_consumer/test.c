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

#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/delay.h>


#define PNUM 	10
#define CNUM 	30
#define N  		3
#define BUF_NUM 8
struct semaphore mutex;
struct semaphore s1, s2;

int thread_id[N] = {0};
int buf[BUF_NUM] = {0};
int in, out, cflag;

static int consumer_thread(void *p);
static int productor_thread(void *p);
#define init_MUTEX(p) sema_init(p, 1)


static __init int test_init(void)
{
	int i;

	printk(KERN_ERR "Hello,test!\n");
	
	printk(KERN_ERR "np_nc module is working..\n");

	in=out=0;
	cflag=0;
	init_MUTEX(&mutex);
	sema_init(&s1,BUF_NUM);
	sema_init(&s2,0);
	
	printk(KERN_ERR "s1.count=%d,s2.count=%d\n",s1.count,s2.count);	

	for(i=0;i< N;i++)
	{
		thread_id[i]=i+1;
		kernel_thread(productor_thread,&(thread_id[i]),CLONE_KERNEL);
		kernel_thread(consumer_thread,&(thread_id[i]),CLONE_KERNEL);
	}
	
	return 0;
}
static int productor_thread(void *p)
{
	int i=*(int *)p;
	int p_num=PNUM;

	while(p_num)
	{
		if((s1.count)<=0)
		{
			printk(KERN_ERR "[producer %d,%d]:I will be waiting for producting..\n",i,s1.count);
		}
		
		down(&s1);
	    down(&mutex);
        
		buf[in]=i*100+(PNUM-p_num+1);
        
		printk(KERN_ERR "[producer %d,%d]:I producted a goods \"%d\" to buf[%d]..\n",i,s1.count,buf[in],in);
        
		in=(in+1)%BUF_NUM;
        
		up(&mutex);
        up(&s2);
		
		p_num--;
	}
	return 0;
}
static int consumer_thread(void *p)
{
	int i=*(int *)p;
	int goods;

	while(cflag!=CNUM)
	{
		if((s2.count)<=0)
		{
			printk(KERN_ERR "[consumer %d,%d]:I will be waiting for goods..\n",i,s2.count);
		}
	    down(&s2);
        down(&mutex);

        goods=buf[out];
        printk(KERN_ERR "[consumer %d,%d]:I consumed a goods \"%d\" from buf[%d]..\n",i,s2.count,goods,(out%BUF_NUM));
        out=(out+1)%BUF_NUM;
            
		up(&mutex);
		up(&s1);
		
		cflag++;
		udelay(1000);
	}
	return 0;
}

static __exit void test_exit(void)
{
	printk(KERN_ERR "Bye, test!\n");
}

//EXPORT_SYMBOL (symbol);
//EXPORT_SYMBOL_GPL (symbol);
//

module_init(test_init);
module_exit(test_exit);

