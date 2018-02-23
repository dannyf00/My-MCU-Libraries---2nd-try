#include "fs637x.h"						//we use fs637x

//hardware configuration
//end hardware configuration

//global defines

//global variables

//read single bit from fs637x
uint8_t fs637x_read(uint8_t regaddr) {
	uint8_t tmp;
	i2c_start();						//send the start condition
	i2c_write(FS637x_ADDR | I2C_CMD_WRITE);	//send the device addr + write
	i2c_write(regaddr);					//send register addr
	i2c_restart();						//restart i2c
	i2c_write(FS637x_ADDR | I2C_CMD_READ);	//send the device addr + read
	tmp = i2c_read(I2C_NOACK);			//read from i2c + no ack
	i2c_stop();							//send the stop condition
	return tmp;
}

//write single byte to fs637x
uint8_t fs637x_write(uint8_t regaddr, uint8_t dat) {
	i2c_start();						//send the start condition
	i2c_write(FS637x_ADDR | I2C_CMD_WRITE);	//send the device addr + write
	i2c_write(regaddr);					//send the register addr
	i2c_write(dat);						//send the data
	i2c_stop();
	return 0;
}

//reset fs637x
void fs637x_init(void) {
	//put default settings here
	
}
