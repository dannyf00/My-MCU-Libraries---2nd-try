#ifndef _USARTISR_H_
#define _USARTISR_H_

#include "gpio.h"						//we use F_CPU

/*****************************************************************


*****************************************************************/
//#define Mhz					000000ul	//suffix for Mhz
#define F_UART				(F_CPU * 4)	//8Mhz		//uart driven by Fosc = 4 * F_CPU
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

//for compatability
#define uart_put(c)			uart_putch(c)
#define uart_get()			uart_getch()

//test if uart transmitter is buy
//1=busy, 0=not busy
#define uart_busy()			(TXIE==1/*TRMT==0*/)		//TRMT=0 when TSR is full
#define uart_available()	(RCIF==1)		//RCIF=1 when data is received

//isr
void _UxTXISR(void);

//initiate the hardware usart
void uart_init(unsigned long baud_rate);

void uart_putch(char ch);

void uart_puts(char *str);

/*

Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux

*/

void uart_putline(char *ln);

//read a char from usart
unsigned char uart_getch(void);

#endif
