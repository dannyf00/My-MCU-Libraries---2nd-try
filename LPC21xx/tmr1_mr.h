#ifndef _TMR1_MR_H
#define _TMR1_MR_H

#include "gpio.h"					//we use gpio

//hardware configuration
//end hardware configuration

//global defines
#define CTMCR_EINT		0x01		//enable interrupt on match
#define CTMCR_RESET		0x02		//reset on match
#define CTMCR_STOP		0x04		//stop on match


//global variable


//initialize the timer
//upcounter
void tmr1_init(uint32_t ps);

//set up the match
void tmr1_setpr0(uint32_t pr);

//install user handler
void tmr1_act0(void (*isr_ptr)(void));

//set up the match
void tmr1_setpr1(uint32_t pr);

//install user handler
void tmr1_act1(void (*isr_ptr)(void));

//set up the match
void tmr1_setpr2(uint32_t pr);

//install user handler
void tmr1_act2(void (*isr_ptr)(void));

//set up the match
void tmr1_setpr3(uint32_t pr);

//install user handler
void tmr1_act3(void (*isr_ptr)(void));

#endif
