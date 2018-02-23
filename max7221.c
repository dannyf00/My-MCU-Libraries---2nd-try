//header file for max7219/7221
#include <regx51.h>							//we use keil c51
#include "gpio.h"
#include "spi_sw.h"							//we use software spi
#include "max7221.h"						//we use max7219/max7221

//hardware configuration
//end hardware configuration


#define max7221_write(cmd, val)	{spi_write(cmd); spi_write(val);}

//global variables
//unsigned char vRAM[8]="23456789";			//display buffer
unsigned char _dig=0;						//current digit	

void max7221_init(void) {
	//instensity max
	spi_select(MAX7221_CS);				//select cs0
	max7221_write(MAX7221_INTSTY, MAX7221_INTSTY_DEFAULT);
	spi_deselect(MAX7221_CS);

	//scan line 0-7
	spi_select(MAX7221_CS);				//select cs0
	max7221_write(MAX7221_SCANLIMIT, MAX7221_SCANLIMIT_DEFAULT);
	spi_deselect(MAX7221_CS);

	//out of shutdown to enable display
	spi_select(MAX7221_CS);				//select cs0
	max7221_write(MAX7221_SHUTDOWN, 0x01);						//bring the chip out of shutdown
	spi_deselect(MAX7221_CS);
}

//send a char to current position
//update _dig
void max7221_putc(unsigned char str) {
	//font table - see max7221 datasheet
	code const unsigned char font_table[]={	//font table
		0x7e,								//'0'
		0x30,								//'1'
		0x6d,								//'2'
		0x79,								//'3'
		0x33,								//'4'
		0x5b,								//'5'
		0x5f,								//'6'
		0x70,								//'7'
		0x7f,								//'8'
		0x73,								//'9'
		0x77,								//'A'
		0x1f,								//'b'
		0x4e,								//'C'
		0x3d,								//'d'
		0x4f,								//'E'
		0x47								//'F'
	};
	
	spi_select(MAX7221_CS);				//select the chip
	max7221_write(++_dig, font_table[str & 0x0f]);
	spi_deselect(MAX7221_CS);				//deselect the chip
	if (_dig==MAX7221_SCANLIMIT_DEFAULT+1) _dig=0;			//wrap around
	//if (_dig==MAX7221_DIGs) _dig=MAX7221_DIGs-1;			//stay at current position

}

//display a str
void max7221_display(unsigned char *str) {
	_dig=0;									//reset the dig
	while (*str) {
		max7221_putc((*str) - '0');
		str++;
	}
}

//display a unsigned long - very slow - 10ms approximately
void max7221_display_ul(unsigned long ul) {
	_dig=0;						//reset the dig
	do {
		max7221_putc(ul % 10);
		ul = ul / 10;
	} while (ul);
}
