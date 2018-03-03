#ifndef UART2AISR_SW_H_INCLUDED
#define UART2AISR_SW_H_INCLUDED

//software uart, timer0 for timebase, tx only
//limitations:
//1. TX only, interrupt-driven
//2. TIMER0 is used
//3. MCU needs to run at at least 8Mhz: up to 38400bps tested to work on internal rc oscillator
//4. Not all frequencies are equal / supported: F_CPU up to 8*256*UART baud rate
//5. Be mindful of baud rate errors
//@1Mhz: 2400bps confirmed to work
//@8Mhz: 38400bps configrmed to work

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines

//global variables
//look-up table for 4 bit reversal, in place
//rest uart using usi + timer0 as clock
//WGM02..0=0b010
//1-start bit, 1-stop bit, 8-data
void uart2a_init(uint32_t bps);
//send a char
void uart2a_put(char ch);

//send a string
void uart2a_puts(char *str);

char uart2a_busy(void);

#endif // UART0_USI_H_INCLUDED
