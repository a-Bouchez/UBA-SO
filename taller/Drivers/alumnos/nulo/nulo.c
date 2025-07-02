#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

static ssize_t nulo_read(struct file *filp, char __user *data, size_t s, loff_t *off) {
  return 0; //como somos nulo, mentimos y decimos que leyeron s bytes de nosotros
}

static ssize_t nulo_write(struct file *filp, const char __user *data, size_t s, loff_t *off) {
  return s; //como somos nulo, mentimos y decimos que nos escribieron s bytes
}

static struct file_operations nulo_operaciones = {
  .owner = THIS_MODULE,
  .read = nulo_read,
  .write = nulo_write,
};

static struct cdev nulo_device;
static dev_t major;
static struct class *nulo_class;

static unsigned int count = 1;
static unsigned int minor = 0;
static char* DEVICE_NAME = "nulo";

static int __init nulo_init(void) {
  cdev_init(&nulo_device, &nulo_operaciones); //Asignar nulo_operaciones a las file operations correspondientes

  alloc_chrdev_region(&major, minor, count, DEVICE_NAME); //pedimos un major y count, y los guardamos en nuestras variable
  cdev_add(&nulo_device, major, count); //asignar el major y minor en cuestión a este dispositivo

  nulo_class = class_create(THIS_MODULE, DEVICE_NAME); //crear clase de dispositivo 
  device_create(nulo_class, NULL, major, NULL, DEVICE_NAME); //crear dHIS_MODispositivo

  return 0;
}

static void __exit nulo_exit(void) {
  unregister_chrdev_region(major, count); //notificamos al kernel que libere nuestro major y count al morir
  cdev_del(&nulo_device);

  device_destroy(nulo_class, major); //desregistrar el dispositivo
  class_destroy(nulo_class); //desregistrar la clase
}

module_init(nulo_init);
module_exit(nulo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de '/dev/null'");