//#include <pic24.h>						//we use pic24f
//#include "gpio.h"
//#include "delay.h"						//we use software delay
//#include "spi_sw.h"						//we use software spi
//#include "misc.h"						//we use ultoa
#include "max7219.h"					//we use max7219

//hardware configuration
//#define SPI_PORT						MAX7219_PORT
//#define SPI_DDR							MAX7219_DDR
//end hardware configuration

//segment information
#define MAX7219_SEGDP					0x80
#define MAX7219_SEGA					0x40
#define MAX7219_SEGB					0x20
#define MAX7219_SEGC					0x10
#define MAX7219_SEGD					0x08
#define MAX7219_SEGE					0x04
#define MAX7219_SEGF					0x02
#define MAX7219_SEGG					0x01
#define MAX7219_BLANK					0x00


//font array
const char led_font[]={
	MAX7219_SEGA | MAX7219_SEGB | MAX7219_SEGC | MAX7219_SEGD | MAX7219_SEGE | MAX7219_SEGF |            0,	//'0'
	           0 | MAX7219_SEGB | MAX7219_SEGC |            0 |            0 |            0 |            0,	//'1'
	MAX7219_SEGA | MAX7219_SEGB |            0 | MAX7219_SEGD | MAX7219_SEGE |            0 | MAX7219_SEGG,	//'2'
	MAX7219_SEGA | MAX7219_SEGB | MAX7219_SEGC | MAX7219_SEGD |            0 |            0 | MAX7219_SEGG,	//'3'
	           0 | MAX7219_SEGB | MAX7219_SEGC |            0 |            0 | MAX7219_SEGF | MAX7219_SEGG,	//'4'
	MAX7219_SEGA |            0 | MAX7219_SEGC | MAX7219_SEGD |            0 | MAX7219_SEGF | MAX7219_SEGG,	//'5'
	MAX7219_SEGA |            0 | MAX7219_SEGC | MAX7219_SEGD | MAX7219_SEGE | MAX7219_SEGF | MAX7219_SEGG,	//'6'
	MAX7219_SEGA | MAX7219_SEGB | MAX7219_SEGC |            0 |            0 | MAX7219_SEGF |            0,	//'7'
	MAX7219_SEGA | MAX7219_SEGB | MAX7219_SEGC | MAX7219_SEGD | MAX7219_SEGE | MAX7219_SEGF | MAX7219_SEGG,	//'8'
	MAX7219_SEGA | MAX7219_SEGB | MAX7219_SEGC |            0 |            0 | MAX7219_SEGF | MAX7219_SEGG,	//'9'
	MAX7219_SEGA | MAX7219_SEGB | MAX7219_SEGC | MAX7219_SEGD | MAX7219_SEGE |            0 | MAX7219_SEGG,	//'a'
	           0 |            0 | MAX7219_SEGC | MAX7219_SEGD | MAX7219_SEGE | MAX7219_SEGF | MAX7219_SEGG,	//'b'
	           0 |            0 |            0 | MAX7219_SEGD | MAX7219_SEGE |            0 | MAX7219_SEGG,	//'c'
	           0 | MAX7219_SEGB | MAX7219_SEGC | MAX7219_SEGD | MAX7219_SEGE |            0 | MAX7219_SEGG,	//'d'
	MAX7219_SEGA |            0 |            0 | MAX7219_SEGD | MAX7219_SEGE | MAX7219_SEGF | MAX7219_SEGG,	//'E'
	MAX7219_SEGA |            0 |            0 |            0 | MAX7219_SEGE | MAX7219_SEGF | MAX7219_SEGG,	//'f'
	           0 |            0 |            0 |            0 |            0 |            0 |            0,	//' '
	           0 |            0 |            0 | MAX7219_SEGD |            0 |            0 |            0,	//'_'
	           0 |            0 |            0 |            0 |            0 |            0 | MAX7219_SEGG,	//'-'
	MAX7219_SEGA |            0 |            0 |            0 |            0 |            0 |            0,	//'top-'
	           0 |            0 |            0 | MAX7219_SEGD |            0 |            0 | MAX7219_SEGG,	//'_+-'
	MAX7219_SEGA |            0 |            0 | MAX7219_SEGD |            0 |            0 |            0,	//'_+top-'
	MAX7219_SEGA |            0 |            0 |            0 |            0 |            0 | MAX7219_SEGG,	//'-+top-'
	MAX7219_SEGA |            0 |            0 | MAX7219_SEGD |            0 |            0 | MAX7219_SEGG,	//'_+-+top-'
	MAX7219_SEGA |            0 |            0 |            0 |            0 |            0 |            0,	//seg_a
	           0 | MAX7219_SEGB |            0 |            0 |            0 |            0 |            0,	//seg_b
	           0 |            0 | MAX7219_SEGC |            0 |            0 |            0 |            0,	//seg_c
	           0 |            0 |            0 | MAX7219_SEGD |            0 |            0 |            0,	//seg_d
	           0 |            0 |            0 |            0 | MAX7219_SEGE |            0 |            0,	//seg_e
	           0 |            0 |            0 |            0 |            0 | MAX7219_SEGF |            0,	//seg_f
	           0 |            0 |            0 |            0 |            0 |            0 | MAX7219_SEGG,	//seg_g
	           0 |            0 |            0 |            0 |            0 |            0 | MAX7219_SEGDP,//seg_dp
	MAX7219_SEGA | MAX7219_SEGB | MAX7219_SEGC | MAX7219_SEGD | MAX7219_SEGE | MAX7219_SEGF | MAX7219_SEGG	//seg_all
};

