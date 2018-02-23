//#include <lpc11xx.h>				//we use lpc1114
#include "gpio.h"					//we use F_CPU + gpio functions
#include "delay.h"					//we use software delays
//#include "systick.h"				//we use systick

//hardware configuration
#define LED_DLY			100			//ms
//end hardware configuration

//global variable
uint32_t tmp;

int main(void) {
	mcu_init();									//reset the  mcu
	tmp=F_CPU;									//read f_cpu - for debugging
	IO_OUT(LED_PORT, LED);						//led3/4 as output
	while (1) {
		IO_FLP(LED_PORT, LED);					//flip led3/4
		delay_ms(LED_DLY);						//waste some time
	};
}
