#ifndef I2C_H_
#define I2C_H_

//hardware configuration
#define F_I2C					F_I2C_100Khz				//i2c frequency
//end hardware configuration

#define F_I2C_100Khz			100000ul					//i2c at 100khz
#define F_I2C_400Khz			400000ul					//i2c at 400khz
#define F_I2C_1Mhz				1000000ul					//i2c at 1Mhz

//*************************************************************
//i2c_sw header file
//*************************************************************

//#define I2C_PORT				PORTC		//i2c pins on portc
//#define I2C_DIR					TRISC		//i2c_port direction
//#define I2C_SDA 				(1<<4) 		//Data line
//#define I2C_SCL 				(1<<3) 		//Clock Line

#define I2C_ACK					0							//0-> ack, to be consistent with i2c protocol
#define I2C_NOACK				1							//1-> no ack

//i2c commands
#define I2C_CMD_WRITE			0x00						//i2c write command
#define I2C_CMD_READ			0x01						//i2c read command

//initialize i2c
void i2c_init(void);

//-----------------START Condition-----------------------
void i2c_start(void);

//-----------------repeat START Condition-----------------------
void i2c_restart(void);

//------------------STOP Condition--------------------------
void i2c_stop(void);

//-------------------I2C write---------------------------
unsigned char i2c_write(unsigned char dat);

//-------------------I2C read---------------------------
unsigned char i2c_read(unsigned char ack);

void i2c_delay(unsigned char dly);						//i2c delay. dly not used

#endif
