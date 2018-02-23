#ifndef _SRVO1_H
#define _SRVO1_H

#include "gpio.h"                           //we use gpio functions

	
//global variables
//extern SRVO_TypeDef srvos[SRVO_CNT+1];

//servor isr to be included in the interrupt routine
//example:
//void interrupt isr(void) {
//	srvo1_isr();							//insert tmr1 isr here
//	...										//other tasks
//}
void srvo1_isr(void);

//initialize the servo using tmr1
//count on internal clock, 1:1 prescaler
void srvo1_init(void);

//change servo parameters
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo1_set(uint8_t sindex, uint8_t pin, uint16_t pr);


//change servo parameters - pin
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo1_setpin(uint8_t sindex, uint8_t pin);


//change servo parameters - period
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo1_setpr(uint8_t sindex, /*uint8_t pin, */uint16_t pr);

#endif
