#include <htc.h>
#include "gpio.h"
#include "i2c_hw.h"

//*************************************************************
//i2c_sw interface
//*************************************************************

#define I2C_SET(bits)			I2C_PORT |= (bits)	//set bits on i2c
#define I2C_CLR(bits)			I2C_PORT &=~(bits)	//clear bits on i2c
#define I2C_FLP(bits)			I2C_PORT ^= (bits)	//flip bits on i2c
#define I2C_OUT(bits)			I2C_DIR &=~(bits)		//set bits to output
#define I2C_HIZ(bits)			I2C_DIR |= (bits)		//set bits to hi-z/input/float
//#define I2C_HIGH(bits)			I2C_SET(bits); I2C_OUT(bits); i2c_delay(1)		//let bits float to high
#define I2C_HIGH(bits)			I2C_HIZ(bits); i2c_delay(1)		//let bits float to high
#define I2C_LOW(bits)			I2C_CLR(bits); I2C_OUT(bits); i2c_delay(1)	//pull bits low
#define I2C_ACK_ERROR	0xf0		//max number of loops before ack times out


#define I2C_WAIT()				do {while (!SSPIF);	SSPIF=0;} while (0)	//wait for the  interrupt to clear

//initialize i2c
void i2c_init(void) {
//	I2C_OUT(I2C_SDA | I2C_SCL);			//turn i2c_sda/i2c_scl as output
	SSPEN = 1;					//enable the mssp port (scl/sda pins)
	SSPM3=1, SSPM2=0, SSPM1=0, SSPM0=0; 		//0b1000=i2c master mode, baud rate = Fosc/(4*(SSPADD+1))
	SSPCON2=0x00;					//clear sspcon2
	SMP = 0;					//enable slew rate control
//	CKE = 0;					//spi edge select
	//SSPADD = 9;					//to yield a 100kbps speed at 4Mhz
	SSPADD = F_CPU / F_I2C - 1 + 2;			//i2c baud rate, minimum of 2
	
}


//-----------------START Condition-----------------------
void i2c_start(void) {
	SEN=1;							//enable start condition
	//I2C_WAIT();
	while (SEN) continue;
}

//-----------------Repeated START Condition-----------------------
void i2c_restart(void) {
	RSEN=1;							//enable start condition
	//I2C_WAIT();
	while (RSEN) continue;
}

//------------------STOP Condition--------------------------
void i2c_stop(void) {
	PEN = 1;						//enable stop condition
	//I2C_WAIT();						//wait for the interrupt to clear
	while (PEN) continue;
}

//-------------------I2C Write---------------------------
unsigned char i2c_write(unsigned char dat) {
	SSPIF=0;					//clear the flag
	SSPBUF=dat;					//load the data
	I2C_WAIT();					//wait for interrupt to clear
	//while (BF) continue;
	return ACKSTAT;					//return ack bit
}

//-----------------------i2c read------------------------------
unsigned char i2c_read(unsigned char ack) {
	while (RW) continue;			//wait for an existing transmission to end
	RCEN=1;							//start to receive
	while (RCEN) continue;
	if (ack==I2C_ACK) ACKDT=I2C_ACK;		//send ack
	else ACKDT=I2C_NOACK;					//send no-ack
	ACKEN=1;						//send the ack bit
	while (ACKEN);					//wait for ack to complete
	return SSPBUF;					//return
}

/*
void i2c_delay(unsigned char dly) {						//i2c delay. dly not used
	NOP();NOP();NOP();NOP();NOP();						//5us under 4Mhz crystal. may need to change
}
*/

#define i2c_delay(n)		{NOP(); NOP(); NOP(); NOP(); NOP();}


