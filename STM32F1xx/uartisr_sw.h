#ifndef _UARTISR_SW_H
#define _UARTISR_SW_H

//software uart using TIM2/3/4/5 Output compare channels
//not all timers available on a given chip

#include "gpio.h"					//we use F_CPU + gpio functions

//hardware configuration
#define UARTSW1_PORT	GPIOC
#define UARTSW1_TX		(1<<0)			//software uart tx pin

#define UARTSW2_PORT	GPIOC
#define UARTSW2_TX		(1<<1)			//software uart tx pin

#define UARTSW3_PORT	GPIOC
#define UARTSW3_TX		(1<<2)			//software uart tx pin

#define UARTSW4_PORT	GPIOC
#define UARTSW4_TX		(1<<3)			//software uart tx pin

#define UART_TMR		2				//supported TIMERs: 2/3/4/5 - not all timers available on a given chip
//end hardware configuration

//global defines

//global variables
//initialize software uart / CCP
//only TX is implemented
//time base TMRx, use output compare ch 1
void uartoc1_init(uint32_t bps);

//send a char
void uartoc1_put(char ch);

//send a string
void uartoc1_puts(char *str);

//test for busy SIGNAL
char uartoc1_busy(void);

//initialize software uart / CCP
//only TX is implemented
//time base TMRx, use output compare ch 1
void uartoc2_init(uint32_t bps);

//send a char
void uartoc2_put(char ch);

//send a string
void uartoc2_puts(char *str);

//test for busy SIGNAL
char uartoc2_busy(void);

//initialize software uart / CCP
//only TX is implemented
//time base TMRx, use output compare ch 1
void uartoc3_init(uint32_t bps);

//send a char
void uartoc3_put(char ch);

//send a string
void uartoc3_puts(char *str);

//test for busy SIGNAL
char uartoc3_busy(void);

//initialize software uart / CCP
//only TX is implemented
//time base TMRx, use output compare ch 1
void uartoc4_init(uint32_t bps);

//send a char
void uartoc4_put(char ch);

//send a string
void uartoc4_puts(char *str);

//test for busy SIGNAL
char uartoc4_busy(void);

#endif
