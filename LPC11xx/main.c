//#include <lpc11xx.h>				//we use lpc1114
#include "gpio.h"					//we use F_CPU + gpio functions
#include "delay.h"					//we use software delays
//#include "systick.h"				//we use systick
#include "tmr16b0_mr.h"				//we use tmr16b0
#include "tmr16b1_mr.h"				//we use tmr16b1
#include "tmr32b0_mr.h"				//we use tmr16b0
#include "tmr32b1_mr.h"				//we use tmr16b1
//#include "tmr16b1.h"				//we use tmr16b1
//#include "tmr32b0.h"				//we use tmr32b0
//#include "tmr32b1.h"				//we use tmr32b1
//#include "dhry.h"					//we use dhrystone
//#include "benchmark_ti.h"			//we use ti benchmark

//hardware configuration
#define LED_DLY			10000		//ticks
//end hardware configuration

//global variable
uint32_t tmp;

//set led
void led_set(void) {
	FIO_SET(LED_PORT, LED);
}

//clr led
void led_clr(void) {
	FIO_CLR(LED_PORT, LED);
}

//flip led
void led_flp(void) {
	IO_FLP(LED_PORT, LED);
}

int main(void) {
	volatile uint32_t tmp0;
	mcu_init();									//reset the  mcu
	IO_OUT(LED_PORT, LED);						//led3/4 as output
	//systick_init(SYSTICK_1ms);				//configured in ms
	tmp=F_CPU;									//read f_cpu - for debugging
	tmr32b1_init(100);							//set prescaler to 1000:1
	tmr32b1_setpr0(LED_DLY);					//set time base -> force roll-over on match
	tmr32b1_act0(led_flp);

	tmr32b0_init(100);
	tmr32b0_setpr1(LED_DLY * 1.01);				//set duty cycle
	tmr32b0_act1(led_flp);
	ei();										//enable interrupt
	while (1) {
		//tmp = systick_get();					//time stamp
		//FIO_SET(LED_PORT, LED);				//flip led3/4
		//delay_ms(100);					//waste some time
		//FIO_CLR(LED_PORT, LED);				//flip led3/4
		//delay_ms(100);					//waste some time
		//dhrystone();							//run dhrystone benchmark
		//run ti benchmark
		//tmp0=benchmark(200, main_fir);		//run ti benchmark
		//tmp = systick_get() - tmp;			//time stamp again
	};
}
