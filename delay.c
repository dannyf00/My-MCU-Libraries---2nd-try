//simple example
/* Includes ------------------------------------------------------------------*/
//#include <iostm8.h>
//#include <stdio.h>                          //because we used printf
#include "gpio.h"				//we use _nop_()
#include "delay.h"
/* Global variables ----------------------------------------------------------*/

//#define _DLY_MS				158				//delay for EWAVR (USB1286)
//#define _DLY_MS				40				//delay for WINAVR debug mode(USB1286, no optimization)
//#define _DLY_MS				158				//delay for WINAVR release (USB1286)
//#define _DLY_MS				120				//delay for C51
//#define _DLY_MS				329				//delay for avr
//#define _DLY_MS				160				//delay for PIC18F46K20 @ 4Mhz
//#define _DLY_MS				200				//delay for PIC16F886
//#define _DLY_MS				(93)			//delay for PIC24 @ 2Mhz
#define _DLY_MS					(95*2+5)			//delay for PIC24F @ 2Mhz
//#define _DLY_MS				984				//delay for LPC2106
//#define _DLY_MS				226				//lpc1343 on keil

//delay routines
void delay(volatile unsigned char dly) {              //waste some cycle
	while (dly--)
		continue;
}

//delay_us(1000) = 10ms
//delay_us(1) = 10us
void delay_us(volatile unsigned short us) {            //delay a us
	delay(us);						//delay the lsb
	us = us >> 8;					//retain the msb
	while (us--) delay(0xff);		//delay the msb
}

void delay_ms(volatile unsigned short ms) {	//delay ms
	while (ms--) delay_us(F_CPU / 1000000ul * _DLY_MS);
}
