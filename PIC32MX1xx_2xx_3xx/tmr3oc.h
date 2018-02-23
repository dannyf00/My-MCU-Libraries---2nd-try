#ifndef _TMR3OC_H
#define _TMR3OC_H

//usring output compare channels 1..5 as timers
//timer3 as the time base

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines
//tmr1 prescaler
#define TMR3_PS1x			0x00
#define TMR3_PS2x			0x01
#define TMR3_PS4x			0x02
#define TMR3_PS8x			0x03
#define TMR3_PS16x			0x04
#define TMR3_PS32x			0x05
#define TMR3_PS64x			0x06
#define TMR3_PS256x			0x07
#define TMR3_PSMASK			TMR3_PS256x

//rtc timing constant
#define TMR_10000ms			(TMR_ms * 10000)	//1ms * 10000
#define TMR_5000ms			(TMR_ms * 5000)		//1ms * 5000
#define TMR_2000ms			(TMR_ms * 2000)		//1ms * 2000
#define TMR_1000ms			(TMR_ms * 1000)		//1ms * 1000
#define TMR_500ms			(TMR_ms * 500)		//1ms * 1000
#define TMR_200ms			(TMR_ms * 200)		//1ms * 200
#define TMR_100ms			(TMR_ms * 100)		//1ms * 100
#define TMR_50ms			(TMR_ms * 50)		//1ms * 50
#define TMR_20ms			(TMR_ms * 20)		//1ms * 20
#define TMR_10ms			(TMR_ms * 10)		//1ms * 10
#define TMR_5ms				(TMR_ms * 5)		//1ms * 5
#define TMR_2ms				(TMR_ms * 2)		//1ms * 2
#define TMR_1ms				(TMR_ms * 1)		//1ms * 1
#define TMR_ms				(F_PB / 1000)		//ms definition

//global variables

//tmr3 isr overflow 


//time base + overflow interrupt
void tmr3_init(uint8_t ps);					//initialize the timer2 (16bit)
void tmr3_act(void (*isr_ptr)(void));		//activate the isr handler

//routines for compare ch 1..5
void tmr31_setpr(uint16_t pr);				//configure output compare 1
void tmr31_act(void (*isr_ptr)(void));		////install user handler

void tmr32_setpr(uint16_t pr);				//configure output compare 2
void tmr32_act(void (*isr_ptr)(void));		////install user handler

void tmr33_setpr(uint16_t pr);				//configure output compare 3
void tmr33_act(void (*isr_ptr)(void));		////install user handler

void tmr34_setpr(uint16_t pr);				//configure output compare 4
void tmr34_act(void (*isr_ptr)(void));		////install user handler

void tmr35_setpr(uint16_t pr);				//configure output compare 5
void tmr35_act(void (*isr_ptr)(void));		////install user handler

#endif
