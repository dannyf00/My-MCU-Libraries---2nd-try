//simple example
/* Includes ------------------------------------------------------------------*/
//#include <iostm8.h>
//#include <stdio.h>                          //because we used printf
//#include "gpio.h"				//we use _nop_()
#include "delay.h"
/* Global variables ----------------------------------------------------------*/

//#define _DLY_MS				158				//delay for EWAVR (USB1286)
//#define _DLY_MS				40				//delay for WINAVR debug mode(USB1286, no optimization)
//#define _DLY_MS				158				//delay for WINAVR release (USB1286)
//#define _DLY_MS				120				//delay for C51
//#define _DLY_MS				329				//delay for avr
//#define _DLY_MS				160				//delay for PIC18F46K20 @ 4Mhz
#if 	defined(_12F675)
		#define _DLY_MS				200				//delay for PIC12f675

#elif 	defined(_16F630) || defined(_16F676)
		#define _DLY_MS				88
	
#elif 	defined(_16F684)
		#define _DLY_MS				200				//for 16f684

#elif 	defined(_16F882) |  defined(_16F883) |  defined(_16F884) |  defined(_16F886) |  defined(_16F887)
		#define _DLY_MS				(139)		//for 16f886

#elif 	defined(_16F1933) || defined(_16F1934) || defined(_16F1936) || defined(_16F1937) || defined(_16F1938) || defined(_16F1939) || \
      	defined(_16LF1933) || defined(_16LF1934) || defined(_16LF1936) || defined(_16LF1937) || defined(_16LF1938) || defined(_16LF1939)
        #define _DLY_MS			90				//for 16f1936

#elif   defined (_18F13K22) || defined (_18F14K22) || defined (_18LF13K22) || defined (_18LF14K22)
		#define _DLY_MS			90				//for 18f13k/14k22
		
#elif	defined(_18F23K20) || defined(_18F24K20) || defined(_18F25K20) || defined(_18F26K20) || \
       	defined(_18F43K20) || defined(_18F44K20) || defined(_18F45K20) || defined(_18F46K20) || \
		defined(_18LF23K20) || defined(_18LF24K20) || defined(_18LF25K20) || defined(_18LF26K20) || \
       	defined(_18LF43K20) || defined(_18LF44K20) || defined(_18LF45K20) || defined(_18LF46K20)

		#define _DLY_MS			110				//for 18fxxK20
		
#elif   defined (_18F23K22) || defined (_18F24K22) || defined (_18F25K22) || defined (_18F26K22) || \
        defined (_18F43K22) || defined (_18F44K22) || defined (_18F45K22) || defined (_18F46K22) || \
        defined (_18LF23K22) || defined (_18LF24K22) || defined (_18LF25K22) || defined (_18LF26K22) || \
        defined (_18LF43K22) || defined (_18LF44K22) || defined (_18LF45K22) || defined (_18LF46K22)
        #define _DLY_MS			40				//for 18f25k22

#elif	defined(_18F6627) || defined(_18F6722) || defined(_18F8627) || defined(_18F8722) || \
		defined(_18F6527) || defined(_18F6622) || defined(_18F8527) || defined(_18F8622) || \
		defined(_18F6628) || defined(_18F6723) || defined(_18F8628) || defined(_18F8723)

		#define _DLY_MS				80
	
#elif	defined(_18F2585) || defined(_18F4585) || defined(_18F2680) || defined(_18F4680)

		#define _DLY_MS				40
	
#elif 	defined(_18F2420) || defined(_18F2520) || defined(_18F4420) || defined(_18F4520)

		#define _DLY_MS 			100 

#elif   defined (_18F2331) || defined (_18F2431) || defined (_18F4331) || defined (_18F4431)
		#define _DLY_MS				100				//default value

#else
//chip not defined
		#define _DLY_MS				200				//default value
		#warning delay routines not calibrated on this mcu!
#endif

//#define _DLY_MS				95				//delay for PIC24 @ 1Mhz
//#define _DLY_MS				984				//delay for LPC2106
//#define _DLY_MS				226				//lpc1343 on keil

//delay routines
void delay(volatile int dly) {              //waste some cycle
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
	while (ms--) delay_us((F_CPU / 1000000ul) * _DLY_MS);
}
