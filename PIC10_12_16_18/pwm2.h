#ifndef _PWM2_H
#define _PWM2_H

#include "gpio.h"						//general gpio

//hardware configuration
//end hardware configuration

//global defines
//define timebase used for pwm function
#define PWM_USE_TMR1		1
#define PWM_USE_TMR2		2
#define PWM_USE_TMR3		3
#define PWM_USE_TMR4		4
#define PWM_USE_TMR5		5
#define PWM_USE_TMR6		6

//tmr1 prescaler

#define TMRx_PS_1x			0x00				//tmr2 post scaler
#define TMRx_PS_2x			0x10
#define TMRx_PS_3x			0x20
#define TMRx_PS_4x			0x30
#define TMRx_PS_5x			0x40
#define TMRx_PS_6x			0x50
#define TMRx_PS_7x			0x60
#define TMRx_PS_8x			0x70
#define TMRx_PS_9x			0x80
#define TMRx_PS_10x			0x90
#define TMRx_PS_11x			0xa0
#define TMRx_PS_12x			0xb0
#define TMRx_PS_13x			0xc0
#define TMRx_PS_14x			0xd0
#define TMRx_PS_15x			0xe0
#define TMRx_PS_16x			0xf0


//timing constant
#define TMRx_MLT_1x			0x00				//tmr2 multiplier = prescaler
#define TMRx_MLT_4x			0x01
#define TMRx_MLT_16x		0x02
#define TMRx_MLT_64x		0x03

//global variables


//initialize the pwm
void pwm2_init(void);
	
//set pwm parameters
//void pwm1_set(unsigned short period, unsigned short duty_cycle);

//set pwm period
void pwm2_setpr(unsigned char prescaler, unsigned short period);

//set pwm duty cycle parameters
void pwm2_setdc(unsigned short duty_cycle);

#endif
