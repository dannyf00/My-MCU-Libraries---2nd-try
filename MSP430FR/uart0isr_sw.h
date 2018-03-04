#ifndef _UART0ISR_SW_H
#define _UART0ISR_SW_H

//Software UART
//timebase: TA0 CCR0..2 -> additional channels / different timers are possible
//user specified pin
//TX only.
//Supports concurrent transmission

//#include <msp430.h> 					//we use ccs/msp430
//msp430g2 launchpad
//msp430g2553 or msp430g2452
//msp430f2418 - proteus
//msp430fr5969
#include "gpio.h"						//we use gpio

//hardware configuration
//for uart0
#define UART0_PORT		PORT2
#define UART0_DDR		UART0_PORT
#define UART0_TX		(1<<0)			//UART0_TX on P2.0

//for uart1
#define UART1_PORT		PORT2
#define UART1_DDR		UART1_PORT
#define UART1_TX		(1<<0)			//UART1_TX on P2.0

//for uart2
#define UART2_PORT		PORT2
#define UART2_DDR		UART2_PORT
#define UART2_TX		(1<<0)			//UART2_TX on P2.0
//end hardware configuration

//global defines
#define F_UART			F_CPU

//uart0
//1-start bit, 8-data bit, 1-stop bit, no parity
void uart0_init(uint32_t bps);			//initialize the uart
void uart0_put(char ch);				//send a char
void uart0_puts(char *str);				//send a string - no empty string, null-terminated
char uart0_busy(void);					//test for busy SIGNAL

//uart1
//1-start bit, 8-data bit, 1-stop bit, no parity
void uart1_init(uint32_t bps);			//initialize the uart
void uart1_put(char ch);				//send a char
void uart1_puts(char *str);				//send a string - no empty string, null-terminated
char uart1_busy(void);					//test for busy SIGNAL

//uart2
//1-start bit, 8-data bit, 1-stop bit, no parity
void uart2_init(uint32_t bps);			//initialize the uart
void uart2_put(char ch);				//send a char
void uart2_puts(char *str);				//send a string - no empty string, null-terminated
char uart2_busy(void);					//test for busy SIGNAL

#endif
