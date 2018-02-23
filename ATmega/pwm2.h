#ifndef PWM2_H_INCLUDED
#define PWM2_H_INCLUDED

#include "gpio.h"

//hardware configuration
#define PWM2A_PORT		PORTB
#define PWM2A_DDR		DDRB
#define PWM2A_PIN		(1<<4)			//OC1A on PB1

#define PWM2B_PORT		PORTD
#define PWM2B_DDR		DDRD
#define PWM2B_PIN		(1<<1)			//OC1A on PB4

//end hardware configuration

//global defines
#define TMR2_PS_NOCLK	0x00			//no clock
#define TMR2_PS_1x		0x01			//prescaler settings
#define TMR2_PS_8x		0x02
#define TMR2_PS_64x		0x03
#define TMR2_PS_256x	0x04
#define TMR2_PS_1024x	0x05
#define TMR2_EXT_N		0x06
#define TMR2_EXT_P		0x07

//global variables

//reset pwm on tmr1, 10-bit, channel a
void pwm2_setpr(unsigned char ps, unsigned char period);

//reset pwm on tmr1, 10-bit, channel a
void pwm2a_init(void);

//reset pwm on tmr1, 10-bit, channel b
void pwm2b_init(void);

//set pwm on tmr1, channel a
void pwm2a_setdc(unsigned char dc);

//set pwm on tmr1, channel b
void pwm2b_setdc(unsigned char dc);

#endif // PWM1_H_INCLUDED
