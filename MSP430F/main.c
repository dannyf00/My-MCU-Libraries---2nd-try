//#include <msp430.h> 					//we use ccs/msp430
//msp430g2 launchpad
//msp430g2553 or msp430g2452
//msp430f2418 - proteus
#include "gpio.h"						//we use gpio
#include "delay.h"						//we use software delays
//#include "tmra.h"						//timer a

//hardware configuration
//end hardware configuration

//global defines

//global variables

int main(void) {

	mcu_init();							//reset the mcu
	GIO_OUT(LED_GPIO, LEDR);			//set led as output
	ei();								//enable interrupt
	while (1) {
		GIO_FLP(LED_GPIO, LEDR);		//flip led
		delay_ms(500);					//waste some time
	};
	
	return 0;
}
