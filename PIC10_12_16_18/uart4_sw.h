#ifndef UART4_SW_H_INCLUDED
#define UART4_SW_H_INCLUDED

//software uart, timer4 for timebase, tx only
//limitations:
//1. TX only, polling
//2. TIMER4 is used
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

//tmr4 isr - needs to be inserted into main as isr
//usage:
//in main.c, declare an isr
//in the ISR:
//  if (TMR4IE && TMR4IF) tmr4_isr();	//TMR4IF is cleared inside tmr4_isr()
void tmr4_isr(void);

//look-up table for 4 bit reversal, in place
//rest uart using usi + timer4 as clock
//1-start bit, 1-stop bit, 8-data
void uart4_init(uint32_t bps);
//send a char
void uart4_put(char ch);

//send a string
void uart4_puts(char *str);

char uart4_busy(void);

#endif // UART0_USI_H_INCLUDED
