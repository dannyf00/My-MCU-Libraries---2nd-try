//#include <p24fxxxx.h>
//#include "gpio.h"
#include "i2c2_hw.h"						//we use hardware i2c2

//void i2c2_delay(unsigned char dly);

//*************************************************************
//i2c_sw interface
//*************************************************************
#define I2C_BRG16				((F_CPU / F_I2C2) - (F_CPU / 10000000ul) -1 + 2)	//brg generator value. minimum of 2

//change this section if not using I2C2
#define I2Cx_CEN				I2C2CONbits.I2CEN		//enable i2c
#define I2Cx_A10M				I2C2CONbits.A10M		//1=10 bits, 0=7 bits
#define I2Cx_BRG				I2C2BRG					//baud rate generator
#define I2Cx_SEN				I2C2CONbits.SEN			//sen, send a start condition
#define I2Cx_RSEN				I2C2CONbits.RSEN		//rsen, send a restart condition
#define I2Cx_PEN				I2C2CONbits.PEN			//pen, send a stop condition
#define I2Cx_RCEN				I2C2CONbits.RCEN		//enable master receive
#define I2Cx_TRSTAT				I2C2STATbits.TRSTAT		//transmission status bit. 1=transmission in progress. 0=transmission complete
#define I2Cx_TBF				I2C2STATbits.TBF		//transmission transmitter full status bit. 1=transmission in progress. 0=transmission complete
#define I2Cx_RBF				I2C2STATbits.RBF		//transmission receiver full status bit. 1=transmission in progress. 0=transmission complete
#define I2Cx_TRN				I2C2TRN					//i2c data buffer
#define I2Cx_ACKSTAT			I2C2STATbits.ACKSTAT	//i2c ack bit
#define I2Cx_ACKDT				I2C2CONbits.ACKDT		//ack knowledge bit. 1=send i2c_nack; 0=send i2c_ack
#define I2Cx_ACKEN				I2C2CONbits.ACKEN		//ack knowledge enable bit. 1=sending ack bit; 0=done sending ack bit
#define I2Cx_RCV				I2C2RCV					//data received
#define I2Cx_I2COV				I2C2STATbits.I2COV		//i2c receiver overflow
#define I2Cx_MD					_I2C2MD							//enable power to i2c1

#define I2C_LONG_TIMEOUT		0x1000

//global variables
static uint16_t _i2c_timeout;									//timeout counter

//initialize i2c
void i2c2_init(void) {
	I2Cx_MD = 0;						//enable power to i2c1
//	I2C_OUT(I2C_SDA | I2C_SCL);				//turn i2c_sda/i2c_scl as output
	I2Cx_A10M = 0;						//i2cxadd is 7 bits
	I2Cx_BRG = I2C_BRG16;					//set the baud rate
	I2Cx_CEN = 1;						//enable the i2c port (scl/sda pins)
}


//-----------------START Condition-----------------------
void i2c2_start(void) {
	I2Cx_SEN=1;								//enable start condition
	//I2C_WAIT();
	while (I2Cx_SEN) continue;
}

//-----------------Repeated START Condition-----------------------
void i2c2_restart(void) {
	I2Cx_RSEN=1;							//enable start condition
	//I2C_WAIT();
	while (I2Cx_RSEN) continue;
}

//------------------STOP Condition--------------------------
void i2c2_stop(void) {
	I2Cx_PEN = 1;							//enable stop condition
	//I2C_WAIT();							//wait for the interrupt to clear
	while (I2Cx_PEN) continue;
}

//-------------------I2C Write---------------------------
unsigned char i2c2_write(unsigned char dat) {
	I2Cx_TRN=dat;							//load the data
	//I2C_WAIT();							//wait for interrupt to clear
	while (I2Cx_TRSTAT) continue;
	return I2Cx_ACKSTAT;					//return ack bit
}

//-----------------------i2c read------------------------------
unsigned char i2c2_read(unsigned char ack) {
	//while (RW);							//wait for an existing transmission to end
	I2Cx_RCEN=1;							//start to receive
	while (I2Cx_RCEN) continue;				//wait for the receive to end
	I2Cx_I2COV=0;							//clear the flag
	if (ack==I2C_ACK) I2Cx_ACKDT=I2C_ACK;			//send ack
	else I2Cx_ACKDT=I2C_NOACK;				//send no-ack
	I2Cx_ACKEN=1;
	while (I2Cx_ACKEN) continue;			//wait for ack to end
	return I2Cx_RCV;						//return
}

/*void i2c_delay(unsigned char dly) {		//i2c delay. dly not used
	NOP();NOP();NOP();NOP();NOP();			//5us under 4Mhz crystal. may need to change
}
*/

#define i2c2_delay(n)			{/*NOP();NOP();NOP();NOP();NOP();*/}


