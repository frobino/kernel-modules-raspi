#include <linux/module.h>
#include <linux/kernel.h>

/*
* Module init function
*/
static int __init basicmod_init(void)
{
printk(KERN_INFO "%s\n", __func__);

/*
* A non 0 return means init_module failed; module can't be loaded.
*/
return 0;
}

/*
* Module exit function
*/
static void __exit basicmod_exit(void)
{
printk(KERN_INFO "%s\n", __func__);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Francesco Robino");
MODULE_DESCRIPTION("Basic Linux Kernel module");

module_init(basicmod_init);
module_exit(basicmod_exit);