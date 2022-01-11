obj-m := myled.o

myled.ko: myled.c
	make -C /usr/src/linux-headers-`uname -r` M=`pwd` V=1 modules

hoge:
	mv myled.c hoge.c
	mv myled2.c myled.c
	mv hoge.c myled2.c

clean:
	make -C /usr/src/linux-headers-`uname -r` M=`pwd` V=1 clean
