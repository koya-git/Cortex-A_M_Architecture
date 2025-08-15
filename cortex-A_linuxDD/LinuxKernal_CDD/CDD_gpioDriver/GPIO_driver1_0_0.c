#include <linux/module.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/string.h>
#include <linux/uaccess.h>

#define RES(name)  volatile uint32_t name

static int MAJOR_NUMBER;
typedef struct { 
    volatile uint32_t BANK[6];
    RES(res1);
    volatile uint32_t SET[2];
    RES(res2);
    volatile uint32_t CLEAR[2];
    RES(res3);
    volatile uint32_t LVL[2];
    RES(res4);
}GPIO_REGt;
GPIO_REGt* GPIOx = NULL;
static char buffer[1024];
static int buffer_len;
int GPIO_BANK_OPEN(struct inode * _1, struct file * _2){
    GPIOx = (GPIO_REGt*) ioremap(0x3f200000,sizeof(GPIO_REGt));
    if(GPIOx == NULL){ return -1; }
    printk(KERN_INFO "(%d) [fopen ] GPIO_Virtual Memory address = 0x%08X \n",MAJOR_NUMBER, GPIOx);
    buffer_len = 0;
    memset(buffer,'\0', 1024*sizeof(char));
    return  0;
}

int GPIO_BANK_CLOSE(struct inode * _1, struct file * _2){
    if(GPIOx == NULL){ return -1; }
    iounmap(GPIOx);
    printk(KERN_INFO "(%d) [fclose] deteted! GPIO_Virtual Memory address(0x%08X) \n",MAJOR_NUMBER, GPIOx);
    return 0;
}

ssize_t GPIO_WRITE(struct file * _1, const char __user * _2, size_t _3, loff_t * _4){
    if(GPIOx == NULL){ return -1; }
    if(!_3){ return 0; }
    memset(buffer,'\0', (buffer_len+2)*sizeof(char));
    buffer_len = _3-1;
    unsigned int _ret = copy_from_user(&buffer[0], _2, sizeof(char)*buffer_len);
    int pinNUM =  0;
    if(kstrtoint(&buffer[2], 10, &pinNUM) == 0){
        /* ================================== */
        int tmpX = 0;
        if(pinNUM >=0 && pinNUM <=9){          tmpX =pinNUM-00;tmpX*=3; GPIOx->BANK[0]  &= ~((0x7 << tmpX)); GPIOx->BANK[0]  |=  ((0x1 << tmpX)); }
        else if(pinNUM >=10 && pinNUM <=19){   tmpX =pinNUM-10;tmpX*=3; GPIOx->BANK[1]  &= ~((0x7 << tmpX)); GPIOx->BANK[1]  |=  ((0x1 << tmpX)); }
        else if(pinNUM >=20 && pinNUM <=29){   tmpX =pinNUM-20;tmpX*=3; GPIOx->BANK[2]  &= ~((0x7 << tmpX)); GPIOx->BANK[2]  |=  ((0x1 << tmpX)); }
        else if(pinNUM >=30 && pinNUM <=39){   tmpX =pinNUM-30;tmpX*=3; GPIOx->BANK[3]  &= ~((0x7 << tmpX)); GPIOx->BANK[3]  |=  ((0x1 << tmpX)); }
        else if(pinNUM >=40 && pinNUM <=49){   tmpX =pinNUM-40;tmpX*=3; GPIOx->BANK[4]  &= ~((0x7 << tmpX)); GPIOx->BANK[4]  |=  ((0x1 << tmpX)); }
        else if(pinNUM >=50 && pinNUM <=59){   tmpX =pinNUM-50;tmpX*=3; GPIOx->BANK[5]  &= ~((0x7 << tmpX)); GPIOx->BANK[5]  |=  ((0x1 << tmpX)); }
        if(buffer[0] == '0'){
            int tmpPOS = ((pinNUM > 31) ? (pinNUM-32) : (pinNUM));
            if(pinNUM <= 31){ 
                GPIOx->SET[0] = ( 1 << tmpPOS);
            }else{ 
                GPIOx->SET[1] = ( 1 << tmpPOS);
            }
        }else{
            int tmpPOS = ((pinNUM > 31) ? (pinNUM-32) : (pinNUM));
            if(pinNUM <= 31){ 
                GPIOx->CLEAR[0] = ( 1 << tmpPOS);
            }else{ 
                GPIOx->CLEAR[1] = ( 1 << tmpPOS);
            }
        }
        
    }
    return _3;
}
struct file_operations  fOPS = {
    .owner = THIS_MODULE,
    .open = GPIO_BANK_OPEN,
    .release = GPIO_BANK_CLOSE,
    .write = GPIO_WRITE
};
static int  __init Init_GPIO_Driver(void){
    MAJOR_NUMBER = register_chrdev(0,"GPIO_koya",&fOPS); 
    if(MAJOR_NUMBER <= 0){ return -1; }
    printk(KERN_INFO "(%d) %s \n",MAJOR_NUMBER,__func__);
    return 0;
}

static void __exit dInit_GPIO_Driver(void){
    unregister_chrdev(MAJOR_NUMBER,"GPIO_koya");
    printk(KERN_INFO "(%d) %s\n", MAJOR_NUMBER,__func__);
}




/* setting the entry point of module init/exit */
module_init(Init_GPIO_Driver);
module_exit(dInit_GPIO_Driver);
MODULE_LICENSE("GPL");
