#ifndef UART2_H_
#define UART2_H_
//uart driver for LPC17xx - non-interrupt driven

#include "gpio.h"						//we use gpio
//#define F_UART							14745600ul			//F_UART running at 1:1 pcksel

//initialize uart
void uart2_init(uint32_t bps);			//initialize uart
void uart2_put(char ch);				//set a char
void uart2_puts(char *str);				//send a string
char uart2_get(void);					//read a char
uint8_t uart2_available(void);			//char available to be read from uart
uint8_t uart2_busy(void);				//uart is busy

#endif /* uart2_H_ */
