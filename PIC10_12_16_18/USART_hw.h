#ifndef USART_HW_H_
#define USART_HW_H_

#include <htc.h>				//we use picc
#include "gpio.h"				//we use f_cpu

//#define Mhz					000000ul	//suffix for Mhz
//hardware configuration
#define F_UART				(F_CPU * 4)	//8Mhz		//crystal frequency
//end hardware configuration

//uart baud rates
#define UART_BR_300			300ul		//buadrate=300
#define UART_BR_600			600ul		//buadrate=600
#define UART_BR_1200		1200ul		//buadrate=1200
#define UART_BR_2400		2400ul		//buadrate=2400
#define UART_BR_4800		4800ul		//buadrate=4800
#define UART_BR_9600		9600ul		//buadrate=9600
#define UART_BR_19200		19200ul		//buadrate=19200
#define UART_BR_38400		38400ul		//buadrate=38400
#define UART_BR_57600		57600ul		//buadrate=57600
#define UART_BR_115200		115200ul	//buadrate=115200

//initiate the hardware usart
void usart_init(unsigned long baud_rate);

void usart_putch(unsigned char ch);

void usart_puts(const unsigned char *str);

/*

Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux

*/

void usart_putline(const unsigned char *ln);

//read a char from usart
unsigned char usart_getch(void);

#endif
