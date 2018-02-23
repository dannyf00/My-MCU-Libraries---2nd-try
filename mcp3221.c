#include <regx51.h>
#include "gpio.h"
//#include "delay.h"
#include "i2c_sw.h"							//we use software i2c
#include "mcp3221.h"						//we use mcp3221 i2c adc

unsigned char _mcp3221_a210x=0x00;					//a210x for the selected chip

void mcp3221_init(void) {
}

void mcp3221_select(unsigned char a210x) {
	_mcp3221_a210x = a210x & 0x0e;			//save a210x
}

unsigned short mcp3221_read(void) {
	unsigned char msb, lsb;					//temp variables
	i2c_start();							//send a start condition
	i2c_write(MCP3221_I2C_ID | _mcp3221_a210x | I2C_CMD_READ);
	msb=i2c_read(I2C_ACK);					//read the upper byte - lowest 4 bits effective, highest 4 bits zeros
	lsb=i2c_read(I2C_NOACK);
	i2c_stop();
	return (msb << 8) | lsb;
}
