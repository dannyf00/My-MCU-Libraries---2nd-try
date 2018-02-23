#ifndef __TMR0_H
#define __TMR0_H

#include "gpio.h"                       //we use f_cpu

//for calling programs
//extern void (*_tmr0_isr_ptr)(void);				//isr handler
//extern unsigned char tmr0_offset;				//tmr0 offset
extern void tmr0_isr(void);

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

//timing constant
#define TMR_ms				(F_CPU / 1000)		//ms definition
#define TMR_1ms				(TMR_ms * 1)		//1ms definition
#define TMR_2ms				(TMR_ms * 2)		//2ms definition
#define TMR_5ms				(TMR_ms * 5)		//5ms definition
#define TMR_10ms			(TMR_ms * 10)		//10ms definition
#define TMR_20ms			(TMR_ms * 20)		//20ms definition
#define TMR_50ms			(TMR_ms * 50)		//50ms definition

//for compatibility
#define TMR0IF				T0IF
#define TMR0IE				T0IE

//initialize the timer
void tmr0_init(unsigned char prescaler);

//activate the isr handler
void tmr0_act(void (*isr_ptr)(void));

#endif
