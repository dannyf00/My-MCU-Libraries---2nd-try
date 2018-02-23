#include "gpio.h"					//we use F_CPU + gpio functions
#include "delay.h"					//we use software delays
//#include "coretick.h"				//we use dwt
#include "systick.h"				//we use systick
//#include "dhry.h"					//we use dhrystone benchmark
//#include "tim2oc.h"					//we use tim2 output compare as timers
#include "adc1.h"					//we use adc
//#include "uart1.h"				//we use uart1isr
#include "uart1isr.h"				//we use uart1isr
#include "tim14.h"					//we use tim14
#include "tim16.h"					//we use tim16
#include "tim17.h"					//we use tim17

//hardware configuration
#define LED_PORT		GPIOA
#define LED1			(1<<3)
#define LED2			(1<<4)
//end hardware configuration

//global defines

//global variables

//flip led
void led_flp(void) {
	IO_FLP(LED_PORT, LED1);
}

uint32_t time0, time1;
int32_t tmp;
char uRAM[20];
int main(void) {
	int i;
	uint32_t time0, time1;

	mcu_init();								//reset the  mcu
	systick_init();							//reset systick

	//initialize the pins to outout
	IO_OUT(LED_PORT, LED1 | LED2);			//ledg/b as output
	IO_SET(LED_PORT, LED1);
	IO_CLR(LED_PORT, LED2);					//cathode/ground

	//adc1_init();							//reset the adc

	uart1_init(9600);						//reset uart1

	tim16_init(100);							//initialize tim1
	tim16_setpr(10000);						//set the period for oc1
	tim16_act(led_flp);						//install user handler

	ei();									//enable global interrupts
	while (1) {
		//IO_FLP(LED_PORT, LED1);				//flip the led
		time0=ticks();						//timestamp time0
		i=time0;
		//i=12345679;
		//display i;
		uRAM[8]='\n', uRAM[9]='\r'; uRAM[10]=0;
		uRAM[7]= (i % 10) + '0'; i /= 10;
		uRAM[6]= (i % 10) + '0'; i /= 10;
		uRAM[5]= (i % 10) + '0'; i /= 10;
		uRAM[4]= (i % 10) + '0'; i /= 10;
		uRAM[3]= (i % 10) + '0'; i /= 10;
		uRAM[2]= (i % 10) + '0'; i /= 10;
		uRAM[1]= (i % 10) + '0'; i /= 10;
		uRAM[0]= (i % 10) + '0'; i /= 10;
		if (!uart1_busy()) uart1_puts(uRAM);
		time1=ticks() - time0;				//calculate th etime elapsed
		//NOP();
		delayms(100);						//waste sometime
	};
}