//write a block
int16_t i2c2_writes(uint8_t DeviceAddr, uint8_t RegAddr, uint8_t *pBuffer, uint16_t NumBytes) {
	//send a strat condition
	I2Cx_SEN=1;								//enable start condition
	//I2C_WAIT();
	_i2c_timeout=I2C_LONG_TIMEOUT;
	while (I2Cx_SEN) if (_i2c_timeout--==0) return -1;	//continue;

	//send device address
	I2Cx_TRN=DeviceAddr | I2C_CMD_WRITE;	//load the data
	//I2C_WAIT();							//wait for interrupt to clear
	_i2c_timeout=I2C_LONG_TIMEOUT;
	while (I2Cx_TRSTAT) if (_i2c_timeout--==0) return -2;	//continue;			//wait for the transmission to end
	if (I2Cx_ACKSTAT) return -3;			//if no ack received

	//send register address
	I2Cx_TRN=RegAddr;								//load the data
	//I2C_WAIT();									//wait for interrupt to clear
	_i2c_timeout=I2C_LONG_TIMEOUT;
	while (I2Cx_TRSTAT) if (_i2c_timeout--==0) return -4;	//continue;			//wait for the transmission to end
	if (I2Cx_ACKSTAT) return -5;					//if no ack received

	//send multiple bytes
	while (NumBytes) {
		//send data bytes
		I2Cx_TRN=*pBuffer;								//load the data
		//I2C_WAIT();									//wait for interrupt to clear
		_i2c_timeout=I2C_LONG_TIMEOUT;
		while (I2Cx_TRSTAT) if (_i2c_timeout--==0) return -6;	//continue;			//wait for the transmission to end
		if (I2Cx_ACKSTAT) return -7;					//if no ack received

		pBuffer++;									//increment buffer pointer
		NumBytes--;									//decrement buffer counter
	}

	//send stop condition
	I2Cx_PEN = 1;									//enable stop condition
	//I2C_WAIT();									//wait for the interrupt to clear
	_i2c_timeout=I2C_LONG_TIMEOUT;
	while (I2Cx_PEN) if (_i2c_timeout--==0) return -8;	//continue;

	return 0;										//indicating success
}

//read a block
int16_t i2c2_reads(uint8_t DeviceAddr, uint8_t RegAddr, uint8_t *pBuffer, uint16_t NumBytes) {
	//send a strat condition
	I2Cx_SEN=1;										//enable start condition
	//I2C_WAIT();
	_i2c_timeout=I2C_LONG_TIMEOUT;
	while (I2Cx_SEN) if (_i2c_timeout--==0) return -1;	//continue;

	//send device address
	I2Cx_TRN=DeviceAddr | I2C_CMD_WRITE;							//load the data
	//I2C_WAIT();									//wait for interrupt to clear
	_i2c_timeout=I2C_LONG_TIMEOUT;
	while (I2Cx_TRSTAT) if (_i2c_timeout--==0) return -2;	//continue;			//wait for the transmission to end
	if (I2Cx_ACKSTAT) return -3;					//if no ack received

	//send register address
	I2Cx_TRN=RegAddr;								//load the data
	//I2C_WAIT();									//wait for interrupt to clear
	_i2c_timeout=I2C_LONG_TIMEOUT;
	while (I2Cx_TRSTAT) if (_i2c_timeout--==0) return -4;	//continue;			//wait for the transmission to end
	if (I2Cx_ACKSTAT) return -5;					//if no ack received


	//send a restrat condition
	I2Cx_RSEN=1;									//enable start condition
	//I2C_WAIT();
	_i2c_timeout=I2C_LONG_TIMEOUT;
	while (I2Cx_RSEN) if (_i2c_timeout--==0) return -6;	//continue;

	//send device address
	I2Cx_TRN=DeviceAddr | I2C_CMD_READ;							//load the data
	//I2C_WAIT();									//wait for interrupt to clear
	_i2c_timeout=I2C_LONG_TIMEOUT;
	while (I2Cx_TRSTAT) if (_i2c_timeout--==0) return -7;	//continue;			//wait for the transmission to end
	if (I2Cx_ACKSTAT) return -8;						//if no ack received


	//read multiple bytes
	I2Cx_ACKDT=I2C_ACK;								//send no-ack
	while (NumBytes) {
		if (NumBytes==1) I2Cx_ACKDT=I2C_NOACK;
		I2Cx_RCEN=1;								//start to receive
		_i2c_timeout=I2C_LONG_TIMEOUT;
		while (I2Cx_RCEN) if (_i2c_timeout--==0) return -8;
		I2Cx_ACKEN=1;								//send ack
		while (I2Cx_ACKEN) continue;				//wait for ack to end
		I2Cx_I2COV=0;								//clear the flag
		*pBuffer=I2Cx_RCV;							//save the data
		pBuffer++;									//increment buffer pointer
		NumBytes--;									//decrement buffer counter
	}

	//restore ack
	//I2Cx_ACKEN=0;
	I2Cx_ACKDT=I2C_ACK;								//send ack

	//send stop condition
	I2Cx_PEN = 1;									//enable stop condition
	//I2C_WAIT();									//wait for the interrupt to clear
	_i2c_timeout=I2C_LONG_TIMEOUT;
	while (I2Cx_PEN) if (_i2c_timeout--==0) return -10;	//continue;

	//I2Cx_ACKEN=1;
	return 0;										//indicating success
}
