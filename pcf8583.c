//#include <lpc210x.h>
//#include "delay.h"
#include <regx51.h>							//we use keil c51
#include "i2c_sw.h"							//we use software i2c
#include "pcf8583.h"

//*************************************************************
// This code is written to interface a pic16f690 with a
// pcf8583 Real Time Clock Chip through an I2C communication
// implemented through software.

// More specifically the code is to write the value 0b00000000
// at address 0x00 in order to start the pcf8583 internal occilator,
// and to also write the value 0b10010000 at address 0x07 in
// order to output a 1hz signal on the pcf8583 output pin.
//*************************************************************


//send byte to ch on pcf8583
void pcf8583_write(unsigned char ch, unsigned char byte_t) {
	i2c_start(); 
	i2c_write(PCF8583_I2C_ID | I2C_CMD_WRITE); 
	i2c_write(ch); 
	i2c_write(byte_t); 
	i2c_stop();
}

//read from pcf8583
unsigned char pcf8583_read(unsigned char ch) {
	unsigned char dat;
	i2c_start(); 							//start condition
	i2c_write(PCF8583_I2C_ID | I2C_CMD_WRITE); 				//second the id
	i2c_write(ch); 							//send the channel
	i2c_start();							//restart
	i2c_write(PCF8583_I2C_ID | I2C_CMD_READ);		//send the read command
	dat=i2c_read(I2C_NOACK);				//read from pcf8583, no acknowledgement
	i2c_stop();
	return dat;
}

