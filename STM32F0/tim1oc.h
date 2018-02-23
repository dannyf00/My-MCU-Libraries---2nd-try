#ifndef _TMR1_OC_H
#define _TMR1_OC_H

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
//initialize tim1 to use compare channels as timers
//16-bit prescaler. 32-bit used for compatability
void tim1_init(uint32_t ps);

//set tim1_oc1 period
//pr is 16-bit. 32-bit used for compatability;
void tim1_setpr1(uint32_t pr);
//install user handler
void tim1_act1(void (*isr_ptr)(void));

//set tim1_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim1_setpr2(uint32_t pr);
//install user handler
void tim1_act2(void (*isr_ptr)(void));

//set tim1_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim1_setpr3(uint32_t pr);
//install user handler
void tim1_act3(void (*isr_ptr)(void));

//set tim1_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim1_setpr4(uint32_t pr);
//install user handler
void tim1_act4(void (*isr_ptr)(void));

#endif
