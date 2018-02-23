#include <regx51.h>
#include "gpio.h"
//#include "delay.h"
#include "i2c_sw.h"							//we use software i2c
#include "mcp4725.h"						//we use mcp4725 i2c adc

unsigned char _mcp4725_a210x=MCP4725_DEFAULT;			//a210x for the selected chip

void mcp4725_init(void) {
}

void mcp4725_select(unsigned char a210x) {
	_mcp4725_a210x = a210x & 0x0e;			//save a210x
}

void mcp4725_dac_write(unsigned short val) {
	i2c_start();							//send a start condition
	i2c_write(MCP4725_I2C_ID | _mcp4725_a210x | I2C_CMD_WRITE);
	i2c_write(val >> 8);					//read the upper byte - lowest 4 bits effective, highest 4 bits zeros
	i2c_write(val);
	i2c_stop();
}
