//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

//#include "msp.h"
#include "gpio.h"					//we use gpio
#include "delay.h"					//we use software delay
#include "systick.h"				//we use systick
#include "tmr32.h"					//we use tmr32
#include "ta0oc.h"					//we use tmra0
#include "ta1oc.h"					//we use tmra1
#include "ta2oc.h"					//we use tmra2
#include "ta3oc.h"					//we use tmra3
#include "coretick.h"

//hardware configuration
#define LED_DLY			50000		//waste time, in clock ticks
//end hardware configuration

//global defines

//global variables

//flip red led
void led_flp(void) {
	IO_FLP(LED_PORT, LED);
}

uint32_t tmp;
void main(void){
	uint32_t time0, time1;
    mcu_init();									//reset the mcu
    systick_init();								//initialize systick
    coretick_init();							//reset coretick

    IO_OUT(LED_DDR, LED);						//led as output

    //set up time base
    tmra0_init(TMRA_PS1x | TMRA_EX1x);			//start tmra0
    //set up ccr1 to drive one led
    tmra0_setpr1(LED_DLY);						//set ccr1 period
    tmra0_act1(led_flp);						//install user handler
    //set up ccr2 for a different channel
    tmra0_setpr2(LED_DLY * 1.01);				//set ccr2 period, with a slight offset
    tmra0_act2(led_flp);						//install user handler

    //set up time base
    //tmra1_init(TMRA_PS1x | TMRA_EX1x);			//start tmr1
    //set up ccr2..4 to drive rgb led
    //tmra1_setpr0(LED_DLY * 1.01);				//set ccr0 period
    //tmra1_act0(led_flp);						//install user handler
    ei();
    while (1) {
    	time0=ticks();
    	delayms(10);
    	time1=ticks() - time0;
    }
}
