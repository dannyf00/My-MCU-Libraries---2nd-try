//#include <htc.h>
//#include <iccioavr.h>
#include <avr/io.h>
//#include <macros.h>
#include "gpio.h"
#include "delay.h"
#include "i2c_hw.h"

//*************************************************************
//i2c_sw interface
//*************************************************************

#define I2C_WAIT()				{while (!(TWCR & (1<<TWINT))) continue; /*TWCR |= (1<<TWINT);*/}	//wait for the  interrupt to clear

//initialize i2c
void i2c_init(void) {
//	I2C_OUT(I2C_SDA | I2C_SCL);				//turn i2c_sda/i2c_scl as output
	TWCR =	(1<<TWEN);						//enable the i2c module
	TWBR = 0xff;							//set i2c baud rate register
	TWSR |= 0x02;							//i2c prescaler to be 1:16
}


//-----------------START Condition-----------------------
void i2c_start(void) {
	TWCR = 	(1<<TWINT) |					//clear TWINT bit by writing a logic 1 to it
			(1<<TWSTA) |					//send i2c start condition. must be cleared by software
			(1<<TWEN);						//enable i2c module
	I2C_WAIT();
	//TWCR &=~(1<<TWSTA);						//clear the start condition. must be cleared by software
}

//-----------------Repeated START Condition-----------------------
void i2c_restart(void) {
	TWCR = 	(1<<TWINT) |					//clear TWINT bit by writing a logic 1 to it
			(1<<TWSTA) |					//send i2c start condition. must be cleared by software
			(1<<TWEN);						//enable i2c module
	I2C_WAIT();
	//TWCR &=~(1<<TWSTA);						//clear the start condition. must be cleared by software
}

//------------------STOP Condition--------------------------
void i2c_stop(void) {
	TWCR = 	(1<<TWINT) |					//clear twint bit by writing a logic 1 to it
			(1<<TWEN) |						//enable the i2c module
			(1<<TWSTO);						//send the stop condition
	//I2C_WAIT();							//wait for the interrupt to clear
	i2c_delay(1);
	//i2c_delay(1);
	//TWCR &=~(1<<TWSTO);						//clear the stop bit. automatically cleared by hardware
}

//-------------------I2C Write---------------------------
unsigned char i2c_write(unsigned char dat) {
	TWDR=dat;							//load the data
	TWCR =	(1<<TWINT) |						//clear twint bit by writing a logic 1 to it
			(0<<TWSTA) |					//disable start bit
			(1<<TWEN);					//enable the two module
	I2C_WAIT();							//wait for interrupt to clear
	//return ACKSTAT;						//return ack bit
	if (TWSR & I2C_TWSR_ACK) return I2C_ACK;			//ack received
	else return I2C_NOACK;						//no ack received
}

//-----------------------i2c read------------------------------
//to be consistent with i2c protocol, use negative logic
//ack = 0/I2C_ACK -> send ack
//ack = 1/I2C_NOACK -> no ack
unsigned char i2c_read(unsigned char ack) {
	TWDR=0x00;								//send 0;
	if (ack==I2C_NOACK) {
		TWCR =	(1<<TWINT) |					//clear twint bit by writing a logic 1 to it
				(0<<TWSTA) |					//disable start bit
				(0<<TWEA) |						//do not send acknowledge
				(1<<TWEN);						//enable the two module
	} else {
		TWCR =	(1<<TWINT) |					//clear twint bit by writing a logic 1 to it
				(0<<TWSTA) |					//disable start bit
				(1<<TWEA) |						//send acknowledge
				(1<<TWEN);						//enable the two module

	}
	I2C_WAIT();								//wait for the transmission to end
	//if (ack) TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	//else TWCR= (1<<TWINT) | (1<<TWEN);
	return TWDR;					//return
}

//void i2c_delay(unsigned char dly) {						//i2c delay. dly not used
	//NOP();NOP();NOP();NOP();NOP();						//5us under 4Mhz crystal. may need to change
//}

