/*
 * rit.h
 *
 *  Created on: May 18, 2016
 *      Author: Ken
 */

#ifndef RIT_H_
#define RIT_H_

#include "gpio.h"					//we use gpio

//hardware configuration
//end hardware configuration

//global defines
#define RIT_PS1x		0b01
#define RIT_PS2x		0b10
#define RIT_PS4x		0b00
#define RIT_PS8x		0b11

//global variables

//reset rit
void rit_init(uint32_t ps, uint32_t pr);

//install user handler
void rit_act(void (*isr_ptr)(void));

#endif /* RIT_H_ */
