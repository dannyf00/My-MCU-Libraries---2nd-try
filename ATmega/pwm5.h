#ifndef PWM5_H_INCLUDED
#define PWM5_H_INCLUDED

#include "gpio.h"

//hardware configuration
#define PWM5A_PORT		PORTC
#define PWM5A_DDR		DDRC
#define PWM5A_PIN		(1<<6)			//OC1A on PB1

#define PWM5B_PORT		PORTC
#define PWM5B_DDR		DDRC
#define PWM5B_PIN		(1<<5)			//OC1A on PB4

#define PWM5C_PORT		PORTC
#define PWM5C_DDR		DDRC
#define PWM5C_PIN		(1<<4)			//OC1A on PB4
//end hardware configuration

//global variables

#define TMR5_PS_NOCLK	TMR3_PS_0x		//no clock
#define TMR5_PS_0x		0x00			//no clock
#define TMR5_PS_1x		0x01			//prescaler settings
#define TMR5_PS_8x		0x02
#define TMR5_PS_64x		0x03
#define TMR5_PS_256x	0x04
#define TMR5_PS_1024x	0x05
#define TMR5_EXT_N		0x06
#define TMR5_EXT_P		0x07

//reset pwm on tmr1, 10-bit, channel a
void pwm5_setpr(unsigned char ps, unsigned short period);

//reset pwm on tmr1, 10-bit, channel a
void pwm5a_init(void);

//reset pwm on tmr1, 10-bit, channel b
void pwm5b_init(void);

void pwm5c_init(void);

//set pwm on tmr1, channel a
void pwm5a_setdc(unsigned short dc);

//set pwm on tmr1, channel b
void pwm5b_setdc(unsigned short dc);

void pwm5c_setdc(unsigned short dc);


#endif // PWM3_H_INCLUDED
