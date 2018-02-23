#ifndef _UARTXISR_H
#define _UARTXISR_H

//#include "stm32f10x_rcc.h"				//we use rcc
//#include "stm32f10x_tim.h"				//we use timer

//hardware configuration
//softuart pin definitions
#define UART_PORT		PORTC
#define UART_DDR		TRISC
#define UART_TX			(1<<2)		//tx pin

#define UART_SET(tx)	IO_SET(UART_PORT, tx)
#define UART_CLR(tx)	IO_CLR(UART_PORT, tx)

//pick the timer to be used
//#define UART_TIM		TIM3
#define tmrx_init		tmr1_init
#define tmrx_act		tmr1_act
#include "tmr1.h"						//we use timer
//end hardware configuration

//insert into the isr
#define UARTX_TX_ISR()				\
	if (TMR1IF) {					\
		TMR1H = tmr1_offset>>8;		\
		TMR1L = tmr1_offset/* & 0x00ff*/;	\
		TMR1IF = 0;					\
		_tmr1_isr_ptr();			\
	}	

//uartx protocol
//1 start bit
//8 data bits
//1 stop bit
//lsb first
#define UART_SR(dat)		(0x0200 | ((dat) << 1) | 0x0000)	//form the uart shift register. 1 start bit (low), 8 data bits, 1 stop bit (high), lsb first

//global defines
//define baud rates
#define UART_BR_300			300ul		//baudrate=300 - it overflows under 24Mhz F_CPU
#define UART_BR_600			600ul		//baudrate=600
#define UART_BR_1200		1200ul		//baudrate=1200
#define UART_BR_2400		2400ul		//baudrate=2400
#define UART_BR_4800		4800ul		//baudrate=4800
#define UART_BR_9600		9600ul		//baudrate=9600
#define UART_BR_19200		19200ul		//baudrate=19200
#define UART_BR_38400		38400ul		//baudrate=38400
#define UART_BR_57600		57600ul		//baudrate=57600 - upper limit for 24Mhz F_CPU
#define UART_BR_115200		115200ul	//baudrate=115200


//global variables
//softuart_isr handler
//install this in the timer
void uartx_isr(void);

//reset softuart_isr
void uartx_init(unsigned long baud);

//transmit a string
void uartx_puts(unsigned char * str);

//if uart is busy, return 1
unsigned char uartx_busy(void);

#endif
