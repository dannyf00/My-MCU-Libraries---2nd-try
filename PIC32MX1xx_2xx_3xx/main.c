#include "config.h"						//configuration words
#include "gpio.h"
#include "delay.h"						//we use software delays
#include "pwm1.h"						//use pwm generator
#include "pwm2.h"						//use pwm generator
#include "pwm3.h"						//use pwm generator
#include "pwm4.h"						//use pwm generator
#include "pwm5.h"						//use pwm generator
#include "refco.h"						//use reference clock generator
#include "systick.h"					//we use systick
#include "uart1isr.h"					//we use uart1isr
#include "uart2isr.h"					//we use uart2isr
#include "systick.h"					//we use systick
#include "adc.h"						//we use adc

//hardware configuration
#define LED_PORT			LATB
#define LED_DDR				TRISB
#define LED					(1<<7)
#define LED_DLY				80000ul		//cycles to be wasted -> to manage main loop update frequency
//end hardware configuration

//global defines
#define ADC
//global variables

//flip the led
void led_flp(void) {
	IO_FLP(LED_PORT, LED);
}

char uRAM[40]="uart0 = \n\r";

int main(void) {
	uint16_t i=0;
	uint32_t tmp, cnt=0;

	mcu_init();						//reset the mcu
	//SystemCoreClock = 50000000ul;	//for simulating 50Mhz top clock

	IO_OUT(LED_DDR, LED);			//led as output

	systick_init();					//reset systick

	//adc_init();						//reset the adc

	//pwm generation
	//pwm1_init(TMRPS_16x, 1000);	//1 flash per second
	//pwm1_setdc(10);		//1% dc

	uart1_init(9600);
	uart2_init(9600);				//initialize uart0

	ei();							//enable interrupts
	while (1) {
		IO_FLP(LED_PORT, LED);		//flip the led
		//i=adc_read(ADC_AN0);		//read the adc
		i=systicks();				//time stamp
		systick_delay(LED_DLY);	//waste some time
		i=systicks() - i;
		if (i) NOP();

		//display tmp
		tmp = i;					//display i
		//convert tmp to uRAM
		uRAM[20]=0, uRAM[19]='\n',  uRAM[18]='\r';
		uRAM[17]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[16]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[15]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[14]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[13]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[12]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[11]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[10]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[ 9]=' ';
		tmp = cnt++ & 0xffff;					//display cnt
		uRAM[ 8]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[ 7]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[ 6]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[ 5]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[ 4]=(tmp % 10) + '0'; tmp /= 10;
		uRAM[ 3]='=';
		uRAM[ 2]='p';
		uRAM[ 1]='m';
		uRAM[ 0]='t';
		//display u RAM
		if (!uart1_busy()) uart1_puts(uRAM);
		if (!uart2_busy()) uart2_puts(uRAM);
		//uart1_put(0x55);
	}
}
