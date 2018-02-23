//#include<regx51.h>										//we use keil c51
#include <pic24.h>											//we use pic24
#include "gpio.h"
#include "_7segx8spi.h"										//we use _7seg display

//hardware configuration
//end hardware configuration

//global variable
//display font for common cathode display - active high
unsigned char const _7seg_font[]= {
	0x3f,									//0
	0x06,									//1
	0x5b,									//2
	0x4f,									//3
	0x66,									//4
	0x6d,									//5
	0x7d,									//6
	0x07,									//7
	0x7f,									//8
	0x6f,									//9
	0x77,									//A
	0x7c,									//b
	0x39,									//C
	0x5e,									//d
	0x79,									//E
	0x71,									//F
	0x40									//???????
};

//display buffer
unsigned char vRAM[_7SEG_NUMBER];									//display buffer

//initialize the display
void _7seg_init(void) {
#if defined(_7SEG_RST)
	IO_CLR(_7SEG_PORT, _7SEG_RST);						//clear rst
	IO_OUT(_7SEG_DDR, _7SEG_RST);						//sck / mosi as output
#endif
	IO_CLR(_7SEG_PORT, _7SEG_SCK | _7SEG_MOSI);			//clear sck / mosi / rst
	IO_OUT(_7SEG_DDR, _7SEG_SCK | _7SEG_MOSI);			//sck / mosi as output
}

void _7seg_write(unsigned char dat) {
	unsigned char mask = 0x80;							//data mask, msb first

	do {
		IO_CLR(_7SEG_PORT, _7SEG_SCK);					//clear the clock line
		if (dat & mask) IO_SET(_7SEG_PORT, _7SEG_MOSI);	//send 1
		else IO_CLR(_7SEG_PORT, _7SEG_MOSI);			//send 0
		IO_SET(_7SEG_PORT, _7SEG_SCK);					//strobe out data on sck's rising edge
		mask = mask >> 1;								//shift to the next bit
	} while (mask);
}

//display the content of vRAM[8]
void _7seg_display(void) {
	static unsigned char digit=0;						//digit to be displayed

	//DIG_OFF(DIGs);										//turn all digits off
#if defined(_7SEG_RST)
	IO_CLR(_7SEG_PORT, _7SEG_RST);	IO_SET(_7SEG_PORT, _7SEG_RST);	//reset and activate the chip
#endif
	_7SEG_ON(_7seg_font[vRAM[digit]]);					//display the digit
	//DIG_ON(1<<digit);									//turn on the digit
	switch (digit) {
	case 0:
		DIG_ON(DIG0);
		break;
	case 1:
		DIG_ON(DIG1);
		break;
	case 2:
		DIG_ON(DIG2);
		break;
	case 3:
		DIG_ON(DIG3);
		break;
	case 4:
		DIG_ON(DIG4);
		break;
	case 5:
		DIG_ON(DIG5);
		break;
	case 6:
		DIG_ON(DIG6);
		break;
	case 7:
		DIG_ON(DIG7);
		break;
	}
	digit+=1;											//increment the digit
	if (digit==_7SEG_NUMBER) digit=0;					//reset the digit
}
