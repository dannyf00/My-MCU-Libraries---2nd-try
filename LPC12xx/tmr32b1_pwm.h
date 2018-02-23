/*
 * tmr16b0.h
 *
 *  Created on: May 15, 2016
 *      Author: Ken
 */

#ifndef TMR32B1PWM_H_
#define TMR32B1PWM_H_

//#include <lpc122x.h>				//we use lpc122x
#include "gpio.h"					//we use F_CPU + gpio functions

//hardware configuration
//end hardware configuration

//global defines
//global variable

//pointer to user handler


//set up tmr - MR0 controls pwm pmeriod
void tmr32b1_pwminit(uint32_t ps, uint32_t pr);

//set up match register - ch0
//void tmr32b1_setdc0(uint32_t match/*, uint32_t config*/);

//set up match register - ch1
void tmr32b1_setdc1(uint32_t match/*, uint32_t config*/);

//set up match register - ch2
void tmr32b1_setdc2(uint32_t match/*, uint32_t config*/);

//set up match register - ch3
void tmr32b1_setdc3(uint32_t match/*, uint32_t config*/);
#endif /* tmr32b1_H_ */
