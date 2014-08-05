#include <linux/module.h>  
#include <linux/init.h>  
#include <linux/kernel.h>   
#include <linux/mm.h>  
#include <linux/errno.h>  
#include <linux/slab.h>  
#include <linux/gfp.h>  
  
struct slab_test{  
    int val;  
};  
  
static int n;  
struct kmem_cache *test_cachep = NULL;  
struct slab_test *object1 = NULL, *object2 = NULL;  
  
void slab_ctor(void *cachep){  
    printk("slab_ctor is called! object %d has been inited!\n", n);  
    n++;  
}  
  
  
static int __init slab_test_init(void){  
    printk("slab test module init\n");  
    n = 0;  
    test_cachep = kmem_cache_create("slab_test_cachep", sizeof(struct slab_test), 0, SLAB_HWCACHE_ALIGN, slab_ctor);  
    if(!test_cachep)  
        return -ENOMEM;  
	printk("before object1 kmem_cache_alloc...\n");
    object1 = kmem_cache_alloc(test_cachep, GFP_KERNEL);  
    if(!object1)  
        return -ENOMEM;  
    else  
        printk("object one has been created!\n");  
    object2 = kmem_cache_alloc(test_cachep, GFP_KERNEL);  
    if(!object2)  
        return -ENOMEM;  
    else  
        printk("object two has been created!\n");  
    return 0;  
}  
  
static void __exit slab_test_exit(void){  
    printk("slab test module exit\n");  
    kmem_cache_free(test_cachep, object1);  
    kmem_cache_free(test_cachep, object2);  
    if(test_cachep)  
        kmem_cache_destroy(test_cachep);  
}  
  
module_init(slab_test_init);  
module_exit(slab_test_exit);  
MODULE_LICENSE("GPL");  
MODULE_AUTHOR("embeddedlwp@163.com");  
MODULE_DESCRIPTION("slab test module"); 
