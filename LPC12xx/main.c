//#include <lpc122x.h>				//we use lpc122x
#include "gpio.h"					//we use F_CPU + gpio functions
#include "delay.h"					//we use software delays
#include "systick.h"				//we use systick
#include "dhry.h"					//we use dhrystone benchmark
#include "tmr32b1_pwm.h"
#include "uart0.h"					//we use uart0
#include "uart1.h"					//we use uart1
#include "adc.h"
#include "tmr16b1_mr.h"
#include "coretick.h"

//hardware configuration
#define LED_DLY			100			//counts
#define PWM_STEP		50
//end hardware configuration

//global defines

//global variables
uint32_t tmp;

//flip led
void led_flp(void) {
	//static int count=0;							//count
	FIO_FLP(LED_PORT, LED);					//flip the led
}

//set led
void led_set(void) {
	//static int count=0;							//count
	FIO_SET(LED_PORT, LED);					//flip the led
}

//clr led
void led_clr(void) {
	//static int count=0;							//count
	FIO_CLR(LED_PORT, LED);					//flip the led
}


int main(void) {
	uint32_t time0, time1, tmp;
	int32_t index;

	mcu_init();									//reset the  mcu
	systick_init();								//reset systick
	//tmr32b1_pwminit(1, 1<<15);					//initialize pwm
	//tmr32b1_setdc1(LPC_CT32B1->MR0/40);			//set pwm duty cycle
	//tmr16b1_init(10);
	//tmr16b1_setpr1(10000); tmr16b1_act1(led_flp);
	//tmr16b1_setpr2(10000+100); tmr16b1_act2(led_flp);

	IO_OUT(LED_PORT, LED);						//led3/4 as output
	tmp=F_CPU;									//read f_cpu - for debugging
	//uart0_init(9600);
	//uart1_init(9600);
	//adc_init();
	ei();
	while (1) {
		IO_FLP(LED_PORT, LED);				//flip led

		time0=ticks();							//time stamp time0
		//dhrystone();							//benchmark
		delayms(LED_DLY);				//benchmark test
		//ticks();								//109 ticks
		//micros();								//204 ticks
		//millis();								//309 ticks
		//uart0_puts("12345678\n\r");
		//uart1_puts("23456789\n\r");
		//for (index=0; index<1000; index++) tmp=adc_read(ADC_CH4);
		time1=ticks() - time0;					//time stamp and calculate elapsed time
		if (time1>10) NOP();					//break point
	}
}

