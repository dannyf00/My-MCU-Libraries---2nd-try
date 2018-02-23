#include "config.h"					//configuration words - for C30. Use config.h for XC16
#include "gpio.h"
#include "delay.h"						//we use software delays

//hardware configuration
#define LED_PORT			PORTB
#define LED_DDR				TRISB
#define LED					(1<<0)
//end hardware configuration

//global defines

//global variables


int main(void) {
	mcu_init();							//reset the mcu
	IO_OUT(LED_DDR, LED);				//led as output
	while (1) {
	}
}
