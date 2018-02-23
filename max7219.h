#ifndef MAX7219_H_INCLUDED
#define MAX7219_H_INCLUDED

#include "gpio.h"						//we use gpio
//hardware configuration
#define MAX7219_PORT					GPIO
#define MAX7219_DDR						TRISIO
#define MAX7219_DIN						(1<<0)
#define MAX7219_LOAD					(1<<1)
#define MAX7219_CLK						(1<<2)
//#define MAX7219_0		(1<<14)
//end hardware configuration

//special char, as defined in led_font[]
#define FONT_A							led_font[10]		//'a'
#define FONT_B							led_font[11]		//'b'
#define FONT_C							led_font[12]		//'c'
#define FONT_D							led_font[13]		//'d'
#define FONT_E							led_font[14]		//'e'
#define FONT_F							led_font[15]		//'f'
#define FONT_BLANK						led_font[16]		//' '
#define FONT_BAR						led_font[17]		//'_'
#define FONT_DASH						led_font[18]		//'-'
#define FONT_TOP						led_font[19]		//SEG A
#define FONT_BAR2						led_font[20]		//_+-
#define FONT_BAR3						led_font[21]		//_+SEG A
#define FONT_BAR4						led_font[22]		//-+seg A
#define FONT_BAR5						led_font[23]		//_+-+segA
#define FONT_SEGA						led_font[24]		//segment a
#define FONT_SEGB						led_font[25]		//segment b
#define FONT_SEGC						led_font[26]		//segment c
#define FONT_SEGD						led_font[27]		//segment d
#define FONT_SEGE						led_font[28]		//segment e
#define FONT_SEGF						led_font[29]		//segment f
#define FONT_SEGG						led_font[30]		//segment g
#define FONT_DP							led_font[31]		//decimal point
#define FONT_ALL						led_font[31]		//all segments on

//register address
#define MAX7219_NOP						0x00
#define MAX7219_DIG0					0x01
#define MAX7219_DIG1					0x02
#define MAX7219_DIG2					0x03
#define MAX7219_DIG3					0x04
#define MAX7219_DIG4					0x05
#define MAX7219_DIG5					0x06
#define MAX7219_DIG6					0x07
#define MAX7219_DIG7					0x08
#define MAX7219_DECODE					0x09
#define MAX7219_INTENSITY				0x0a
#define MAX7219_SCANLIMIT				0x0b
#define MAX7219_SHUTDOWN				0x0c
#define MAX7219_DISPTEST				0x0f

//shutdown register
#define MAX7219_SHUTOFF					0x00				//shutdown max7219
#define MAX7219_NORMAL					0x01				//turn on max7219

//decode mode
#define MAX7219_NODECODE				0x00				//no decoding. User to provide segment information
#define MAX7219_CODEB0					0x01				//code b for digit 0 only
#define MAX7219_CODEB30					0x0f				//code b for digit 3..0
#define MAX7219_CODEB70					0xff				//code b for digit 7..0

//intensity register
#define MAX7219_INTENSITY1				0x00				//intensity 1/32
#define MAX7219_INTENSITY3				0x01				//intensity 3/32
#define MAX7219_INTENSITY5				0x02				//intensity 5/32
#define MAX7219_INTENSITY7				0x03				//intensity 7/32
#define MAX7219_INTENSITY9				0x04				//intensity 9/32
#define MAX7219_INTENSITY11				0x05				//intensity 11/32
#define MAX7219_INTENSITY13				0x06				//intensity 13/32
#define MAX7219_INTENSITY15				0x07				//intensity 15/32
#define MAX7219_INTENSITY17				0x08				//intensity 17/32
#define MAX7219_INTENSITY19				0x09				//intensity 19/32
#define MAX7219_INTENSITY21				0x0a				//intensity 21/32
#define MAX7219_INTENSITY23				0x0b				//intensity 23/32
#define MAX7219_INTENSITY25				0x0c				//intensity 25/32
#define MAX7219_INTENSITY27				0x0d				//intensity 27/32
#define MAX7219_INTENSITY29				0x0e				//intensity 29/32
#define MAX7219_INTENSITY31				0x0f				//intensity 31/32

//scanlimit
#define MAX7219_SCANLIMIT00				0x00				//scan digit 0..0
#define MAX7219_SCANLIMIT01				0x01				//scan digit 0..1
#define MAX7219_SCANLIMIT02				0x02				//scan digit 0..2
#define MAX7219_SCANLIMIT03				0x03				//scan digit 0..3
#define MAX7219_SCANLIMIT04				0x04				//scan digit 0..4
#define MAX7219_SCANLIMIT05				0x05				//scan digit 0..5
#define MAX7219_SCANLIMIT06				0x06				//scan digit 0..6
#define MAX7219_SCANLIMIT07				0x07				//scan digit 0..7

//extern unsigned short _max7219_cs;							//chip select cache
extern const unsigned char led_font[];						//font map

//select max7219
//#define max7219_select(cs)				do {_max7219_cs = (cs); max7219_deselect(_max7219_cs); IO_CLR(SPI_PORT, _max7219_cs);} while (0)

//deselect max7219
//#define max7219_deselect(cs)			do {IO_SET(SPI_PORT, _max7219_cs); IO_OUT(SPI_DDR, _max7219_cs);} while (0)

//write to max7219
//#define max7219_write(addr, dat) 		do {max7219_select(_max7219_cs); spi_write((addr) & 0x0f); spi_write(dat); max7219_deselect(_max7219_cs);} while (0)

//shutdown / turn on max7219
#define max7219_shutdown(mode)			max7219_write(MAX7219_SHUTDOWN, mode)

//set intensity
#define max7219_intensity(intensity)	max7219_write(MAX7219_INTENSITY, intensity)

//set decode
#define max7219_decode(decode)			max7219_write(MAX7219_DECODE, decode)

//set scan limit
#define max7219_scanlimit(limit)		max7219_write(MAX7219_SCANLIMIT, limit)

//initialize max7219
void max7219_init(void);

//display str on max7219
void max7219_display(char * str);

#endif // MAX7219_H_INCLUDED
