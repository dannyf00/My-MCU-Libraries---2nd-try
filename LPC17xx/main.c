#include "gpio.h"					//we use gpio
#include "delay.h"					//we use software delays
//#include "systick.h"				//we use systick
//#include "rit.h"					//we use repetitive interrupt timer
//#include "tmr0.h"					//we use timer0

//hardware configuration
#define LED_DLY			1000000		//waste some cycles
//end hardware configuration


int main() {
	mcu_init();						//reset the mcu
	IO_OUT(LED_PORT, LED);			//led as output
	while (1) {
		IO_FLP(LED_PORT, LED);		//flip the led
		//FIO_FLP(LED_PORT, LED);		//flip the led
		delay(LED_DLY);				//waste some time
	}
  	return 0;
}
