obj-m += rpi-pwm.o

all:
	make ARCH=arm CROSS_COMPILE=${CCPREFIX} -C /home/osso/isomount/Linux_tools/raspberry/kernel/linux M=$(PWD) modules

clean:
	make -C /home/osso/isomount/Linux_tools/raspberry/kernel/linux M=$(PWD) clean
	
