#ifndef UART3_H_
#define UART3_H_
//uart driver for LPC17xx - non-interrupt driven

#include "gpio.h"						//we use gpio
//#define F_UART							14745600ul			//F_UART running at 1:1 pcksel

//initialize uart
void uart3_init(uint32_t bps);			//initialize uart
void uart3_put(char ch);				//set a char
void uart3_puts(char *str);				//send a string
char uart3_get(void);					//read a char
uint8_t uart3_available(void);			//char available to be read from uart
uint8_t uart3_busy(void);				//uart is busy

#endif /* uart3_H_ */
