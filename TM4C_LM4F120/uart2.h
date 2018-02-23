#ifndef _UART2_H
#define _UART2_H

#include "gpio.h"						//we use gpio

//hardware configuration
//comment out if not used
//U2TX=PD7, U2RX=PD6
#define UART2_TX()			do {GPIOD->DEN |= (1<<7); GPIOD->AFSEL |= (1<<7); GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (7*4))) | (0x01 << (7*4));} while (0)
#define UART2_RX()			do {GPIOD->DEN |= (1<<6); GPIOD->AFSEL |= (1<<6); GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (6*4))) | (0x01 << (6*4));} while (0)
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
void uart2_init(uint32_t uart_bps);

//send a char
void uart2_put(char ch);

//send a string
void uart2_puts(char * str);

//read usartx status
//1 if usartx is busy
//0 if usartx is available for new transmission
char uart2_busy(void);

//check for rx availability
char uart2_available(void);

#endif /* UART0ISR_H_ */
