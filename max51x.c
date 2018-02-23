#include <regx51.h>								//we use keil c51
#include "gpio.h"
#include "i2c_sw.h"							//we use software i2c
#include "max51x.h"							//we use max517/8/9

unsigned char _max51x_i2c_addr=0;				//current max51x i2c address

void max517_select(unsigned char a3210) {
	_max51x_i2c_addr = MAX517_I2C_ID | (a3210 & 0x06);
}

void max518_select(unsigned char a3210) {
	_max51x_i2c_addr = MAX518_I2C_ID | (a3210 & 0x06);
}

void max519_select(unsigned char a3210) {
	_max51x_i2c_addr = MAX519_I2C_ID | (a3210 & 0x1e);
}

void max51x_init(void) {
}

void max51x_write(unsigned char cmd, unsigned char val) {
	i2c_start();							//send the start condition
	i2c_write(_max51x_i2c_addr | I2C_CMD_WRITE);	//send the slave address
	i2c_write(cmd);							//send the command
	i2c_write(val);							//send the value
	i2c_stop();								//send the stop condition
}
