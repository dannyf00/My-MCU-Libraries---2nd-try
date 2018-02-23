#include "gpio.h"									//use gpio
#include "delay.h"									//use software delays
#include "coretick.h"
#include "systick.h"								//use systick
//#include "uart0isr.h"								//use uart0/vcp
#include "timer0.h"
#include "timer1.h"
#include "timer2.h"
#include "pwm.h"									//we use ccp
#include "Hpwm.h"									//we use HARDWARE PWM
#include "pwm2tmr.h"								//configure pwm as timers
#include "uart.h"

//hardware configuration
#define LED_PORT			GPIOC
#define LED					(1<<5)					//1=R, 2=B, 3=G
//end hardware configuration

//global defines

//global variables

void led_flp(void) {
	static int i=0;
	//if (i++ == 2) {IO_FLP(LED_PORT, LED); i=0;}
	IO_FLP(LED_PORT, LED);
}

char uRAM[40];

int main(void) {
	int32_t i, tmp, counter=0;

	mcu_init();										//reset the  mcu
	coretick_init();								//initialize coretick
	systick_init();									//initialize systick

	//tmr0a_init(10, 1000);
	//tmr0a_act(led_flp);
	//tmr2b_init(10, 1001);
	//tmr2b_act(led_flp);
	IO_OUT(LED_PORT, LED);							//led as output

	//HPWM1_init(1, 10000); HPWM1A_setdc(i=0);		//use hardware pwm
	//pwm1_init(1, 10000); pwm1_setdc(i=0);			//use timer ccp

	//pwm2tmr - does not work as cmpa/cmpb not updated until zero is reached
	//pwm0a_init(PWM_PS32x, 40000); pwm0a_act(led_flp);
	uart0_init(9600);
	ei();											//enable interrupts
	while(1) {
		//cycle counting
		counter+=1;
		//flip led
		//tmp = TIMER5->TBR;
		IO_FLP(LED_PORT, LED);					//to be benchmarked
		//tmp = TIMER5->TBR - tmp;
		//tmp = ticks();							//time stamp
		//i+=1; if (i==10000) i=0;					//increment duty cycle
		//pwm1_setdc(i);
		tmp = coreticks();
		delay(100000);									//waste some time
		tmp = coreticks() - tmp;						//calculate time elapsed
		if (tmp) NOP();

		//uart0
		//uart0_puts("test uart0\n\r");
		//tmp = UART0->FBRD;
		tmp = SystemCoreClock;
		uRAM[20]=0; uRAM[19]='\n'; uRAM[18]='\r';
		uRAM[17]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[16]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[15]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[14]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[13]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[12]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[11]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[10]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[ 9]= ' ';
		tmp = counter & 0xff;
		uRAM[ 8]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[ 7]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[ 6]= (tmp % 10) + '0'; tmp /= 10;
		uRAM[ 5]=' ';
		uRAM[ 4]=' ';
		uRAM[ 3]='=';
		uRAM[ 2]='p';
		uRAM[ 1]='m';
		uRAM[ 0]='t';
		if (!uart0_busy()) uart0_puts(uRAM);
	}

	return 0;
}


