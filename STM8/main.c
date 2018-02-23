#include "gpio.h"							//we use gpio
#include "delay.h"							//we use software delays

//hardware configuration
#define LED_PORT		GPIOD
#define LED				(1<<0)
//end hardware configuration

//global defines

//global variables

void main(void) {
	mcu_init();								//reset the mcu
	while (1) {
	};
}
