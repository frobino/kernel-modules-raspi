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