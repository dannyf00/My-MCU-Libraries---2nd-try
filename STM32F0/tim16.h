#ifndef _TMR16_H
#define _TMR16_H

#include <stdint.h>
#include "gpio.h"

//calling convention
	//initialize the timer
	//tim14_init(1000/2);							//with a prescaler

	//initialize oc1 to call a user handler
	//tim14_setpr(1000);							//specify period
	//tim14_act(led_flp);							//install user handler
//end calling convention

//hardware configuration
//end hardware configuration

//global defines
//initialize tim4 to use compare channels as timers
//16-bit prescaler. 32-bit used for compatability
void tim16_init(uint32_t ps);

//set tim4_oc1 period
//pr is 16-bit. 32-bit used for compatability;
void tim16_setpr(uint32_t pr);
//install user handler
void tim16_act(void (*isr_ptr)(void));

#endif
