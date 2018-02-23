//#define TARGET_IS_BLIZZARD_RA1					//indicate parts, for rom functions
//#define PART_TM4C1233H6PM							//indicate parts, for pin / memory definitions
#include "gpio.h"									//use gpio
#include "delay.h"									//use software delays
#include "coretick.h"
//#include "timer0.h"									//use timers / wtimers
#include "systick.h"								//use systick
//#include "uart0isr.h"								//use uart0/vcp

//hardware configuration
#define LED_PORT			GPIOK
#define LED					(1<<3)					//1=R, 2=B, 3=G
//end hardware configuration

//global defines

//global variables


int main(void) {
	uint32_t i, tmp;
	
	mcu_init();										//reset the  mcu
	coretick_init();								//initialize coretick
	systick_init();									//initialize systick
	
	IO_OUT(LED_PORT, LED);							//led as output

	ei();											//enable interrupts
	while(1) {
		//flip led
		IO_FLP(LED_PORT, LED);						//to be benchmarked
		tmp = ticks();							//time stamp
		delay_ms(100);								//waste some time
		tmp = ticks() - tmp;					//calculate time elapsed
	}

	return 0;
}


