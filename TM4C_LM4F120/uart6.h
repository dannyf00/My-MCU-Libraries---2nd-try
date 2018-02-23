#ifndef _UART6_H
#define _UART6_H

#include "gpio.h"						//we use gpio

//hardware configuration
//comment out if not used
//U6TX=PD5, U6RX=PD4
#define UART6_TX()			do {GPIOD->DEN |= (1<<5); GPIOD->AFSEL |= (1<<5); GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (5*4))) | (0x01 << (5*4));} while (0)
#define UART6_RX()			do {GPIOD->DEN |= (1<<4); GPIOD->AFSEL |= (1<<4); GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (4*4))) | (0x01 << (4*4));} while (0)
//end hardware configuration

//global defines
#define F_UART				F_CPU

//define baud rates
#define UART_BR_300			300ul		//baud rate=300
#define UART_BR_600			600ul		//baud rate=600
#define UART_BR_1200		1200ul		//baud rate=1200
#define UART_BR_2400		2400ul		//baud rate=2400
#define UART_BR_4800		4800ul		//baud rate=4800
#define UART_BR_9600		9600ul		//baud rate=9600
#define UART_BR_19200		19200ul		//baud rate=19200
#define UART_BR_38400		38400ul		//baud rate=38400
#define UART_BR_57600		57600ul		//baud rate=57600
#define UART_BR_115200		115200ul	//baud rate=115200

//global variables

//reset the usart module
void uart6_init(uint32_t uart_bps);

//send a char
void uart6_put(char ch);

//send a string
void uart6_puts(char * str);

//read usartx status
//1 if usartx is busy
//0 if usartx is available for new transmission
char uart6_busy(void);

//check for rx availability
char uart6_available(void);

#endif /* UART0ISR_H_ */
