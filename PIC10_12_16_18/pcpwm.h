//hearder file for 14-bit power control pwm in 18f4331

#if   defined (_18F2331) || defined (_18F2431) || defined (_18F4331) || defined (_18F4431)
#else
#warning this header file only applicable to PIC18F2331/2431/4331/4431
#endif

#ifndef _PCPWM_H
#define _PCPWM_H

#include "gpio.h"                           //we use gpio functions

//hardware configuration
//end hardware configuration

//global defines
#define PCPWM_PS1x			0x00					//prescaler = 1:1
#define PCPWM_PS4x			0x01					//prescaler = 4:1
#define PCPWM_PS16x			0x02					//prescaler = 16:1
#define PCPWM_PS64x			0x03					//prescaler = 64:1

#define pcpwm_getpr()		_pcpwm_pr
//global variables

void pcpwm_init(void);

//set pwm period - 14bit period recast to 12bits
void pcpwm_setpr(uint16_t prescaler, uint16_t period);

//get pwm period - 14bit period
uint16_t pcpwm_getpr(void);


//set pwm period for ch 0 - 14bit dc
void pcpwm_setdc0(uint16_t dc);

//set pwm period for ch 1 - 14bit dc
void pcpwm_setdc1(uint16_t dc);

//set pwm period for ch 2 - 14bit dc
void pcpwm_setdc2(uint16_t dc);

//set pwm period for ch 3 - 14bit dc
void pcpwm_setdc3(uint16_t dc);

#endif
