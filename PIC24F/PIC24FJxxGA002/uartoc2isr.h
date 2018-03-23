#ifndef UARTOC2ISR_H_INCLUDED
#define UARTOC2ISR_H_INCLUDED

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines

//global variables

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

#endif /* UARTOC1_H_INCLUDED */
