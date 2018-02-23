#ifndef __7SEG_SPI_H
#define __7SEG_SPI_H

//7segment drivers
//send highest digits first.
//hardware configuration
#define _7SEG_PORT			LATB				//pins on portd
#define _7SEG_DDR			TRISB
#define _7SEG_SCK			(1<<6)				//sck pin
#define _7SEG_MOSI			(1<<7)				//mosi pin
#define _7SEG_COM			(1<<7)				//com pin - can be commented out if com pins are tied to vcc or gnd
//end hardware configuration

//hc164 connection:
//the least significant bit first in the hc164 chain and
//the most significant bit first last

//up to 8 digits

#define _7SEG_COM_ANODE			1				//1=common anode, 0=common cathod
//user to define com pins
//end hardware configuration

#define _7SEG_BASE			10				//display base. <= 16

#ifdef _7SEG_COM							//if the com pin defined
#if _7SEG_COM_ANODE == 1
//for common anode
#define DIG_ON(com)			{IO_SET(_7SEG_PORT, com); IO_OUT(_7SEG_DDR, com);}	//turn on a digit
#define DIG_OFF(com)			{IO_CLR(_7SEG_PORT, com); IO_OUT(_7SEG_DDR, com);}	//turn off a digit
#else
//for common cathod
#define DIG_OFF(com)			{IO_SET(_7SEG_PORT, com); IO_OUT(_7SEG_DDR, com);}	//turn on a digit
#define DIG_ON(com)			{IO_CLR(_7SEG_PORT, com); IO_OUT(_7SEG_DDR, com);}	//turn off a digit
#endif	//_7seg_com_anode
#else										//_7seg_com pin not defined
#define DIG_ON(com)							//for compatability
#define DIG_OFF(com)						//for compatibility
#endif //_7seg_com

void _7seg_init(void);							//initialize 7-segment display

void _7seg_putc(unsigned char ch);	//send a ch to _7segment
void _7seg_puts(unsigned char * str);		//send a str to _7segment
	
//display a string.
//highest / left most numbers first
unsigned char _7seg_display1(unsigned short num);	//display 1 number
unsigned char _7seg_display2(unsigned short num);	//display 2 numbers
unsigned char _7seg_display4(unsigned short num);	//display 4 numbers
unsigned char _7seg_display6(unsigned short num);	//display 6 numbers
unsigned char _7seg_display8(unsigned short num);	//display 8 numbers

#endif
