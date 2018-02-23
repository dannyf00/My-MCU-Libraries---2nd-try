//#include <regx51.h>
#include <avr/io.h>
#include "gpio.h"
#include "delay.h"
#include "i2c_sw.h"
#include "tc74.h"

unsigned char TC74_ADDR=TC74_ADDR_A5;				//TC74 default address

void tc74_select(unsigned char addr) {		//select tc74
	TC74_ADDR=addr & 0xfe;
	i2c_init();										//initialize the i2c
}

void tc74_write(unsigned char cmd, unsigned char data_t) {
	//tc74_select(addr);								//select the device
	i2c_start();									//send the start condition
	i2c_write(TC74_ADDR | TC74_CMD_WRITE);			//send the address + write bit
	i2c_write(cmd);									//send the command
	i2c_write(data_t);								//send the data
	i2c_stop();										//send the stop condition
}

signed char tc74_read(unsigned char cmd) {
	signed char tmp=0;
	//tc74_select(addr);								//select the device
	i2c_start();									//send the start condition
	i2c_write(TC74_ADDR | TC74_CMD_WRITE);			//send the address + write bit
	i2c_write(cmd);									//write the command
	//i2c_stop();
	i2c_start();									//restart
	i2c_write(TC74_ADDR | TC74_CMD_READ);			//send the address + read bit
	tmp=i2c_read(I2C_NOACK);						//read
	i2c_stop();										//send the stop condition
	return tmp;										//return the read
}

void tc74_shutdown(void) {
	tc74_write(TC74_CMD_RWCR, TC74_MASK_STANDBY);
}
