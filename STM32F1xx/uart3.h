#ifndef _UART3_H
#define _UART3_H

#include "gpio.h"							//we use gpio

void uart3_init(uint32_t baudrate);
//uart1 send a char
void uart3_put(char dat);
//uart1 print a string
void uart3_puts(char *str);
//uart1 returns a char
char uart3_get(void);
//test if uart1 receiver has data available
//return true if transmission on uart1 has completed
uint8_t uart3_available(void);
//test if uart1 is busy
uint8_t uart3_busy(void);

#endif
