.SILENT:
bin_name = GPIO_driver1_0_0
obj-m +=$(bin_name).o

all:
	mkdir -p build
	rm -rf build/*
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	mv ${bin_name}.ko build
	rm -rf .${bin_name}* ${bin_name}.mod* ${bin_name}.o  modules.order Module.symvers

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


load:
	insmod build/${bin_name}.ko
	dmesg | tail
# 	create device node manually
	mknod /dev/GPIO_koya c 511 0
	chmod 666 /dev/GPIO_koya
	echo "---------------------------------------------------------------------------------"
	ls -la /dev/GPIO_koya*
	echo "---------------------------------------------------------------------------------"
unload:
	rmmod ${bin_name}
	rm -rf /dev/GPIO_koya

msg:
	dmesg | tail

