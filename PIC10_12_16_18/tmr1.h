#ifndef __TMR1_H
#define __TMR1_H

#include "gpio.h"                                               //we use f_cpu

//for calling programs
extern void (*_tmr1_isr_ptr)(void);				//isr handler
extern unsigned short tmr1_offset;				//tmr1 offset

//tmr1 prescaler
#define TMR1_PS1x			0x00
#define TMR1_PS2x			0x01
#define TMR1_PS4x			0x02
#define TMR1_PS8x			0x03

//timing constant
#define TMR_ms				(F_CPU / 1000)		//ms definition
#define TMR_1ms				(TMR_ms * 1)		//1ms definition
#define TMR_2ms				(TMR_ms * 2)		//2ms definition
#define TMR_5ms				(TMR_ms * 5)		//5ms definition
#define TMR_10ms			(TMR_ms * 10)		//10ms definition
#define TMR_20ms			(TMR_ms * 20)		//20ms definition
#define TMR_50ms			(TMR_ms * 50)		//50ms definition

//initialize the timer
void tmr1_init(unsigned char prescaler, unsigned short period);

//activate the isr handler
void tmr1_act(void (*isr_ptr)(void));

//tmr1 isr
void tmr1_isr(void);

#endif
