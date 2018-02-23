#include <regx51.h>							//we use keil c51
#include "gpio.h"
#include "i2c_sw.h"							//we use software i2c
#include "pcf8574.h"						//we use pcf8574

unsigned char _pcf8574_a210x;				//a210 for the chip

void pcf8574_init(void) {
}

//select pcf8574
void pcf8574_select(unsigned char a210x) {
	_pcf8574_a210x=a210x & 0x0e;
}

//deselect pcf8574
void pcf8574_deselect(unsigned char a210x) {
}

//read pcf8574
//p0=lsb, p1=msb
unsigned char pcf8574_read(void) {
	unsigned char p1;
	i2c_start();							//i2c start condition
	i2c_write(PCF8575_I2C_ADDR | _pcf8574_a210x | I2C_CMD_READ);	//send the read command
	//p0=i2c_read(I2C_ACK);					//read the lsb, with ack
	p1=i2c_read(I2C_NOACK);					//read the msb, no ack
	i2c_stop();								//send the stop condition
	return (p1);							//return the bytes
}

//write a word to pcf8574
void pcf8574_write(unsigned char byte_t) {
	i2c_start();							//i2c start condition
	i2c_write(PCF8575_I2C_ADDR | _pcf8574_a210x | I2C_CMD_WRITE);	//send the write command
	i2c_write(byte_t);				//write the lsb
	//i2c_write(word_t >> 8);					//wrute the msb
	i2c_stop();								//send the stop condition
}
