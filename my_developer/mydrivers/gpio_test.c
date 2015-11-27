#include <stdio.h>
#include <stdlib.h>

#define MSS_GPIO_CFG		0x40013000
#define MSS_GPIO_IRQ		0x40013080
#define MSS_GPIO_IN			0x40013084
#define MSS_GPIO_OUT		0x40013088

#define FPGA_GPIO_CFG		CONFIG_M2S_FPGA_GPIO_ADDR
#define FPGA_GPIO_IRQ		(FPGA_GPIO_CFG + 0x80)
#define FPGA_GPIO_IN		(FPGA_GPIO_CFG + 0x90)
#define FPGA_GPIO_OUT		(FPGA_GPIO_CFG + 0xa0)


unsigned int * GPIO_OUT=(unsigned int*)MSS_GPIO_OUT;


void initGPIO(unsigned char gpio){
	unsigned int * cfg =(unsigned int *)(MSS_GPIO_CFG+gpio*sizeof(unsigned int));
	*cfg=0x01;
}

void setGPIO(unsigned int out,unsigned int GPIO_number){
	unsigned int gpio_s=1<<GPIO_number;
	unsigned int previous_gpio=0;
	previous_gpio=*GPIO_OUT;
	if(out==0)
		*GPIO_OUT=previous_gpio & (~gpio_s);
	else
		*GPIO_OUT=previous_gpio | (gpio_s);
}


int main(int argc, char ** argv)
{
	unsigned int gpio_status=0;	
 	unsigned int GPIO_number=0;
	if(argc<=1){
		printf("xxx.o pin state, try again");
		exit(1);
	}
	sscanf(argv[1],"%d",&GPIO_number);
	if(GPIO_number>31){
		printf("GPIO number should be less than 32");
		exit(1);
	}
	sscanf(argv[2],"%d",&gpio_status);
	/*soft register*/
/*	unsigned int * SYSREG_SOFT_RST_CR=(unsigned int * )0xE0042030;
	/*Reset GPIO hardware*/
//	*SYSREG_SOFT_RST_CR |=0x00004000;
	/**take GPIO hw out of reset*/
//	*SYSREG_SOFT_RST_CR &=~(0x00004000);
	initGPIO(GPIO_number);		
	setGPIO(gpio_status,GPIO_number);
	return 0;
}	


