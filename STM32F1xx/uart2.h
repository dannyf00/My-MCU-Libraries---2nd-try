#ifndef _UART2_H
#define _UART2_H

#include "gpio.h"							//we use gpio

void uart2_init(uint32_t baudrate);
//uart1 send a char
void uart2_put(char dat);
//uart1 print a string
void uart2_puts(char *str);
//uart1 returns a char
char uart2_get(void);
//test if uart1 receiver has data available
//return true if transmission on uart1 has completed
uint8_t uart2_available(void);
//test if uart1 is busy
uint8_t uart2_busy(void);

#endif
