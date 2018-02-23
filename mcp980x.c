//#include <lpc210x.h>
#include <regx51.h>
//#include <htc.h>
#include "gpio.h"
//#include "delay.h"
#include "i2c_sw.h"									//we use software i2c
#include "mcp980x.h"									//we use mcp980x

//*************************************************************
// This code is written to interface a pic16f690 with a
// mcp980x Real Time Clock Chip through an I2C communication
// implemented through software.

// More specifically the code is to write the value 0b00000000
// at address 0x00 in order to start the mcp980x internal occilator,
// and to also write the value 0b10010000 at address 0x07 in
// order to output a 1hz signal on the mcp980x output pin.
//*************************************************************

unsigned char _mcp980x_i2c_addr;						//mcp980x's address

void mcp980x_select(unsigned char a210) {			//select the mcp980x
	_mcp980x_i2c_addr = MCP980x_I2C_ID | (a210 & 0x0e);	//select the sensor
}

//send byte to ch on mcp980x
void mcp980x_write(unsigned char ch, unsigned char byte_t) {
	i2c_start(); 
	i2c_write(_mcp980x_i2c_addr | I2C_CMD_WRITE); 
	i2c_write(ch); 
	i2c_write(byte_t); 
	i2c_stop();
}

//send word_t to ch on mcp980x
void mcp980x_write_word(unsigned char ch, unsigned short word_t) {
	i2c_start(); 
	i2c_write(_mcp980x_i2c_addr | I2C_CMD_WRITE); 
	i2c_write(ch); 
	i2c_write(word_t>>8); 							//write the msb
	i2c_write(word_t & 0x00ff);						//write the lsb
	i2c_stop();
}

//read from mcp980x
unsigned char mcp980x_read(unsigned char ch) {
	unsigned char msb, lsb;
	i2c_start(); 							//start condition
	i2c_write(_mcp980x_i2c_addr | I2C_CMD_WRITE); 				//send the id
	i2c_write(ch); 							//send the channel
	i2c_restart();							//restart
	i2c_write(_mcp980x_i2c_addr | I2C_CMD_READ);		//send the read command
	//msb=i2c_read(I2C_ACK);					//read from mcp980x, acknowledgement
	lsb=i2c_read(I2C_NOACK);				//read from mcp980x, no acknowledgement
	i2c_stop();
	return lsb;
}

//read from mcp980x
unsigned short mcp980x_read_word(unsigned char ch) {
	unsigned char msb, lsb;
	i2c_start(); 							//start condition
	i2c_write(_mcp980x_i2c_addr | I2C_CMD_WRITE); 				//send the id
	i2c_write(ch); 							//send the channel
	//i2c_stop();
	i2c_restart();							//restart
	i2c_write(_mcp980x_i2c_addr | I2C_CMD_READ);		//send the read command
	msb=i2c_read(I2C_ACK);					//read from mcp980x, acknowledgement
	lsb=i2c_read(I2C_NOACK);				//no ack
	i2c_stop();								//stop condition
	return (msb<<8) | lsb;
}

