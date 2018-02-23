//demo code for using ad5241/2
//#include <regx51.h>
#include <avr/io.h>
#include "gpio.h"
#include "delay.h"
#include "i2c_sw.h"
#include "ad5242.h"

unsigned char I2C_AD524X_CS=I2C_AD524X_ID;					//i2c selection bit. default A10=0x00;

void ad524x_cs_set(unsigned char a10) {
	I2C_AD524X_CS = I2C_AD524X_ID | (a10 & I2C_AD524X_A10_MASK);			//form I2c_ad524x_cs
}

unsigned char ad524x_cs_get(void) {
	return I2C_AD524X_CS;
}

void ad524x_write(unsigned char instr, unsigned char val) {
	i2c_start();											//start i2c
	i2c_write(I2C_AD524X_CS | I2C_AD524X_CMD_WRITE);		//send the address byte: id + write

	i2c_write(instr & I2C_AD524X_INSTR_MASK);				//send the instruction bit
	i2c_write(val);											//send val
	i2c_stop();												//i2c stop send
}

void ad524x_shutdown(void) {								//shutdown the pot
	i2c_start();											//start i2c
	i2c_write(I2C_AD524X_CS | I2C_AD524X_CMD_WRITE);		//send the address byte: id + write

	i2c_write(I2C_AD524X_INSTR_SD & I2C_AD524X_INSTR_MASK);				//send the instruction bit
	i2c_write(0x00);											//send a dummy value
	i2c_stop();												//i2c stop send
}

void ad524x_reset(void) {									//reset the chip
	i2c_start();											//start i2c
	i2c_write(I2C_AD524X_CS | I2C_AD524X_CMD_WRITE);		//send the address byte: id + write

	i2c_write(I2C_AD524X_INSTR_RS & I2C_AD524X_INSTR_MASK);				//send the instruction bit
	i2c_write(0x00);											//send a dummy value
	i2c_stop();												//i2c stop send
}
