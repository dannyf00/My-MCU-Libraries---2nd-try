//#include <iostm8.h>					//we use stm8s
//#include <htc.h>						//we use picc
//#include <regx51.h>						//we use keil c51
#include <p24fxxxx.h>						//we use pic24f
#include "gpio.h"
//#include "hc164.h"						//we use hc164
#include "_7seg_spi.h"						//our own header file

//initialize _7segment driver
void _7seg_init(void) {					//initialize 7-segment display
	IO_CLR(_7SEG_PORT, _7SEG_SCK | _7SEG_MOSI);	//clear sck / mosi
	IO_OUT(_7SEG_DDR, _7SEG_SCK | _7SEG_MOSI);	//sck / mosi as output
}

void _7seg_write(unsigned char ch) {	//send data via hc164
	unsigned char mask = 0x80;

	do {
		IO_CLR(_7SEG_PORT, _7SEG_SCK);	//clear sck
		if (ch & mask) IO_SET(_7SEG_PORT, _7SEG_MOSI);	//send 1
		else IO_CLR(_7SEG_PORT, _7SEG_MOSI);	//otherwise, send 0
		IO_SET(_7SEG_PORT, _7SEG_SCK);	//strobe out the data
		mask = mask >> 1;				//shift for the next bit
	} while (mask);
	IO_CLR(_7SEG_PORT, _7SEG_SCK);		//reset sck
}

void _7seg_putc(unsigned char ch) {	//send a num to _7segment
	//common anode segment table for 7-segment display
	//hc164->7seg connection:
	//0->A: ~0x01
	//1->B: ~0x02
	//2->C: ~0x04
	//3->D: ~0x08
	//4->E: ~0x10
	//5->F: ~0x20
	//6->G: ~0x40
	//7->DP:~0x80
	const unsigned char seg_table[]={
		0xC0,							//'0'
		0xF9,							//'1'
		0xA4,							//'2'
		0xB0,							//'3'
		0x99,							//'4'
		0x92,							//'5'
		0x82,							//'6'
		0xF8,							//'7'
		0x80,							//'8'
		0x98,							//'9'
		0x80 | 0x08,					//'A'
		0x80 | 0x01 | 0x02,				//'b'
		0x80 | 0x02 | 0x04 | 0x40,		//'C'
		0x80 | 0x01 | 0x20,				//'d'
		0x80 | 0x02 | 0x04,				//'E'
		0x80 | 0x02 | 0x04 | 0x08		//'F'
	};
	//hc164_write(seg_table[num % 10]);	//if num is numerical
	//hc164_write(seg_table[ch-'0']);	//if num is alphanumerical
#if _7SEG_COM_ANODE == 1				//common anode -> com pin high and seg pin low to light up a led	
	_7seg_write(seg_table[ch & 0x0f]);
#else									//common cathod-> com pin low and seg pin high to light up a led
	_7seg_write(~seg_table[ch & 0x0f]);
#endif
	//return 0;							//successful
}

void _7seg_puts(unsigned char * str) {
	while (*str) {
		_7seg_putc(*str++);
	}
}
	
//send 1 digit
unsigned char _7seg_display1(unsigned short num) {

	DIG_OFF(_7SEG_COM);
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the least significant digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 2nd digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 3rd digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 4th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 5th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 6th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 7th digit
	_7seg_putc(num % _7SEG_BASE);                          //send the most significant digit
	DIG_ON(_7SEG_COM);
	return 0;
}

//send 2 digits
unsigned char _7seg_display2(unsigned short num) {

	DIG_OFF(_7SEG_COM);
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the least significant digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 2nd digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 3rd digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 4th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 5th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 6th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 7th digit
	_7seg_putc(num % _7SEG_BASE);                          //send the most significant digit
	DIG_ON(_7SEG_COM);
	return 0;
}

//send 4 digits
unsigned char _7seg_display4(unsigned short num) {

	DIG_OFF(_7SEG_COM);
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the least significant digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 2nd digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 3rd digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 4th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 5th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 6th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 7th digit
	_7seg_putc(num % _7SEG_BASE);                          //send the most significant digit
	DIG_ON(_7SEG_COM);
	return 0;
}

//send 6 digits
unsigned char _7seg_display6(unsigned short num) {

	DIG_OFF(_7SEG_COM);
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the least significant digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 2nd digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 3rd digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 4th digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 5th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 6th digit
	//_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 7th digit
	_7seg_putc(num % _7SEG_BASE);                          //send the most significant digit
	DIG_ON(_7SEG_COM);
	return 0;
}

//send 8 digits
unsigned char _7seg_display8(unsigned short num) {

	DIG_OFF(_7SEG_COM);
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the least significant digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 2nd digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 3rd digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 4th digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 5th digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 6th digit
	_7seg_putc(num % _7SEG_BASE); num = num / _7SEG_BASE;	//send the 7th digit
	_7seg_putc(num % _7SEG_BASE);                          //send the most significant digit
	DIG_ON(_7SEG_COM);
	return 0;
}

