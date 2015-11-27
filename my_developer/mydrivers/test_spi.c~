#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
	char count=10;
	unsigned char led_ds3=0;
	char command[100];
	while(count>0){
		led_ds3=led_ds3^1;	
		count--;
		sprintf(command,"gpio_test.o %s %d","1",led_ds3);

		system(command);
		usleep(100000);
	}
	return 0;	
}	


