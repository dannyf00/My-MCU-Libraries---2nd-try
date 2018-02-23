#include <p24fxxxx.h>					//we use pic24f
#include "gpio.h"
#include "config.h"					//configuration words


//hardware configuration
//end hardware configuration

void mcu_init(void) {
}
	
//main code section
int main(void)
{         
	mcu_init();						//reset the mcu


	ei();
	while(1) {
		//flp();
	}           
}

