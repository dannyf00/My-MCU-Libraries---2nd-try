#ifndef I2C2_SW_H_
#define I2C2_SW_H_

#include <p24fxxxx.h>
#include "gpio.h"

//*************************************************************
//i2c_sw header file
//*************************************************************

//hardware configuration
#define I2C_PORT				PORTB						//i2c pins on portc
#define I2C_DIR					TRISB						//i2c_port direction
//#define I2C_SDA 				(1<<4) 						//Data line
//#define I2C_SCL 				(1<<3) 						//Clock Line
#define F_I2C2					F_I2C_100Khz				//i2c frequency at 400Khz (or 100Khz)
//end hardware configuration

#define I2C_ACK					0							//0-> ack, to be consistent with i2c protocol
#define I2C_NOACK				1							//1-> no ack
#define I2C_CMD_WRITE			0x00						//i2c write command
#define I2C_CMD_READ			0x01						//i2c read command

#define F_I2C_100Khz			100000ul					//i2c at 100Khz
#define F_I2C_400Khz			400000ul					//i2c at 400Khz
#define F_I2C_1Mhz				1000000ul					//i2c at 1Mhz

//initialize i2c
void i2c2_init(void);

//-----------------START Condition-----------------------
void i2c2_start(void);

//-----------------repeat START Condition-----------------------
void i2c2_restart(void);

//------------------STOP Condition--------------------------
void i2c2_stop(void);

//-------------------I2C write---------------------------
unsigned char i2c2_write(unsigned char dat);

//-------------------I2C read---------------------------
unsigned char i2c2_read(unsigned char ack);

//void i2c_delay(unsigned char dly);						//i2c delay. dly not used

#endif //i2c2_sw_h_
