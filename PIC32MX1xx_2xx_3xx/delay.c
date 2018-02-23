//simple example
/* Includes ------------------------------------------------------------------*/
//#include <iostm8.h>
//#include <stdio.h>                          //because we used printf
#include "delay.h"
/* Global variables ----------------------------------------------------------*/

//#define _DLY_MS				158				//delay for EWAVR (USB1286)
//#define _DLY_MS				40				//delay for WINAVR debug mode(USB1286, no optimization)
//#define _DLY_MS				158				//delay for WINAVR release (USB1286)
//#define _DLY_MS				120				//delay for C51
//#define _DLY_MS				329				//delay for avr
//#define _DLY_MS				160				//delay for PIC18F46K20 @ 4Mhz
//#define _DLY_MS				200				//delay for PIC16F886
//#define _DLY_MS				(93)            //delay for PIC24 @ 2Mhz
#define _DLY_MS					(144 * 100/12*2/3)            //delay for PIC32F @ 1Mhz (1Mhz Crystal simulated. Optimization 0, xc32), to be divided by 10
//#define _DLY_MS				984				//delay for LPC2106
//#define _DLY_MS				226				//lpc1343 on keil

//delay routines
void delay(uint16_t dly) {              //waste some cycle
	while (dly--)
            //continue;								//use 95*2+6
            NOP();									//use 164
            //LATB;
}

//delay_us(1000) = 10ms
//delay_us(1) = 10us
void delay_us(uint32_t us) {            //delay a us
	delay(us);						//delay the lsb
	us = us >> 16;					//retain the msb
	while (us--) delay(0xffff);		//delay the msb
}

void delay_ms(uint32_t ms) {	//delay ms
	while (ms--) delay_us(F_CPU / 1000 * _DLY_MS / 10 / 1000);
}
