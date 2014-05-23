#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/init.h>
// #include <linux/gpio.h>
// used by request_mem_region,...
#include <linux/ioport.h>
// used by ioremap,iounmap...
#include <asm/io.h>

#define LED1 16 

/** The base address of the GPIO peripheral (ARM Physical Address) */
//#define GPIO_BASE       0x20200000UL // Physical address
#define GPIO_BASE	0x7E200000UL
#define GPIO_GPCLR0     10
/** GPIO Register set */
//volatile unsigned int* gpio;
void __iomem *base;

static struct timer_list blink_timer;

/*
* Timer function called periodically
*/
static void blink_timer_func(unsigned long data)
{
printk(KERN_INFO "%s\n", __func__);

*(int *)((char *)base + GPIO_GPCLR0) = data;

/* schedule next execution */
blink_timer.data = !data;	// makes the LED toggle
blink_timer.expires = jiffies + (1*HZ); // 1 sec.
add_timer(&blink_timer);
}

/*
* Module init function
*/
static int __init gpiomod_init(void)
{
int ret = 0;

printk(KERN_INFO "%s\n", __func__);

//int j, tmp, val;
//void __iomem *base;
//volatile unsigned long *ptr;
  
if (!request_mem_region(GPIO_BASE, 1024, "gpio-test")) {
    printk(KERN_ERR "request_mem_region failed");
    ret = 1;
    return ret;
  }

base = ioremap(GPIO_BASE, 1024);
if (!base) {
    printk(KERN_ERR "ioremap failed");
    ret = 1;
    return ret;
  } 


/* init timer, add timer function */
init_timer(&blink_timer);

blink_timer.function = blink_timer_func;
blink_timer.data = 1L;	// initially turn LED on
blink_timer.expires = jiffies + (1*HZ); // 1 sec.
add_timer(&blink_timer);

return ret;
}

/*
* Module exit function
*/
static void __exit gpiomod_exit(void)
{
printk(KERN_INFO "%s\n", __func__);

// deactivate timer if running
del_timer_sync(&blink_timer);

// turn LED off
// gpio_set_value(LED1, 0);
// unregister GPIO
// gpio_free(LED1);

iounmap(base);
printk(KERN_INFO "iounmap completed");  
release_mem_region(GPIO_BASE, 1024);
printk(KERN_INFO "release_mem_region completed");

}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Francesco Robino");
MODULE_DESCRIPTION("Basic kernel module using a timer and GPIOs to flash the GREEN OK on-board LED.");

module_init(gpiomod_init);
module_exit(gpiomod_exit);