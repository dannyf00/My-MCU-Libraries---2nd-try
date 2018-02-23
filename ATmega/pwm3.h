#ifndef PWM3_H_INCLUDED
#define PWM3_H_INCLUDED

#include "gpio.h"

//hardware configuration
#define PWM3A_PORT		PORTC
#define PWM3A_DDR		DDRC
#define PWM3A_PIN		(1<<6)			//OC1A on PB1

#define PWM3B_PORT		PORTC
#define PWM3B_DDR		DDRC
#define PWM3B_PIN		(1<<5)			//OC1A on PB4

#define PWM3C_PORT		PORTC
#define PWM3C_DDR		DDRC
#define PWM3C_PIN		(1<<4)			//OC1A on PB4
//end hardware configuration

//global variables

#define TMR3_PS_NOCLK	TMR3_PS_0x		//no clock
#define TMR3_PS_0x		0x00			//no clock
#define TMR3_PS_1x		0x01			//prescaler settings
#define TMR3_PS_8x		0x02
#define TMR3_PS_64x		0x03
#define TMR3_PS_256x	0x04
#define TMR3_PS_1024x	0x05
#define TMR3_EXT_N		0x06
#define TMR3_EXT_P		0x07

//reset pwm on tmr1, 10-bit, channel a
void pwm3_setpr(unsigned char ps, unsigned short period);

//reset pwm on tmr1, 10-bit, channel a
void pwm3a_init(void);

//reset pwm on tmr1, 10-bit, channel b
void pwm3b_init(void);

void pwm3c_init(void);

//set pwm on tmr1, channel a
void pwm3a_setdc(unsigned short dc);

//set pwm on tmr1, channel b
void pwm3b_setdc(unsigned short dc);

void pwm3c_setdc(unsigned short dc);


#endif // PWM3_H_INCLUDED
