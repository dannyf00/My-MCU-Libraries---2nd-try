#ifndef UART1_H_
#define UART1_H_
//uart driver for LPC21xx - non-interrupt driven

#include "gpio.h"						//we use gpio
//#define F_UART							14745600ul			//F_UART running at 1:1 pcksel

//initialize uart
void uart1_init(uint32_t bps);			//initialize uart
void uart1_put(char ch);				//set a char
void uart1_puts(char *str);				//send a string
char uart1_get(void);					//read a char
uint8_t uart1_available(void);			//char available to be read from uart
uint8_t uart1_busy(void);				//uart is busy

#endif /* UART0_H_ */
