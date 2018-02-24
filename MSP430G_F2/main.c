//#include <msp430.h> 					//we use ccs/msp430
//msp430g2 launchpad
//msp430g2553 or msp430g2452
//msp430f2418 - proteus
//msp430fr5969
#include "gpio.h"						//we use gpio
#include "delay.h"						//we use software delays
#include "tmra0.h"						//timer a0
#include "tmra1.h"						//timer a1
#include "tmra2.h"						//timer a2
#include "tmra3.h"						//timer a3
#include "tmrb0.h"						//timer b0
#include "systick.h"					//use ta3_ccr0 as systick counter

//hardware configuration
#define LED_PORT		P3OUT			//GPIOA.1/Green and GPIOB.14/Red
#define LED_DDR			P3DIR
#define LED				(1<<0)
//end hardware configuration

//global defines

//global variables

//flip the led
void led_flp(void) {
	IO_FLP(LED_PORT, LED);
}

int main(void) {
	volatile uint32_t time0, time1;

	mcu_init();							//reset the mcu
	IO_OUT(LED_DDR, LED);				//set led as output
	//IO_OUT(LED_DDR, LED2);
	//systick_init();
	
	//set a0
	//tmra0_init(TMRB_PS1x | TMRB_EX1x);
	//tmra0_setpr0(10000);
	//tmra0_act0(led_flp);
	//tmra0_setpr2(10100);
	//tmra0_act2(led_flp);

	tmrb0_init(TMRA_PS1x | TMRA_EX1x);
	tmrb0_setpr0(10000);
	tmrb0_act0(led_flp);
	tmrb0_setpr1(10000*1.01);
	tmrb0_act1(led_flp);
	
	ei();								//enable interrupt
	while (1) {
		//IO_FLP(LED_PORT, LED);		//flip led
		//IO_FLP(LED1_PORT, LED1);
		//time0=ticks();
		delay_ms(50);					//waste some time
		//time1=ticks() - time0;
		//if (time0==time1) NOP();
		
	};
	return 0;
}
