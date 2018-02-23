#include <regx51.h>
//#include <iccioavr.h>
//#include <avr/io.h>
//#include <macros.h>
#include "gpio.h"
#include "delay.h"
#include "i2c_sw.h"					//we use software i2c
#include "ad525x.h"					//we use ad525x

unsigned char _AD525X_ADDR;				//ad525x default address

void ad525x_select(unsigned char a1a0) {			//select tc74
	_AD525X_ADDR=AD525X_ADDR | (a1a0 & 0x06);		//a1a0 = 0b00000xx0
	i2c_init();										//initialize the i2c
}

void ad525x_write(unsigned char cmd, unsigned char data_t) {
	//tc74_select(addr);								//select the device
	i2c_start();									//send the start condition
	i2c_write(_AD525X_ADDR | AD525X_ADDR_WRITE);			//send the address + write bit
	i2c_write(cmd);									//send the command
	i2c_write(data_t);								//send the data
	i2c_stop();										//send the stop condition
}

unsigned char ad525x_read(unsigned char cmd) {
	unsigned char tmp=0;
	//tc74_select(addr);								//select the device
	i2c_start();									//send the start condition
	i2c_write(_AD525X_ADDR | AD525X_ADDR_READ);			//send the address + read bit
	i2c_write(cmd);									//write the command
	//i2c_stop();
	//i2c_start();									//restart
	//i2c_write(TC74_ADDR | TC74_CMD_READ);			//send the address + read bit
	tmp=i2c_read(I2C_NOACK);						//read
	i2c_stop();										//send the stop condition
	return tmp;										//return the read
}

