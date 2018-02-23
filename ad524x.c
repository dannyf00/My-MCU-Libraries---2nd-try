#include <regx51.h>
//#include <iccioavr.h>
//#include <avr/io.h>
//#include <macros.h>
#include "gpio.h"
#include "delay.h"
#include "i2c_sw.h"					//we use software i2c
#include "ad524x.h"					//we use ad524x

unsigned char _AD524X_ADDR;				//ad524x default address

void ad524x_select(unsigned char a1a0) {			//select tc74
	_AD524X_ADDR=AD524X_ADDR | (a1a0 & 0x06);		//a1a0 = 0b00000xx0
	i2c_init();										//initialize the i2c
}

void ad524x_write(unsigned char cmd, unsigned char data_t) {
	//tc74_select(addr);								//select the device
	i2c_start();									//send the start condition
	i2c_write(_AD524X_ADDR | AD524X_ADDR_WRITE);			//send the address + write bit
	i2c_write(cmd);									//send the command
	i2c_write(data_t);								//send the data
	i2c_stop();										//send the stop condition
}

unsigned char ad524x_read(unsigned char cmd) {
	unsigned char tmp=0;
	//tc74_select(addr);								//select the device
	i2c_start();									//send the start condition
	i2c_write(_AD524X_ADDR | AD524X_ADDR_READ);			//send the address + read bit
	i2c_write(cmd);									//write the command
	//i2c_stop();
	//i2c_start();									//restart
	//i2c_write(TC74_ADDR | TC74_CMD_READ);			//send the address + read bit
	tmp=i2c_read(I2C_NOACK);						//read
	i2c_stop();										//send the stop condition
	return tmp;										//return the read
}

//#define TC74_GET_TEMP()				tc74_read(TC74_CMD_RTR)	//read tc74 temperature register
//#define tc74_get_temp()				TC74_GET_TEMP()

//#define TC74_GET_CONFIG()			tc74_read(TC74_CMD_RWCR)	//read tc74 configuration register
//#define tc74_get_config()			TC74_GET_CONFIG()

void ad524x_shutdown(void) {
	ad524x_write(AD524X_CMD_SHUTDOWN, 0x00);		//send the shutdown command
}
