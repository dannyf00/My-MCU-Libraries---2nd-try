//interfacing with 24lc000 with hardware i2c
//address must be a 16-bit word (64K byte eeprom capacity
//unsigned long used for addresses: its lower 16 bits are addresses, and bit 20.19.18 are A2.1.0, respectively
//#include <htc.h>								//we use picc
//#include <ioavr.h>							//we use iar avr
//#include <regx51.h>							//we use keil c51
//#include <avr/io.h>							//we use avr gcc
//#include "delay.h"
//#include "i2c_sw.h"
#include "24lc.h"

#define I2C_24LC_CS_DEFAULT		0x00			//default a210x

unsigned char I2C_24LC_CS=I2C_24LC_CS_DEFAULT;	//24lc000 chip select

void _24lc_select(unsigned char a210x) {		//update a210
//if 16bit addresses are used, active I2C_24LC_CS
#ifdef I2C_24LC_16BIT
	I2C_24LC_CS=a210x & 0x0e;					//retain only bit 3..1
#endif
//otherwise, use the default value of I2C_24LC_CS
}

void _24lc_deselect(unsigned char a210x) {
	I2C_24LC_CS=I2C_24LC_CS_DEFAULT & 0x0e;		//default CS

}

unsigned char _24lc_cs_get(void) {				//read back 210x
	return I2C_24LC_CS;
}

void _24lc_init(void) {							//initialize 24lc
}

unsigned char _24lc_write(unsigned short address, unsigned char dat) {	//write to 24lc
	unsigned char ack;
	i2c_start();				//start the i2c
	i2c_write(I2C_24LC_ID | I2C_24LC_WRITE | I2C_24LC_CS);		//write to the device control/address byte
#ifdef I2C_24LC_16BIT
	i2c_write(address>>8);						//send the high 8-bit address
#endif
	i2c_write(address & 0xff);					//send the low 8-bite address
	ack=i2c_write(dat);							//send the data
	i2c_stop();									//send the stop condition to initiate the write
#ifndef I2C_24LC_ACK_POLLING
	delay_ms(I2C_24LC_WRITE_DELAY);				//delay for the write operation
#else
//	alternative: ack polling, used to increase throughput.
	do {
		i2c_start();
		ack=i2c_write(I2C_24LC_ID | I2C_24LC_WRITE | I2C_24LC_CS);
		i2c_stop();
	} while(ack);								//wait for the device to acknowledge
#endif
	return ack;									//0=success, 1=failure
}

unsigned char _24lc_read(unsigned short address) {	//random read from 24lc
	unsigned char data_t;
	i2c_start();
	i2c_write(I2C_24LC_ID | I2C_24LC_WRITE | I2C_24LC_CS);
#ifdef I2C_24LC_16BIT
	i2c_write(address>>8);						//send the high 8-bit address
#endif
	i2c_write(address & 0xff);					//send the low 8-bite address
	i2c_stop();									//shouldn't have to do that but it works
	i2c_start();								//start again
//	i2c_restart();								//repeat start
	i2c_write(I2C_24LC_ID | I2C_24LC_READ | I2C_24LC_CS);			//keep the ack
	data_t=i2c_read(I2C_NOACK);
	i2c_stop();
   return data_t;
}
