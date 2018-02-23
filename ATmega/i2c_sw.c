//#include <lpc210x.h>
//#include <iccioavr.h>
//#include <regx51.h>						//we use keil c51
//#include <p24fxxxx.h>						//we use pic24f
//#include <htc.h>							//we use picc
//#include "gpio.h"
//#include "delay.h"
#include "i2c_sw.h"

//*************************************************************
//i2c_sw interface
//*************************************************************

#define I2C_SET(bits)				IO_SET(I2C_PORT, bits)		//set bits on i2c
#define I2C_CLR(bits)				IO_CLR(I2C_PORT, bits)		//clear bits on i2c
#define I2C_FLP(bits)				IO_FLP(I2C_PORT, bits)		//flip bits on i2c
#define I2C_OUT(bits)				IO_OUT(I2C_DIR, bits)		//set bits to output
#define I2C_HIZ(bits)				IO_IN(I2C_DIR, bits)		//set bits to hi-z/input/float
//#define I2C_HIGH(bits)			{I2C_SET(bits); I2C_OUT(bits); i2c_delay(1);}		//let bits float to high
#define I2C_HIGH(bits)				do {I2C_HIZ(bits); i2c_delay(0);} while (0)		//let bits float to high
#define I2C_LOW(bits)				do {I2C_OUT(bits); I2C_CLR(bits); i2c_delay(0);} while (0)	//pull bits low
#define I2C_ACK_ERROR				0x09						//max number of loops before ack times out
#define i2c_delay(n)				do {NOP8();} while (0)		//delay

//initialize i2c
void i2c_init(void) {
	//I2C_OUT(I2C_SDA | I2C_SCL);			//turn i2c_sda/i2c_scl as output
	I2C_HIGH(I2C_SDA | I2C_SCL);			//clear the bus (idles high)
}


//-----------------START Condition-----------------------
void i2c_start(void) {
//	I2C_LOW(I2C_SCL);						//let scl float high
//	I2C_HIGH(I2C_SDA | I2C_SCL);			//let both float high
	I2C_HIGH(I2C_SDA);						//let sda high
	I2C_HIGH(I2C_SCL);						//let scl high
	I2C_LOW(I2C_SDA);						//pull i2c_sda low
	I2C_LOW(I2C_SCL);						//pull i2c_scl low
}

//------------------STOP Condition--------------------------
void i2c_stop(void) {
	I2C_LOW(I2C_SCL);						//let scl float high
	I2C_LOW(I2C_SDA);
	I2C_HIGH(I2C_SCL);						//let scl float high
	I2C_HIGH(I2C_SDA);						//let sda  high
}

//------------------restart condition---------------------

//-------------------I2C Write---------------------------
unsigned char i2c_write(unsigned char dat) {
	unsigned char i;

	I2C_HIGH(I2C_SDA);						//let sda float
	/*
	for(i=0;i<8;i++) { //For loop 8 time(send data 1 byte)
		I2C_LOW(I2C_SCL);					//clear i2c_scl
	  	if(dat&0x80)
			{I2C_HIGH(I2C_SDA);}			//set i2c_sda
		else
			{I2C_LOW(I2C_SDA);}				//clear i2c_sda
	  	dat <<= 1;							//shift out the highest bit
		I2C_HIGH(I2C_SCL);					//set i2c_scl
	}
	*/
	i=0x80;
	do {
		I2C_LOW(I2C_SCL);					//clear i2c_scl
	  	if(dat&i)
			{I2C_HIGH(I2C_SDA);}			//set i2c_sda
		else
			{I2C_LOW(I2C_SDA);}				//clear i2c_sda
		I2C_HIGH(I2C_SCL);					//set i2c_scl
		i2c_delay(0);
	  	i = i >> 1;							//shift out the highest bit
	} while (i);
	I2C_LOW(I2C_SCL);						//clear i2c_scl

	I2C_HIGH(I2C_SDA);						//float sda, let the slave control it
	I2C_HIGH(I2C_SCL);
	i=0;
	while ((IO_GET(I2C_PORT_IN, I2C_SDA)&&(i<I2C_ACK_ERROR)))
		i++;								//wait for ack from the slave (ack = sda pulled to low by the slave
	//I2C_HIZ(I2C_SDA);
	I2C_LOW(I2C_SCL);
	if (i<I2C_ACK_ERROR) return I2C_ACK;	//no trouble
	else return I2C_NOACK;					//trouble! ack timed out
}

//-----------------------i2c read------------------------------
//to be consistent with i2c protocol, use negative logic
//ack = 0 -> send ack
//ack = 1 -> no ack
unsigned char i2c_read(unsigned char ack) {
	unsigned char i, data_t=0;

	I2C_HIGH(I2C_SDA);						//let sda float
	/*for (i=0; i<8; i++) {					//read the data
		I2C_LOW(I2C_SCL);					//clear i2c_scl
		data_t <<=1;						//left shift the data
		I2C_HIGH(I2C_SCL);					//let scl float to high
		if (I2C_PORT_IN & I2C_SDA) data_t |= 0x01;	//set the last bit high
	}*/

	i=0x80;
	do {
		I2C_LOW(I2C_SCL);					//clear i2c_scl
		data_t <<=1;						//left shift the data
		i = i >> 1;
		i2c_delay(0); i2c_delay(0);i2c_delay(0);i2c_delay(0);
		I2C_HIGH(I2C_SCL);					//let scl float to high
		if (IO_GET(I2C_PORT_IN, I2C_SDA)) data_t |= 0x01;	//set the last bit high
		else data_t |= 0x00;
		//i2c_delay(0);
	} while (i);
	I2C_LOW(I2C_SCL);						//pull scl low
	if (ack==I2C_ACK)
		{I2C_LOW(I2C_SDA);}					//send ack
	else
		{I2C_HIGH(I2C_SDA);}				//send no-ack
	I2C_HIGH(I2C_SCL);						//send ack/no-ack
	I2C_LOW(I2C_SCL);
	//I2C_LOW(I2C_SDA);						//reset sda
	return data_t;
}

