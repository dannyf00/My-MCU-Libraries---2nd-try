#include <regx51.h>							//we use keil c51
#include "gpio.h"
#include "i2c_sw.h"							//we use software i2c
#include "max582x.h"						//we use max582x

//hardware configuration
//end hardware configuration

//global variables
unsigned char _max582x_addr;				//default max582x

//select l version address
void max582xl_select(unsigned char add) {
	_max582x_addr = MAX582XL_ADDR | ((add)?0x02:0x00);
	//i2c_init();								//reset - only necessary in high noise environment
}

//select m version address
void max582xm_select(unsigned char add) {
	_max582x_addr = MAX582XM_ADDR | ((add)?0x02:0x00);
	//i2c_init();								//reset - only necessary in high noise environment
}

//send a command / data to max582xl
//data in word_t right aligned (lowest 8/10/12 bits effective)
void max582x_write(unsigned char cmd, unsigned short word_t) {
	word_t <<= MAX582X_SHIFT;				//left shift word_t
	i2c_start();							//send the start condition
	i2c_write(_max582x_addr | I2C_CMD_WRITE);	//write to max582x
	i2c_write(cmd | ((word_t) >> 12));							//send the command
	i2c_write((word_t>>4) & 0x00ff);				//send the low byte
	i2c_stop();
}

//read from max582x
unsigned short max582x_read(unsigned char cmd) {
	unsigned char msb, lsb;

	i2c_start();							//send the start condition
	i2c_write(_max582x_addr | I2C_CMD_WRITE);	//write to max582x
	i2c_write(cmd);							//send the command
	i2c_restart();							//send the restart condition
	i2c_write(_max582x_addr | I2C_CMD_READ);	//read
	msb=i2c_read(I2C_ACK);					//read msb, no ack
	lsb=i2c_read(I2C_NOACK);					//read lsb, ack
	i2c_stop();								//send the stop condition
	return (msb << 8) | lsb;				//return the word
}	

//power mode
void max582x_power(unsigned char mode) {
	max582x_write(MAX582X_EXT, mode & 0x0f);
}
