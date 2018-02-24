#ifndef _TMRA0_H
#define _TMRA0_H

#include "gpio.h"							//using msp430

//hardware configuration
//end hardware configuration

//global defines

//global variables
//prescaler definitions
#define TMRA_PS1x		(0b00<<6)	//prescaler @ 1x
#define TMRA_PS2x		(0b01<<6)	//prescaler @ 2x
#define TMRA_PS4x		(0b10<<6)	//prescaler @ 4x
#define TMRA_PS8x		(0b11<<6)	//prescaler @ 8x
//expanded divider definitions
#define TMRA_EX1x		0b000		//expansion divider
#define TMRA_EX2x		0b001		//expansion divider
#define TMRA_EX3x		0b010		//expansion divider
#define TMRA_EX4x		0b011		//expansion divider
#define TMRA_EX5x		0b100		//expansion divider
#define TMRA_EX6x		0b101		//expansion divider
#define TMRA_EX7x		0b110		//expansion divider
#define TMRA_EX8x		0b111		//expansion divider


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
#define TMR_ms				(F_CPU / 1000)		//ms definition

//initialize timer_a, ccr0
void tmra0_init(uint16_t ps);

//set tmra0 period
void tmra0_setpr0(uint16_t pr);

//install user handler for timer_a, ccr0
void tmra0_act0(void (*isr_ptr)(void));

//initialize timer_a, ccr1
void tmra0_setpr1(uint16_t period);

//install user handler for timer_a, ccr1
void tmra0_act1(void (*isr_ptr)(void));

//initialize timer_a, ccr2
void tmra0_setpr2(uint16_t period);

//install user handler for timer_a, ccr2
void tmra0_act2(void (*isr_ptr)(void));

//initialize timer_a, ccr3
void tmra0_setpr3(uint16_t period);

//install user handler for timer_a, ccr3
void tmra0_act3(void (*isr_ptr)(void));

//initialize timer_a, ccr4
void tmra0_setpr4(uint16_t period);

//install user handler for timer_a, ccr4
void tmra0_act4(void (*isr_ptr)(void));

#endif