//unsigned short _max7219_cs=0;			//cs pin
//unsigned char vRAM[8];				//display buffer


//#define max7219_write(addr, dat) 		do {max7219_select(_max7219_cs); spi_write((addr) & 0x0f); spi_write(dat); max7219_deselect(_max7219_cs);} while (0)

//spi communications
void max7219_write(char addr, char dat) {
	char mask;
	
	IO_CLR(MAX7219_PORT, MAX7219_LOAD);
	//send addr first
	mask = 0x80;
	do {
		IO_CLR(MAX7219_PORT, MAX7219_CLK);
		if (addr & mask) IO_SET(MAX7219_PORT, MAX7219_DIN); else IO_CLR(MAX7219_PORT, MAX7219_DIN);
		IO_SET(MAX7219_PORT, MAX7219_CLK);			//strike out data on rising edge
		mask = mask >> 1;
	} while (mask);

	//send data second
	mask = 0x80;
	do {
		IO_CLR(MAX7219_PORT, MAX7219_CLK);
		if (dat & mask) IO_SET(MAX7219_PORT, MAX7219_DIN); else IO_CLR(MAX7219_PORT, MAX7219_DIN);
		IO_SET(MAX7219_PORT, MAX7219_CLK);			//strike out data on rising edge
		mask = mask >> 1;
	} while (mask);
	
	//load the data
	IO_SET(MAX7219_PORT, MAX7219_LOAD);				//load up data to display on rising edge of CS/LOAD pin
}

		
void max7219_init(void) {
	//reset the pins
	IO_SET(MAX7219_PORT, MAX7219_DIN | MAX7219_LOAD | MAX7219_CLK);
	IO_OUT(MAX7219_DDR , MAX7219_DIN | MAX7219_LOAD | MAX7219_CLK);
	
	//_max7219_cs = cs;
	//max7219_write(MAX7219_SHUTDOWN, MAX7219_SHUTOFF);
	//delay_ms(1);
	//max7219_write(MAX7219_SHUTDOWN, MAX7219_NORMAL);
	max7219_shutdown(MAX7219_NORMAL);

	//delay_ms(1);						//datasheet asks for 250us delay here

	//max7219_write(MAX7219_SCANLIMIT, MAX7219_SCANLIMIT07);
	max7219_scanlimit(MAX7219_SCANLIMIT07);

	//max7219_write(MAX7219_DECODE, MAX7219_NODECODE);
	max7219_decode(MAX7219_NODECODE);

	//max7219_write(MAX7219_INTENSITY, MAX7219_INTENSITY1);
	max7219_intensity(MAX7219_INTENSITY5);
}

void max7219_display(char * str) {
	//send 8 digits
	max7219_write(MAX7219_DIG0, *str++);
	max7219_write(MAX7219_DIG1, *str++);
	max7219_write(MAX7219_DIG2, *str++);
	max7219_write(MAX7219_DIG3, *str++);
	max7219_write(MAX7219_DIG4, *str++);
	max7219_write(MAX7219_DIG5, *str++);
	max7219_write(MAX7219_DIG6, *str++);
	max7219_write(MAX7219_DIG7, *str++);
}

