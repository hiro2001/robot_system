//SPDX-License-Identifier:GPL-3.0
/*
*Copyright(c)2021 Ryuich Ueda. All rights reserved.
*Copyright(c)2021 Hiroyuki Matsuda. All rights reserved.
*/


#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Ryuichi Ueda and Hiroyuki Matsuda");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;

static volatile u32 *gpio_base = NULL;


static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	char c;
	if(copy_from_user(&c,buf,sizeof(char)))
		return -EFAULT;
  printk(KERN_INFO "receive %c\n", c);


	if(c == '0')
		gpio_base[10] = 1 << 25;
	else if(c == '1')
		gpio_base[7] = 1 << 25;
  return 1;
}

static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t* pos){
  int size = 0;
  char sushi[] = {0xF0, 0x9F, 0x8D, 0xA3, 0x0A, 0x20, 0x4C, 0x4F, 0x56, 0x45};
  if(copy_to_user(buf+size, (const char *)sushi, sizeof(sushi))){
    printk(KERN_INFO "sushi : copy_to_user failed\n");
    return -EFAULT;
  }
  size += sizeof(sushi);
  return size;

}
static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
	.read = sushi_read
};

static int __init init_mod(void)
{
	int retval;
	retval =  alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}
	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	cdv.owner = THIS_MODULE;
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d\n",MAJOR(dev),MINOR(dev));
		return retval;
	}

	cls = class_create(THIS_MODULE,"myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.\n");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));

  gpio_base = ioremap_nocache(0xfe200000, 0xA0);
  
	const u32 one = 25;
	const u32 index1 = one/10;//GPFSEL2
	const u32 shift1 = (one%10)*3;//15bit
	const u32 mask1 = ~(0x7 << shift1);//11111111111111000111111111111111
	gpio_base[index1] = (gpio_base[index1] & mask1) | (0x1 << shift1);//001: output flag
	const u32 two = 24;
	const u32 index2 = two/10;//GPFSEL2
	const u32 shift2 = (two%10)*3;//15bit
	const u32 mask2 = ~(0x7 << shift2);//11111111111111000111111111111111
	gpio_base[index2] = (gpio_base[index2] & mask2) | (0x1 << shift2);//001: output flag
	const u32 two = 24;
	const u32 index3 = three/10;//GPFSEL2
	const u32 shift3 = (three%10)*3;//15bit
	const u32 mask3 = ~(0x7 << shift3);//11111111111111000111111111111111
	gpio_base[index3] = (gpio_base[index3] & mask3) | (0x1 << shift3);//001: output flag
	
	return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
	iounmap(gpio_base);
}

module_init(init_mod);
module_exit(cleanup_mod);
