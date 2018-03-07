#ifndef _PWMTA1_H
#define _PWMTA1_H

#include "gpio.h"							//using msp430

//hardware configuration
//other pin remapping possible
#define PWM_TA1CH1()				do {IO_OUT(P1DIR, 1<<2); IO_SET(P1SEL, 1<<2); /*IO_AF1(PORT1, 1<<2);*/} while (0)	//CH1 output on P1.2, AF1
#define PWM_TA1CH2()				do {IO_OUT(P1DIR, 1<<3); IO_SET(P1SEL, 1<<3); /*IO_AF1(PORT1, 1<<3);*/} while (0)	//CH2 output on P1.3, AF1
//end hardware configuration

//global defines

//global variables
//prescaler definitions
//prescaler definitions
#define TMRA_PS1x		(0x00<<6)	//prescaler @ 1x
#define TMRA_PS2x		(0x01<<6)	//prescaler @ 2x
#define TMRA_PS4x		(0x02<<6)	//prescaler @ 4x
#define TMRA_PS8x		(0x03<<6)	//prescaler @ 8x
//expanded divider definitions
#define TMRA_EX1x		0x00		//expansion divider
#define TMRA_EX2x		0x01		//expansion divider
#define TMRA_EX3x		0x02		//expansion divider
#define TMRA_EX4x		0x03		//expansion divider
#define TMRA_EX5x		0x04		//expansion divider
#define TMRA_EX6x		0x05		//expansion divider
#define TMRA_EX7x		0x06		//expansion divider
#define TMRA_EX8x		0x07		//expansion divider


//rtc timing constant
/*
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
*/
//initialize timer_a, free-running
//top at CCR0, up or up/down mode
void pwmta1_init(uint16_t ps, uint16_t pr);

//set tmra0 duty cycle - not all channels are available on all timers / chips
void pwmta1_setdc1(uint16_t dc);		//TIMERA1->CCR1 = (dc)
void pwmta1_setdc2(uint16_t dc);		//TIMERA1->CCR2 = (dc)
void pwmta1_setdc3(uint16_t dc);		//TIMERA1->CCR2 = (dc)
void pwmta1_setdc4(uint16_t dc);		//TIMERA1->CCR2 = (dc)
void pwmta1_setdc5(uint16_t dc);		//TIMERA1->CCR2 = (dc)
void pwmta1_setdc6(uint16_t dc);		//TIMERA1->CCR2 = (dc)

#endif
