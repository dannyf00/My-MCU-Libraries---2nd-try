#ifndef PWM0_H_INCLUDED
#define PWM0_H_INCLUDED

#include "gpio.h"

//hardware configuration
#define PWM0A_PORT		PORTB
#define PWM0A_DDR		DDRB
#define PWM0A_PIN		(1<<0)			//OC0A on PB0

#define PWM0B_PORT		PORTB
#define PWM0B_DDR		DDRB
#define PWM0B_PIN		(1<<1)			//OC0B on PB1
//end hardware configuration

//global defines
#define TMR0_PS_NOCLK	0x00			//no clock
#define TMR0_PS_1x		0x01			//prescaler settings
#define TMR0_PS_8x		0x02
#define TMR0_PS_64x		0x03
#define TMR0_PS_256x	0x04
#define TMR0_PS_1024x	0x05
#define TMR0_EXT_N		0x06
#define TMR0_EXT_P		0x07

//global variables

//reset pwm on tmr1, 10-bit, channel a
void pwm0_setpr(unsigned char ps, unsigned char period);

//reset pwm on tmr1, 10-bit, channel a
void pwm0a_init(void);

//reset pwm on tmr1, 10-bit, channel b
void pwm0b_init(void);

//set pwm on tmr1, channel a
void pwm0a_setdc(unsigned char dc);

//set pwm on tmr1, channel b
void pwm0b_setdc(unsigned char dc);

#endif // PWM1_H_INCLUDED
