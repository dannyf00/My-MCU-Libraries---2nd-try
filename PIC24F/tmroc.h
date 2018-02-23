#ifndef _TMROC_H
#define _TMROC_H

//using unused output compare channels on pic24fj64ga002 as timers

#include "gpio.h"

//hardware configuration
#ifndef USE_TMR2
#define USE_TMR2					//use tmr2 as timebase. comment out to use tmr3
#endif
//end hardware configuration

//global defines
//tmr prescaler
#define TMR_PS1x			0x00
#define TMR_PS8x			0x01
#define TMR_PS64x			0x02
#define TMR_PS256x			0x03
#define TMR_PSMASK			TMR_PS256x				//mask for tmr_ps

//rest tmr output compare
void tmroc_init1(uint16_t ps);
void tmroc_init2(uint16_t ps);
void tmroc_init3(uint16_t ps);
void tmroc_init4(uint16_t ps);
void tmroc_init5(uint16_t ps);

//set output compare channel period
void tmroc_setpr1(uint16_t pr);
//install user handler
void tmroc_act1(void (*isrptr)(void));

//set output compare channel period
void tmroc_setpr2(uint16_t pr);
//install user handler
void tmroc_act2(void (*isrptr)(void));

//set output compare channel period
void tmroc_setpr3(uint16_t pr);
//install user handler
void tmroc_act3(void (*isrptr)(void));

//set output compare channel period
void tmroc_setpr4(uint16_t pr);
//install user handler
void tmroc_act4(void (*isrptr)(void));

//set output compare channel period
void tmroc_setpr5(uint16_t pr);
//install user handler
void tmroc_act5(void (*isrptr)(void));

#endif
