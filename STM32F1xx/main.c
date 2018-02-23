#include "gpio.h"					//we use F_CPU + gpio functions
#include "delay.h"					//we use software delays
//#include "coretick.h"				//we use dwt
//#include "dhry.h"					//we use dhrystone benchmark
//#include "tim2oc.h"					//we use tim2 output compare as timers
//#include "adc1.h"					//we use adc
//#include "uart.h"

//hardware configuration
#define LEDG_PORT		GPIOC
#define LEDG			(1<<9)		//green led on PC9 on Discovery board

#define LEDB_PORT		GPIOC
#define LEDB			(1<<8)		//blue led on PC8 on Discovery board

#define LED_PORT		LEDG_PORT
#define LED				LEDG
//end hardware configuration

//global defines

//global variables

int main(void) {
	mcu_init();									//reset the  mcu
	//coretick_init();							//reset coretick

	//initialize the pins to outout
	IO_OUT(LEDG_PORT, LEDG);					//ledg/b as output
	IO_OUT(LEDB_PORT, LEDB);

	ei();										//enable global interrupts
	while (1) {
		IO_FLP(LEDG_PORT, LEDG);				//flip ledg
		delay_ms(100);							//waste sometime
	};
}
