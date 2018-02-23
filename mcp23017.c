#include <regx51.h>
#include "gpio.h"
#include "i2c_sw.h"								//we use software i2c
#include "mcp23017.h"							//we use mcp23017 i2c expander

unsigned char _mcp23017_addr=0x00;				//mcp23017 i2c address

//select mcp23017
void mcp23017_select(unsigned char a210) {
	_mcp23017_addr = MCP23017_I2C_ID | ((a210) & 0x0e);
}


//write a byte to mcp23017
void mcp23017_write(unsigned char ch, unsigned char byte_t) {
	i2c_start();								//send the start condition
	i2c_write(_mcp23017_addr | I2C_CMD_WRITE);	//send the slave address
	i2c_write(ch);								//send the ch
	i2c_write(byte_t);							//send the data byte
	i2c_stop();									//send the stop condition
}

//read a byte from mcp23017
unsigned char mcp23017_read(unsigned char ch) {
	i2c_start();								//send the start condition
	i2c_write(_mcp23017_addr | I2C_CMD_WRITE); 	//second the id
	i2c_write(ch); 								//send the channel
	i2c_start();								//restart
	i2c_write(_mcp23017_addr | I2C_CMD_READ);	//send the read command
	ch=i2c_read(I2C_NOACK);					//read from ds1307, no acknowledgement
	i2c_stop();									//send the stop condition
	return ch;
}
