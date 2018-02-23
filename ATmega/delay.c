//simple example
/* Includes ------------------------------------------------------------------*/
//#include <iostm8.h>
//#include <stdio.h>                          //because we used printf
#include "gpio.h"				//we use _nop_()
/* Global variables ----------------------------------------------------------*/

//#define _DLY_MS				158				//delay for EWAVR (USB1286)
#define _DLY_MS					41				//release mode: delay for WINAVR debug mode(attiny85)
//#define _DLY_MS					3				//debug mode: delay for WINAVR debug mode(attiny85)
//#define _DLY_MS					3			//delay for WINAVR debug mode(USB1286, no optimization)
//#define _DLY_MS				158				//delay for WINAVR release (USB1286)
//#define _DLY_MS				120				//delay for C51
//#define _DLY_MS				329				//delay for avr
//#define _DLY_MS				89				//delay for PIC
//#define _DLY_MS				984				//delay for LPC2106
//#define _DLY_MS				226				//lpc1343 on keil

//delay routines
void delay(unsigned char dly) {              //waste some cycle
	while (dly--)
		continue;
}

//delay_us(1000) = 10ms
//delay_us(1) = 10us
void delay_us(unsigned short us) {            //delay a us
	delay(us);						//delay the lsb
	us = us >> 8;					//retain the msb
	while (us--) delay(0xff);		//delay the msb
}

void delay_ms(unsigned short ms) {	//delay ms
	while (ms--) delay_us(F_CPU / 1000000ul * _DLY_MS);
}
