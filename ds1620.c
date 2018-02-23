#include <regx51.h>
#include "gpio.h"
#include "ds1620.h"							//we use ds1620

void ds1620_init(void) {					//reset ds1620
	IO_SET(DS1620_PORT, DS1620_SCK);		//sck idles high
	IO_OUT(DS1620_DDR, DS1620_SCK);			//sck as output

	IO_IN(DS1620_DDR, DS1620_DQ);			//sio as input/high-z
}

//write a byte
//assuming that the device has been selected
void ds1620_send(unsigned char byte_t) {	//write a byte
	unsigned char mask = 0x01;				//mask

	IO_OUT(DS1620_DDR, DS1620_DQ);			//sio as output
	//IO_CLR(DS1620_PORT, DS1620_SCK);		//clear sck
	do {
		IO_CLR(DS1620_PORT, DS1620_SCK);	//set sck -> strobe out the bit on sck's rising edge
		if (byte_t & mask) IO_SET(DS1620_PORT, DS1620_DQ);	//send 1
		else IO_CLR(DS1620_PORT, DS1620_DQ);				//otherwise, send 0
		IO_SET(DS1620_PORT, DS1620_SCK);	//set sck -> strobe out the bit on sck's rising edge
		mask = mask << 1;					//shift to the next bit
	} while (mask);
	//IO_CLR(DS1620_PORT, DS1620_SCK);		//clear sck

}

//read a byte
//assuming that the device has been selected
unsigned char ds1620_get(void) {			//read a byte
	unsigned char mask = 0x01;				//mask
	unsigned char tmp = 0x00;				//temp variable

	IO_IN(DS1620_DDR, DS1620_DQ);			//sio as input
	//IO_SET(DS1620_PORT, DS1620_SCK);		//set sck
	do {
		IO_CLR(DS1620_PORT, DS1620_SCK);	//clear sck -> strobe in the bit on sck's falling edge
		NOP(); NOP(); NOP(); //NOP(); NOP();	//waste some time to allow ds1620 to output the bit on sio - tcdd in the datasheet (800ns)
		if (DS1620_PORT_IN & DS1620_DQ) tmp |= mask;	//read 1
		else tmp |= 0x00;					//otherwise, read 0
		IO_SET(DS1620_PORT, DS1620_SCK);	//set sck
		mask = mask << 1;					//shift to the next bit
	} while (mask);
	//IO_CLR(DS1620_PORT, DS1620_SCK);		//clear sck
	return tmp;
}

//#define ds1620_init()						//do nothing - for compatability reasons only

//write a byte to a channel
//assuming that the device has been selected
void ds1620_write(unsigned char ch, unsigned char byte_t) {
	ds1620_send(ch | DS1620_CMD_WRITE);		//send the channel
	ds1620_send(byte_t);
}

//write a word to a channel
//assuming that the device has been selected
void ds1620_write16(unsigned char ch, unsigned short word_t) {
	ds1620_send(ch | DS1620_CMD_WRITE);		//send the channel
	ds1620_send(word_t & 0x00ff);
	ds1620_send(word_t >> 8);
}

//read a byte from a channel
//assuming that the device has been selected
unsigned char ds1620_read(unsigned char ch) {
	ds1620_send(ch | DS1620_CMD_READ);		//send the channel
	return ds1620_get();					//return the result of a read operation
}

//read a word from a channel
//assuming that the device has been selected
unsigned short ds1620_read16(unsigned char ch) {
	unsigned char lsb, msb;

	ds1620_send(ch | DS1620_CMD_READ);		//send the channel
	lsb=ds1620_get();						//get the lsb
	msb=ds1620_get();						//get the msb
	return (msb<<8) | lsb;					//return the result of a read operation
}
