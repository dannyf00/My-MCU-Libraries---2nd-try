#ifndef _TMR2OC_H
#define _TMR2OC_H

//usring output compare channels 1..5 as timers
//timer2 as the time base

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines
//tmr1 prescaler
#define TMR2_PS1x			0x00
#define TMR2_PS2x			0x01
#define TMR2_PS4x			0x02
#define TMR2_PS8x			0x03
#define TMR2_PS16x			0x04
#define TMR2_PS32x			0x05
#define TMR2_PS64x			0x06
#define TMR2_PS256x			0x07
#define TMR2_PSMASK			TMR2_PS256x

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

//tmr2 isr overflow 


//time base + overflow interrupt
void tmr2_init(uint8_t ps);					//initialize the timer2 (16bit)
void tmr2_act(void (*isr_ptr)(void));		//activate the isr handler

//routines for compare ch 1..5
void tmr21_setpr(uint16_t pr);				//configure output compare 1
void tmr21_act(void (*isr_ptr)(void));		////install user handler

void tmr22_setpr(uint16_t pr);				//configure output compare 2
void tmr22_act(void (*isr_ptr)(void));		////install user handler

void tmr23_setpr(uint16_t pr);				//configure output compare 3
void tmr23_act(void (*isr_ptr)(void));		////install user handler

void tmr24_setpr(uint16_t pr);				//configure output compare 4
void tmr24_act(void (*isr_ptr)(void));		////install user handler

void tmr25_setpr(uint16_t pr);				//configure output compare 5
void tmr25_act(void (*isr_ptr)(void));		////install user handler

#endif
