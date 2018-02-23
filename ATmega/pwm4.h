#ifndef PWM4_H_INCLUDED
#define PWM4_H_INCLUDED

#include "gpio.h"

//hardware configuration
#define PWM4A_PORT		PORTC
#define PWM4A_DDR		DDRC
#define PWM4A_PIN		(1<<6)			//OC1A on PB1

#define PWM4B_PORT		PORTC
#define PWM4B_DDR		DDRC
#define PWM4B_PIN		(1<<5)			//OC1A on PB4

#define PWM4C_PORT		PORTC
#define PWM4C_DDR		DDRC
#define PWM4C_PIN		(1<<4)			//OC1A on PB4
//end hardware configuration

//global variables

#define TMR4_PS_NOCLK	TMR3_PS_0x		//no clock
#define TMR4_PS_0x		0x00			//no clock
#define TMR4_PS_1x		0x01			//prescaler settings
#define TMR4_PS_8x		0x02
#define TMR4_PS_64x		0x03
#define TMR4_PS_256x	0x04
#define TMR4_PS_1024x	0x05
#define TMR4_EXT_N		0x06
#define TMR4_EXT_P		0x07

//reset pwm on tmr1, 10-bit, channel a
void pwm4_setpr(unsigned char ps, unsigned short period);

//reset pwm on tmr1, 10-bit, channel a
void pwm4a_init(void);

//reset pwm on tmr1, 10-bit, channel b
void pwm4b_init(void);

void pwm4c_init(void);

//set pwm on tmr1, channel a
void pwm4a_setdc(unsigned short dc);

//set pwm on tmr1, channel b
void pwm4b_setdc(unsigned short dc);

void pwm4c_setdc(unsigned short dc);


#endif // PWM3_H_INCLUDED
