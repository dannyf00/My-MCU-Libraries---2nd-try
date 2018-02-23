#ifndef _PWM_SW_H
#define _PWM_SW_H

#include "gpio.h"

//hardware configuration
#define PWM_PORT		PORTB
#define PWM_DDR			TRISB
#define PWM_CNT			4				//number of pwm channels
//end hardware configuration

//global defines
//tmr0 prescaler
#define TMR0_PS_1x			0xff
#define TMR0_PS_2x			0x00
#define TMR0_PS_4x			0x01
#define TMR0_PS_8x			0x02
#define TMR0_PS_16x			0x03
#define TMR0_PS_32x			0x04
#define TMR0_PS_64x			0x05
#define TMR0_PS_128x		0x06
#define TMR0_PS_256x		0x07

typedef struct {
	unsigned char dc;					//pwm duty cycle
	unsigned char pin;					//pwm pin
} PWM_T;

//global variables

void pwm_isr(void);					//isr for tmr0

//example isr
//void interrupt isr(void) {
//	//tmr0
//	if (TMR0IF) pwm_isr();
//}

void pwm_isr(void);
	
//reset pwm
void pwm_init(unsigned char prescaler, unsigned char period);

//set pwm duty cycle
void pwm_setdc(unsigned char ch, unsigned char dc, unsigned char pin);

#define pwm0_setdc(pin, dc)		pwm_setdc(0, dc, pin)
#define pwm1_setdc(pin, dc)		pwm_setdc(1, dc, pin)
#define pwm2_setdc(pin, dc)		pwm_setdc(2, dc, pin)
#define pwm3_setdc(pin, dc)		pwm_setdc(3, dc, pin)
#define pwm4_setdc(pin, dc)		pwm_setdc(4, dc, pin)
#define pwm5_setdc(pin, dc)		pwm_setdc(5, dc, pin)
#define pwm6_setdc(pin, dc)		pwm_setdc(6, dc, pin)
#define pwm7_setdc(pin, dc)		pwm_setdc(7, dc, pin)

#endif
