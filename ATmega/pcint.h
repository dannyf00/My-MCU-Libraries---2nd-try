#ifndef PCINT_H_INCLUDED
#define PCINT_H_INCLUDED

#include "gpio.h"
#include "delay.h"							//we use software delays

//hardware configuration
#define PCINT0_PORT			PORTB
#define PCINT0_DDR			DDRB
#define PCINT0_PINs			(1<<4)			//pcint0..7

#define PCINT1_PORT			PORTC
#define PCINT1_DDR			DDRC
#define PCINT1_PINs			(1<<4)			//pcint8..15

#define PCINT2_PORT			PORTD
#define PCINT2_DDR			DDRD
#define PCINT2_PINs			(1<<4)			//pcint16..23
//end hardware configuration

//global defines


//global variables
//reset pcint isr
void pcint0_init(void);
//activate pcint0
void pcint0_act(void (*isr_ptr)(void));

//reset pcint isr
void pcint1_init(void);
//activate pcint1
void pcint1_act(void (*isr_ptr)(void));

//reset pcint isr
void pcint2_init(void);
//activate pcint0
void pcint2_act(void (*isr_ptr)(void));

#endif // PCINT_H_INCLUDED
