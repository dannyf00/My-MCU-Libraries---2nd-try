#include "gpio.h"					//we use own gpio macros

//reset the mcu
void mcu_init(void) {
	/* Enable AHB clock to the GPIO domain. */
	//LPC_SC->SYSAHBCLKCTRL |= (1<<6);		//for gpio
	//LPC_SC->PCONP |= 1<<15;			//15: enable clock to gpio
	//SystemCoreClockUpdate();					//update SystemCoreClock
}

