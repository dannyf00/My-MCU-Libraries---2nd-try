/*
 * tmr32.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Ken
 */

#ifndef TMR32_H_
#define TMR32_H_


//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

//#include "msp.h"
#include "gpio.h"					//we use gpio

//hardware configuration
//end hardware configuration

//global defines
#define TMR32PS_1x			(0b00<<2)		//prescaler 1:1
#define TMR32PS_16x			(0b01<<2)		//prescaler = 16:1
#define TMR32PS_256x		(0b10<<2)		//prescaler = 256:1
#define TMR32PS_MASK		(TMR32PS_16x | TMR32PS_256x)		//prescaler mask

//global variables

//user isr ptr
//static void (* _tmr321_isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default
//static void (* _tmr322_isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default


//initialize tmrx
void tmr321_init(uint32_t prescaler, uint32_t period);

//install user handler for tmrx
void tmr321_act(void (*isrptr)(void));


//initialize tmrx
void tmr322_init(uint32_t prescaler, uint32_t period);

//install user handler for tmrx
void tmr322_act(void (*isrptr)(void));


#endif /* TMR32_H_ */
