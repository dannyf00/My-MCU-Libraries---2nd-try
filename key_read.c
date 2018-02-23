#include <regx51.h>								//we use keil c51
#include "gpio.h"
#include "key_read.h"						//we use key_read hc164

//hardware configuration
//end hardware configuration

void key_init(void) {
	unsigned char mask = 0x01;
	//IO_CLR(KEYROW_PORT, KEYROW0 | KEYROW1 | KEYROW2 | KEYROW3);
	//IO_IN(KEYROW_DDR, KEYROW0 | KEYROW1 | KEYROW2 | KEYROW3);
	//hc164_write(0xff);
	//IO_CLR(HC164_PORT, HC164_SCK | HC164_SDO);
	//IO_OUT(HC164_OUT, HC164_SCK | HC164_SDO);

	//write all pins high
	IO_SET(HC164_PORT, HC164_SDO);
	do {
		IO_SET(HC164_PORT, HC164_SCK);		//set the clock
		mask = mask << 1;
		IO_CLR(HC164_PORT, HC164_SCK);		//sck set
	} while (mask);
}

unsigned char key_read(unsigned char row) {
	unsigned char mask = 0x01;
	unsigned char tmp;
	
	IO_IN(KEYROW_DDR, row);					//row as input
	
	IO_CLR(HC164_PORT, HC164_SCK | HC164_SDO);	//sck / sdo cleared
	IO_OUT(HC164_DDR, HC164_SCK | HC164_SDO);	//sck / sdo as output

	IO_SET(HC164_PORT, HC164_SCK);			//sck on rising edge, strobe out the '0'
	IO_SET(HC164_PORT, HC164_SDO);			//'1' follows
	do {
		IO_SET(HC164_PORT, HC164_SCK);		//sck set
		if (KEYROW_PORT_IN & row) tmp |= 0x00;	//if row is high, no key pressed
		else tmp |= mask;					//if row is low, key pressed
		IO_CLR(HC164_PORT, HC164_SCK);		//set the clock
		mask = mask << 1;
	} while (mask);
	IO_CLR(HC164_PORT, HC164_SDO | HC164_SCK);			//clear sdo
	return tmp;
}

