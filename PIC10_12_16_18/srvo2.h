#ifndef _SRVO2_H
#define _SRVO2_H

//servo driver user timer2. 
//assumptions:
//1. F_CPU = 1Mhz
//2. servo not sensitive to length of off-period: 10ms - 20ms

#include "gpio.h"                           //we use gpio functions
//#include "delay.h"                         //we use software delays

//global variables
//extern SRVO_TypeDef srvos[SRVO_CNT+1];

//servor isr to be included in the interrupt routine
//example:
//void interrupt isr(void) {
//	srvo2_isr();							//insert tmr2 isr here
//	...										//other tasks
//}
void srvo2_isr(void);


//initialize the servo using tmr2
//count on internal clock, 4:1 prescaler (4 to achieve a maximum period of 8*256*1us =~2ms)
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

#endif
