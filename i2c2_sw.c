#include "i2c2_sw.h"

//*************************************************************
//i2c_sw interface
//*************************************************************

#define I2C_SET(bits)				IO_SET(I2C2_PORT, bits)		//set bits on i2c
#define I2C_CLR(bits)				IO_CLR(I2C2_PORT, bits)		//clear bits on i2c
#define I2C_FLP(bits)				IO_FLP(I2C2_PORT, bits)		//flip bits on i2c
#define I2C_OUT(bits)				IO_OUTOD(I2C2_DIR, bits)	//set bits to output
#define I2C_HIZ(bits)				IO_INPU(I2C2_DIR, bits)		//do {I2C_SET(bits); /*IO_INPU(I2C_DIR, bits);*/ i2c_delay(0);} while (0)			//set bits to hi-z/input/float
//#define I2C_HIGH(bits)			{I2C_SET(bits); I2C_OUT(bits); i2c_delay(1);}		//let bits float to high
//note: commenting out I2C_HIZ() or I2C_OUT() from the comments below will accelerate the execution but cause duty cycle to deviate from 50%
#define I2C_HIGH(bits)				do {I2C_SET(bits); /*I2C_HIZ(bits); */i2c_delay(100);} while (0)		//let bits float to high
#define I2C_LOW(bits)				do {I2C_CLR(bits); /*I2C_OUT(bits); */i2c_delay(100);} while (0)	//pull bits low
#define I2C_ACK_ERROR				0x09						//max number of loops before ack times out
#define i2c_delay(n)				do {NOP();} while (0)		//delay

//initialize i2c
void i2c2_init(void) {
	//I2C_OUT(I2C2_SDA | I2C2_SCL);			//turn i2c_sda/i2c_scl as output
	//I2C_LOW(I2C_SDA | I2C_SCL);			//clear the bus
	I2C_HIGH(I2C2_SDA | I2C2_SCL);
}


//-----------------START Condition-----------------------
void i2c2_start(void) {
//	I2C_LOW(I2C_SCL);						//let scl float high
//	I2C_HIGH(I2C_SDA | I2C_SCL);			//let both float high
	I2C_HIGH(I2C2_SDA);						//let sda high
	I2C_HIGH(I2C2_SCL);						//let scl high
	I2C_LOW(I2C2_SDA);						//pull i2c_sda low
	I2C_LOW(I2C2_SCL);						//pull i2c_scl low
}

//------------------STOP Condition--------------------------
void i2c2_stop(void) {
	I2C_LOW(I2C2_SCL);						//let scl float high
	I2C_LOW(I2C2_SDA);
	I2C_HIGH(I2C2_SCL);						//let scl float high
	I2C_HIGH(I2C2_SDA);						//let sda  high
}

//------------------restart condition---------------------

//-------------------I2C Write---------------------------
unsigned char i2c2_write(unsigned char dat) {
	unsigned char i=0x80;

	I2C_HIGH(I2C2_SDA);						//let sda float
	do {
		I2C_LOW(I2C2_SCL);					//clear i2c_scl
	  	if (dat & i) {I2C_HIGH(I2C2_SDA);}		//set i2c_sda
		else {I2C_LOW(I2C2_SDA);}			//clear i2c_sda
		//i2c_delay(0);
	  	I2C_HIGH(I2C2_SCL);					//set i2c_scl
		//I2C_HIGH(I2C2_SCL);					//set i2c_scl - for 50% dc
		//i2c_delay(0);
	  	i = i >> 1;							//shift out the highest bit
	} while (i);
	I2C_LOW(I2C2_SCL);						//clear i2c_scl

	I2C_HIGH(I2C2_SDA);						//float sda, let the slave control it
	//I2C_HIGH(I2C2_SCL);
	i=0;
	while ((IO_GET(I2C2_PORT_IN, I2C2_SDA)&&(i<I2C_ACK_ERROR)))
		i++;								//wait for ack from the slave (ack = sda pulled to low by the slave
	//I2C_HIGH(I2C2_SDA);
	I2C_LOW(I2C2_SCL);
	I2C_HIGH(I2C2_SCL);
	if (i<I2C_ACK_ERROR) return I2C_ACK;	//no trouble
	else return I2C_NOACK;					//trouble! ack timed out
}

//-----------------------i2c read------------------------------
//to be consistent with i2c protocol, use negative logic
//ack = 0 -> send ack
//ack = 1 -> no ack
unsigned char i2c2_read(unsigned char ack) {
	unsigned char i=0x80, data_t=0;

	I2C_HIGH(I2C2_SDA);						//let sda float
	do {
		I2C_LOW(I2C2_SCL);					//clear i2c_scl
		//I2C_LOW(I2C2_SCL);					//clear i2c_scl
		//data_t = data_t << 1;				//left shift the data
		//i2c_delay(0); //i2c_delay(0);//i2c_delay(0);i2c_delay(0);
		I2C_HIGH(I2C2_SCL);					//let scl float to high
		if (IO_GET(I2C2_PORT_IN, I2C2_SDA)) data_t |= i;	//0x01;	//set the last bit high
		else data_t |= 0x00;
		//i2c_delay(0);
		i = i >> 1;
	} while (i);
	I2C_LOW(I2C2_SCL);						//pull scl low
	if (ack==I2C_ACK)
		{I2C_LOW(I2C2_SDA);}				//send ack
	else
		{I2C_HIGH(I2C2_SDA);}				//send no-ack
	I2C_HIGH(I2C2_SCL);						//send ack/noack
	I2C_LOW(I2C2_SCL);
	//I2C_LOW(I2C2_SDA);						//reset sda
	return data_t;
}

//write from a buffer
int8_t i2c2_writes(uint8_t DeviceAddr, uint8_t RegAddr, uint8_t *pBuffer, uint8_t NumByteToWrite) {
	i2c2_start();							//send start condition
	i2c2_write(DeviceAddr | I2C_CMD_WRITE);	//send device addr, for write operations
	i2c2_write(RegAddr);					//send register addr
	while (NumByteToWrite) {
		i2c2_write(*pBuffer);				//send data
		pBuffer++;							//increment buffer pointer
		NumByteToWrite--;					//decrement counter
	}
	i2c2_stop();							//send stop condition
	return 0;								//indicating success
}

//read to a buffer
int8_t i2c2_reads(uint8_t DeviceAddr, uint8_t RegAddr, uint8_t *pBuffer, uint8_t NumByteToRead) {
	i2c2_start();							//send start condition
	i2c2_write(DeviceAddr | I2C_CMD_WRITE);	//send device addr, for write operations
	i2c2_write(RegAddr);					//send register addr
	i2c2_restart();							//send restart
	i2c2_write(DeviceAddr | I2C_CMD_READ);	//send device addr, for read operations
	while (NumByteToRead) {
		if (NumByteToRead==1) {
			*pBuffer=i2c2_read(I2C_NOACK);
			i2c2_stop();							//send the stop condition
			break;
		}
		*pBuffer=i2c2_read(I2C_ACK);		//read the data
		pBuffer++;							//increment buffer
		NumByteToRead--;					//decrement count
	}
	return 0;
}

		