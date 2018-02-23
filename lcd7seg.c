//#include <regx51.h>							//we use keil c51
#include <htc.h>							//we use picc
#include "gpio.h"
#include "_7seg_lcd.h"						//7segment lcd, up to 4 digits

//hardware configuration
//end hardware configuration

//global variable
volatile unsigned char vRAM[8];						//display buffer
//display font for common cathode display - active high
const unsigned char _7seg_font[]={
	0x3f,									//'0'
	0x06,									//'1'
	0x5b,									//'2'
	0x4f,									//'3'
	0x66,									//'4'
	0x6d,									//'5'
	0x7d,									//'6'
	0x07,									//'7'
	0x7f,									//'8'
	0x6f,									//'9'
	0x77,									//'A'
	0x7c,									//'b'
	0x39,									//'C'
	0x5e,									//'d'
	0x79,									//'E'
	0x71,									//'F'
	0x40};									//' '

//reset the 7segment display
void _7seg_init(void) {
	IO_CLR(COM_PORT, COM0);					//clera com0
	IO_OUT(COM_DDR, COM0);					//com0 as output

#ifdef DIG1_PORT
	IO_CLR(DIG1_PORT, DIG1s);				//cleara dig1
	IO_OUT(DIG1_DDR, DIG1s);				//dig1 as output
#endif

#ifdef DIG2_PORT
	IO_CLR(DIG2_PORT, DIG2s);				//cleara dig2
	IO_OUT(DIG2_DDR, DIG2s);				//dig2 as output
#endif

#ifdef DIG3_PORT
	IO_CLR(DIG3_PORT, DIG3s);				//cleara dig3
	IO_OUT(DIG3_DDR, DIG3s);				//dig3 as output
#endif

#ifdef DIG4_PORT
	IO_CLR(DIG4_PORT, DIG4s);				//cleara dig4
	IO_OUT(DIG4_DDR, DIG4s);				//dig4 as output
#endif

}

//display vram[_7SEG_NUMBER]
void _7seg_display(void) {
	static unsigned char com0=0;			//com0's value. 0=com0 high, 1=com0 low

#ifdef DIG1_PORT							//dig1 port is configured
	DIG1_PORT = (com0)?_7seg_font[vRAM[0] & 0x1f]:(~_7seg_font[vRAM[0] & 0x1f]);
#endif

#ifdef DIG2_PORT							//dig1 port is configured
	DIG2_PORT = (com0)?_7seg_font[vRAM[1] & 0x1f]:(~_7seg_font[vRAM[1] & 0x1f]);
#endif

#ifdef DIG3_PORT							//dig1 port is configured
	DIG3_PORT = (com0)?_7seg_font[vRAM[2] & 0x1f]:(~_7seg_font[vRAM[2] & 0x1f]);
#endif

#ifdef DIG4_PORT							//dig1 port is configured
	DIG4_PORT = (com0)?_7seg_font[vRAM[3] & 0x1f]:(~_7seg_font[vRAM[3] & 0x1f]);
#endif

	if (com0) {
		IO_CLR(COM_PORT, COM0);				//clr com0
		com0=0;								//set com0
	}
	else {
		IO_SET(COM_PORT, COM0);				//set com0
		com0=1;								//clera com0
	}
}

