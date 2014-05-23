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
#define GPIO_BASE       0x20200000UL // Physical address
//#define GPIO_BASE	0x7E200000UL // Virtual address
/* From page 90 manual, gpioclr0 is at row 10, gpset0 row 7*/
#define GPIO_GPSET0	7
#define GPIO_GPCLR0     10
#define GPIO_GPFSEL1    1
/** GPIO Register set */

volatile unsigned int* gpio;
void __iomem *base;

static struct timer_list blink_timer;

/*
* Timer function called periodically
*/
static void blink_timer_func(unsigned long data)
{
printk(KERN_INFO "%s\n", __func__);

if (!data) {
  /* Set the GPIO16 (pin number 16) output low ( Turn OK LED on )*/
  gpio[GPIO_GPCLR0] = (1 << 16);
  }
else {
  /* Set the GPIO16 (pin number 16) output high ( Turn OK LED off )*/
  gpio[GPIO_GPSET0] = (1 << 16);
  }
  
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

// get the pointer to gpio
gpio = (volatile unsigned int *)base;  
// Now,we will be able to use the memory-mapped gpio register to configure the GPIO Pins as Input or Output.

/* Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
   peripheral register to enable GPIO16 as an output. 
   See page 90 manual,     
   bits 18 to 20 in the ‘GPIO Function Select 1′ (GPFSEL1) register control the GPIO16 pin.
*/
gpio[GPIO_GPFSEL1] |= (1 << 18);

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