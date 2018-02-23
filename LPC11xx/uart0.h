#ifndef UART0_H_
#define UART0_H_
//uart driver for LPC17xx - non-interrupt driven

#include "gpio.h"						//we use gpio
//#define F_UART							14745600ul			//F_UART running at 1:1 pcksel

//initialize uart
void uart0_init(uint32_t bps);			//initialize uart
void uart0_put(char ch);				//set a char
void uart0_puts(char *str);				//send a string
char uart0_get(void);					//read a char
uint8_t uart0_available(void);			//char available to be read from uart
uint8_t uart0_busy(void);				//uart is busy

#endif /* UART0_H_ */
