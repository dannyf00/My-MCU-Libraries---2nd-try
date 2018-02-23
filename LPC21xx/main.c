#include "gpio.h"					//we use gpio
#include "delay.h"					//we use software delays

//hardware configuration
#define LED_DLY			10000		//waste some cycles
//end hardware configuration


int main() {
	mcu_init();						//reset the mcu
	IO_OUT(LED_DDR, LED);			//led as output
	while (1) {
		IO_FLP(LED_PORT, LED);		//flip the led
		//FIO_FLP(LED_PORT, LED);		//flip the led
		delay(LED_DLY);				//waste some time
	}
  	return 0;
}
