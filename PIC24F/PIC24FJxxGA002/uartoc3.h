#ifndef UARTOC3_H_INCLUDED
#define UARTOC3_H_INCLUDED

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines

//global variables

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

#endif /* UARTOC1_H_INCLUDED */
