#ifndef UART5ISR_SW_H_INCLUDED
#define UART5ISR_SW_H_INCLUDED

//software uart, timer5 for timebase, tx only
//limitations:
//1. TX only, interrupt-driven
//2. TIMER5 is used
//3. MCU needs to run at at least 1Mhz: up to 9600bps@2Mhz tested to work on internal rc oscillator
//4. Not all frequencies are equal / supported: F_CPU up to 8*256*UART baud rate
//5. Be mindful of baud rate errors
//@1Mhz: 2400bps confirmed to work
//@2Mhz: 9600bps configrmed to work

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines

//global variables
//look-up table for 4 bit reversal, in place
//usage:
//in main.c, declare an isr
//in the ISR:
//  if (TMR5IE && TMR5IF) tmr5_isr();	//TMR5IF is cleared inside tmr5_isr()
//timer5/uart overflow isr
void tmr5_isr(void);

//rest uart using usi + timer0 as clock
//1-start bit, 1-stop bit, 8-data
void uart5_init(uint32_t bps);
//send a char
void uart5_put(char ch);

//send a string
void uart5_puts(char *str);

char uart5_busy(void);

#endif // UART0_USI_H_INCLUDED
