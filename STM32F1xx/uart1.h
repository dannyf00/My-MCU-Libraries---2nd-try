#ifndef _UART1_H
#define _UART1_H

#include "gpio.h"							//we use gpio

void uart1_init(uint32_t baudrate);
//uart1 send a char
void uart1_put(char dat);
//uart1 print a string
void uart1_puts(char *str);
//uart1 returns a char
char uart1_get(void);
//test if uart1 receiver has data available
//return true if transmission on uart1 has completed
uint8_t uart1_available(void);
//test if uart1 is busy
uint8_t uart1_busy(void);

#endif
