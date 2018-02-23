//#include <pic24.h>						//we use pic24f
//#include "config.h"						//configuration words
//#include "gpio.h"
//#include "delay.h"						//we use software delay
#include "i2c_sw.h"						//we use software i2c
#include "pca9554.h"					//we use pcc9554
//hardware configuration
//end hardware configuration

unsigned char _pca9554_i2c_addr=PCA9554_ADDR;	//default i2c_address

//select pca9554
//#define pca9554_select(addr)			_pca9554_i2c_addr = (addr)

//#define pca9554_deselect(addr)			//does nothing

//write to addr
void pca9554_write(unsigned char addr, unsigned char dat) {
	i2c_start();						//send the start condition
	i2c_write(_pca9554_i2c_addr | I2C_CMD_WRITE);	//send the address + write command
	i2c_write(addr);					//send the address
	i2c_write(dat);						//send the data
	i2c_stop();							//send the stop condition
}

//read from addr
unsigned char pca9554_read(unsigned char addr) {
	unsigned char tmp;
	i2c_start();						//start the transmission
	i2c_write(_pca9554_i2c_addr | I2C_CMD_WRITE);	//send the address + write
	i2c_write(addr);				//send the address to be read from
	i2c_stop();							//stop
	i2c_start();						//start condition again
	i2c_write(_pca9554_i2c_addr | I2C_CMD_READ);	//read mode
	tmp=i2c_read(I2C_NOACK);				//read the byte
	i2c_stop();							//send the stop condition
	return tmp;
}

//set port to output
//#define pca9554_out(pins)				pca9554_write(PCA9554_DDR, pins)	//default to 1 (input). 0 -> output. 1-> input

//write to port
//#define pca9554_port(dat)				pca9554_write(PCA9554_POUT, dat)
