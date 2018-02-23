//driving multiple servos off TIMER2 on ATMEGA328p
//assumptions:
//1. 1Mhz F_CPU
//2. servos not sensitive to duration of off state

#ifndef SRVO2_H_INCLUDED
#define SRVO2_H_INCLUDED

//#include <avr/io.h>							//we use gcc-avr
#include "gpio.h"
//#include "delay.h"							//we use software delays

//hardware configuration
//#define SRVO_PORT			PORTB
//#define SRVO_DDR			DDRB
//#define SRVO2_CNT			8				//srvo counts
//end hardware configuration

//global defines

//global variables
//extern SRVO2_TypeDef srvos[SRVO2_CNT+1];

//servor isr to be included in the interrupt routine

//initialize the servo using tmr2
//count on internal clock, 8:1 prescaler (4 to achieve a maximum period of 8*256*1us =~2ms)
void srvo2_init(void);

//change servo parameters
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo2_set(uint8_t sindex, uint8_t pin, uint16_t pr);

//change servo parameters - pin
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo2_setpin(uint8_t sindex, uint8_t pin);

//change servo parameters - period
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo2_setpr(uint8_t sindex, /*uint8_t pin, */uint16_t pr);

#endif // SRVO2_H_INCLUDED
