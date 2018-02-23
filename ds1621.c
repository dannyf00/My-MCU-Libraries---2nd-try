//#include <lpc210x.h>
//#include <regx51.h>
//#include <htc.h>									//we use pic
#include <p24fxxxx.h>								//we use pic24f
#include "gpio.h"
//#include "delay.h"
#include "i2c_sw.h"									//we use software i2c
#include "ds1621.h"									//we use ds1621

//*************************************************************
// This code is written to interface a pic16f690 with a
// ds1621 Real Time Clock Chip through an I2C communication
// implemented through software.

// More specifically the code is to write the value 0b00000000
// at address 0x00 in order to start the ds1621 internal occilator,
// and to also write the value 0b10010000 at address 0x07 in
// order to output a 1hz signal on the ds1621 output pin.
//*************************************************************

unsigned char _ds1621_i2c_addr;						//ds1621's address

void ds1621_select(unsigned char a210) {			//select the ds1621
	_ds1621_i2c_addr = DS1621_I2C_ID | (a210 & 0x0e);	//select the sensor
}

//send byte to ch on ds1621
void ds1621_write(unsigned char ch, unsigned char byte_t) {
	i2c_start(); 
	i2c_write(_ds1621_i2c_addr | I2C_CMD_WRITE); 
	i2c_write(ch); 
	i2c_write(byte_t); 
	i2c_stop();
}

//read from ds1621
unsigned char ds1621_read(unsigned char ch) {
	unsigned char dat;
	i2c_start(); 							//start condition
	i2c_write(_ds1621_i2c_addr | I2C_CMD_WRITE); 				//send the id
	i2c_write(ch); 							//send the channel
	i2c_restart();							//restart
	i2c_write(_ds1621_i2c_addr | I2C_CMD_READ);		//send the read command
	dat=i2c_read(I2C_NOACK);				//read from ds1621, no acknowledgement
	i2c_stop();
	return dat;
}

//read from ds1621
unsigned short ds1621_read_word(unsigned char ch) {
	unsigned char msb, lsb;
	i2c_start(); 							//start condition
	i2c_write(_ds1621_i2c_addr | I2C_CMD_WRITE); 				//send the id
	i2c_write(ch); 							//send the channel
	//i2c_stop();
	i2c_restart();							//restart
	i2c_write(_ds1621_i2c_addr | I2C_CMD_READ);		//send the read command
	msb=i2c_read(I2C_ACK);					//read from ds1621, acknowledgement
	lsb=i2c_read(I2C_NOACK);				//no ack
	i2c_stop();								//stop condition
	return (msb<<8) | lsb;
}

