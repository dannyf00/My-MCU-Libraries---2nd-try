#include <regx51.h>
#include "gpio.h"
#include "i2c_sw.h"							//we use software i2c
#include "pcf8591.h"						//we use pcf8591

//hardware configuration
//#define PCF8591_0					0		//a210 of pcf8591_0
//end hardware configuration

unsigned char _pcf8591_addr=0x00;

void pcf8591_write(unsigned char ch, unsigned char data_t) {
	i2c_start();							//send the i2c start condition
	i2c_write(_pcf8591_addr | I2C_CMD_WRITE);	//write
	i2c_write(ch);							//send the control byte
	i2c_write(data_t);						//send the 2nd byte
	i2c_stop();								//send the stop condition
}

unsigned char pcf8591_read(unsigned char ch) {
	unsigned char tmp;
	i2c_start();							//send the i2c start condition
	i2c_write(_pcf8591_addr | I2C_CMD_WRITE);	//write
	i2c_write(ch);							//send the control byte
	i2c_restart();							//send the restart condition
	i2c_write(_pcf8591_addr | I2C_CMD_READ);
	tmp=i2c_read(I2C_NOACK);
	i2c_stop();								//send the stop condition
	return tmp;
}

//reset pcf8591
void pcf8591_init() {
}
