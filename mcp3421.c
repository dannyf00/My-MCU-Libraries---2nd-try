/*
 */

#include <avr/io.h>						//we use gcc avr
#include "gpio.h"
//#include "delay.h"						//we use software delay
#include "i2c_sw.h"						//we use software i2c
#include "mcp3421.h"					//we use mcp3421

//global variables
unsigned char _mcp3421_addr = MCP3421_I2C_ADDR;	//default to a210=0b000
unsigned char _mcp3421_config = MCP3421_OC | MCP3421_12BITS | MCP3421_1x;	//default configuration

//perform adc conversion
unsigned char mcp3421_read(unsigned char a210, signed long * adc) {
	unsigned long tmp_ul;
	unsigned char config;
	i2c_start();
	i2c_write(_mcp3421_addr | I2C_CMD_READ);
	tmp_ul = i2c_read(I2C_ACK);			//read the msb
	tmp_ul = (tmp_ul << 8) | i2c_read(I2C_ACK);			//read the lsb
	if ((_mcp3421_config & MCP3421_18BITS) == MCP3421_18BITS) tmp_ul = (tmp_ul << 8) | i2c_read(I2C_ACK);		//read the lsb
	config = i2c_read(I2C_NOACK);				//read the config
	i2c_stop();
	*adc = tmp_ul;
	return config;
}

//write configuration word to mcp3421
void mcp3421_write(unsigned char a210, unsigned char config) {
	_mcp3421_addr = MCP3421_I2C_ADDR | (a210 & 0x0e);	//configure the i2c address
	_mcp3421_config = config;
	i2c_start();					//send a start condition
	i2c_write(_mcp3421_addr | I2C_CMD_WRITE);	//send the address + read
	i2c_write(_mcp3421_config);				//write configuration word
	i2c_stop();
}
