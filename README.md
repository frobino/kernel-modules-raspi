kernel-modules-raspi
====================

Simple kernel modules for the raspberry pi.

To compile kernel modules it is necessary first to compile a kernel. 
In fact, kernel modules are compiled against a specific kernel version (which is supposed to be the one running on the RasPi)

So the step 1 is:

kernel compilation and installation on RasPi
====================

Howto build a new kernel for the Raspbian (or whatever distribution) already installed on the SD.
Basically I just cross compile a new kernel and I sobstitute it to the actual one running on the OS installed on the board.

http://elinux.org/RPi_Kernel_Compilation
http://mitchtech.net/raspberry-pi-kernel-compile/

Q:Why do we use a kernel for the raspberry instead of taking it from kernel.org (vanilla kernel)?
A:http://www.raspberrypi.org/phpBB3/viewtopic.php?f=71&t=11189

CREATE A COMPLETE NEW DISTRO WITH YOCTO:

http://www.pimpmypi.com/blog/blogPost.php?blogPostID=7

Now that we have compiled and installed a specific version of the kernel, we can move to step 2:

how to compile a kernel module
====================

http://stackoverflow.com/questions/20167411/how-to-compile-a-kernel-module-for-raspberry-pi

BASIC STEPS FOR OS FROM SCRATCH

http://rpidev.wordpress.com/

useful commands when debugging kernel modules
====================

dmesg | tail: show the last results of printk() from kernel modules

insmod <modulename>.ko

rmmod

create your own OS
====================

http://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/

very fun, very low level. This source does not explain how to mount/unmount device drivers, 
but it explains how to write the assembly and how to create from it a C function that can be 
used in the kernel modules we are develping! Try to mix this tutorial with the other LED ON/OFF 
with timer tutorial! Instead of using the provided kernel functions (timer, etc.) make your own! 
So we can make a comparison using linux provided gpio_set_value and jiffies timer.

Same things can be done in low level C:
http://www.valvers.com/embedded-linux/raspberry-pi/step01-bare-metal-programming-in-cpt1

However, we cannot insert these C functions directly in the kernel module.
We need to use ioremap:
http://www.raspberrypi.org/forums/viewtopic.php?f=44&t=8690&p=170701 
https://groups.google.com/forum/#!topic/beagleboard/rR8ww8fI3ms 
http://93.93.128.176/forums/viewtopic.php?t=22738&p=213886 
http://blogsmayan.blogspot.se/p/programming-interrupts-in-raspberry-pi.html

