#ifndef _TMR3_OC_H
#define _TMR3_OC_H

#include <stdint.h>
#include "gpio.h"

//calling convention
	//initialize the timer
	//tim4_init(1000/2);							//with a prescaler

	//initialize oc1 to call a user handler
	//tim4_setpr1(1000);							//specify period
	//tim4_act1(led_flp);							//install user handler
//end calling convention

//hardware configuration
//end hardware configuration

//global defines
//initialize tim3 to use compare channels as timers
//16-bit prescaler. 32-bit used for compatability
void tim3_init(uint32_t ps);
void tim3_act(void (*isr_ptr)(void));

//set tim3_oc1 period
//pr is 16-bit. 32-bit used for compatability;
void tim3_setpr1(uint32_t pr);
//install user handler
void tim3_act1(void (*isr_ptr)(void));

//set tim3_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim3_setpr2(uint32_t pr);
//install user handler
void tim3_act2(void (*isr_ptr)(void));

//set tim3_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim3_setpr3(uint32_t pr);
//install user handler
void tim3_act3(void (*isr_ptr)(void));

//set tim3_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim3_setpr4(uint32_t pr);
//install user handler
void tim3_act4(void (*isr_ptr)(void));

#endif
