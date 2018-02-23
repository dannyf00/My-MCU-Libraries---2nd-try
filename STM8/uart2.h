#ifndef _UART2_H
#define _UART2_H

#include "gpio.h"

//reset uart
void uart2_init(uint16_t BaudRate);
//get a char - blocking
//test uart1_available() before calling this function
char uart2_get(void);
//put a char - blocking
void uart2_put(char dat);
//put a string
void uart2_puts(char *str);
//test if there is data in uart1 receiver buffer
//return !0 if there is data in UART1->DR
char uart2_available(void);
//test if uart tx is in progress
//returns 1 if transmission buffer is full / uart1 busy
char uart2_busy(void);
#endif
