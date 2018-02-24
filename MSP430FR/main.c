#include "gpio.h"					//we use gpio
#include "delay.h"					//we use software delay
#include "systick.h"				//we use systick
#include "tmra0.h"					//we use tmra0
#include "tmra1.h"					//we use tmra1
#include "tmra2.h"					//we use tmra2
#include "tmra3.h"					//we use tmra3
#include "tmrb0.h"					//we use tmrb0
#include "pwmta0.h"					//we use pwmta0

//hardware configuration
#define LED1_PORT		PORTB		//P4.6=PB.14
#define LED1			(1<<14)		//LED1/red led
#define LED2_PORT		PORT1		//P1.0=PA.0
#define LED2			(1<<0)		//LED2/green led on FR5969 launchpad

#define LED_DLY			20000ul		//16-bit
//end hardware configuration

//flip led1
void led_flp(void) {
	IO_FLP(LED1_PORT, LED1);		//flip the led
}

int main( void ) {
	uint32_t i;
	
	mcu_init();						//reset the mcu

	//initialize the leds
	IO_OUT(LED1_PORT, LED1);		//led1 as output
	IO_OUT(LED2_PORT, LED2);		//led2 as output

	//systick
	systick_init();					//reset systick
	//systick_setpr0(5000);
	//systick_act0(led_flp);
	//systick_setpr1(5050);
	//systick_act1(led_flp);

	//TIMERA0..3
	//tmra3_init(TMRA_PS8x | TMRA_EX1x);
	//tmra3_setpr0(1010); tmra3_act0(led_flp);
	//tmra3_setpr1(1000); tmra3_act1(led_flp);

	//TIMERB0 - flip led1
	tmrb0_init(TMRB_PS2x | TMRB_EX4x);
	tmrb0_setpr2(1000); tmrb0_act2(led_flp);
	tmrb0_setpr6(1010); tmrb0_act6(led_flp);

	//pwmta0
	//pwmta0_init(TMRA_PS1x | TMRA_EX1x, 10000);
	//pwmta0_setdc1(10);				//ta0_ch2 on  10/10000 duty cycle
	//pwmta0_setdc2(100);				//ta0_ch2 on 100/10000 duty cycle
	
	ei();
	while (1) {
		IO_FLP(LED2_PORT, LED2);	//flip led2
		i=systicks();
		delay(LED_DLY);				//waste sometime
		i=systicks() - i;
		if (i) NOP();
	}
	
	return 0;
}
