#ifndef PWM1_H_INCLUDED
#define PWM1_H_INCLUDED

#include "gpio.h"

//hardware configuration
#define PWM1A_PORT		PORTB
#define PWM1A_DDR		DDRB
#define PWM1A_PIN		(1<<1)			//OC1A on PB1
//#define PWM1nA_PIN		(1<<0)			//nOC1A on PB0 - uncomment to activate (code conditionally compiles)

#define PWM1B_PORT		PORTB
#define PWM1B_DDR		DDRB
#define PWM1B_PIN		(1<<4)			//OC1A on PB4
#define PWM1nB_PIN		(1<<3)			//nOC1A on PB3 - uncomment to activate (code conditionally compiles)

#define PWM1C_PORT		PORTB
#define PWM1C_DDR		DDRB
//#define PWM1C_PIN		(1<<7)			//OC1A on PB7
//#define PWM1nC_PIN		(1<<7)			//nOC1A on PB7 - uncomment to activate (code conditionally compiles)
//end hardware configuration

//global variables

#define TMR1_PS_NOCLK	TMR1_PS_0x		//no clock
#define TMR1_PS_0x		0x00			//no clock
#define TMR1_PS_1x		0x01			//prescaler settings
#define TMR1_PS_8x		0x02
#define TMR1_PS_64x		0x03
#define TMR1_PS_256x	0x04
#define TMR1_PS_1024x	0x05
#define TMR1_EXT_N		0x06
#define TMR1_EXT_P		0x07

//reset pwm on tmr1, 10-bit, channel a
void pwm1_setpr(unsigned char ps, unsigned short period);

//reset pwm on tmr1, 10-bit, channel a/b/c
void pwm1a_init(void);
void pwm1b_init(void);
void pwm1c_init(void);
void pll_enable(void);

//set pwm on tmr1, channel a/b/c
void pwm1a_setdc(unsigned short dc);
void pwm1b_setdc(unsigned short dc);
void pwm1c_setdc(unsigned short dc);

#endif // PWM1_H_INCLUDED
