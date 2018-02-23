#ifndef USART_HW_H_
#define USART_HW_H_

#include <htc.h>			//we use picc
#include "gpio.h"			//we use f_cpu

/*****************************************************************


*****************************************************************/
////#define Mhz					000000ul	//suffix for Mhz
#define F_UART				(F_CPU * 4)	//8Mhz		//crystal frequency
#define UART_BR_300		300ul		//buadrate=300
#define UART_BR_600		600ul		//buadrate=600
#define UART_BR_1200		1200ul		//buadrate=1200
#define UART_BR_2400		2400ul		//buadrate=2400
#define UART_BR_4800		4800ul		//buadrate=4800
#define UART_BR_9600		9600ul		//buadrate=9600
#define UART_BR_19200		19200ul		//buadrate=19200
#define UART_BR_38400		38400ul		//buadrate=38400
#define UART_BR_57600		57600ul		//buadrate=57600
#define UART_BR_115200		115200ul	//buadrate=115200

extern volatile unsigned char _UART_BUSY;			//uart busy flag. 0=uart not busy. 1=uart busy
extern volatile unsigned char *_UART_ptr;			//buffer pointer

//uart tx isr
//implemented with the macro below (UART_TX_ISR())
#if 0
	//uart tx section of the isr
	if (TXIF) {
		TXIF = 0;						//reset the flag
		TXREG = *_UART_ptr;			//load up the next char and start transmission. TXIF is reset by writing to TXREG
		if (*_UART_ptr) {				//end of the string not yet reached
			_UART_ptr++;				//increment to the next char
		} else {
			_UART_BUSY = 0;				//reset the flag
			TXIE = 0;					//no more transmission
		}
	}
#endif

//uart_tx marco, to be inserted into the isr
#define UART_TX_ISR()	if (TXIF) { \
		TXREG = *_UART_ptr;		\
		if (*_UART_ptr) {		\
			_UART_ptr++;		\
		} else { 				\
			_UART_BUSY = 0;		\
			TXIE = 0;			\
		} 						\
	}							

//initiate the hardware usart
void uart_init(unsigned long baud_rate);

//void usart_putch(unsigned char ch);

unsigned char uart_puts(unsigned char *str);

/*

Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux

*/

//void uart_putline(const unsigned char *ln);

//read a char from usart
//unsigned char uart_getch(void);

#endif
