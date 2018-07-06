#ifndef _TMR4_OC_H
#define _TMR4_OC_H

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
//initialize tim4 to use compare channels as timers
//16-bit prescaler. 32-bit used for compatability
void tim4_init(uint32_t ps);
void tim4_act(void (*isr_ptr)(void));

//set tim4_oc1 period
//pr is 16-bit. 32-bit used for compatability;
void tim4_setpr1(uint32_t pr);
//install user handler
void tim4_act1(void (*isr_ptr)(void));

//set tim4_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim4_setpr2(uint32_t pr);
//install user handler
void tim4_act2(void (*isr_ptr)(void));

//set tim4_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim4_setpr3(uint32_t pr);
//install user handler
void tim4_act3(void (*isr_ptr)(void));

//set tim4_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim4_setpr4(uint32_t pr);
//install user handler
void tim4_act4(void (*isr_ptr)(void));

#endif
