#ifndef __I2C_SW_H
#define __I2C_SW_H

//*************************************************************
//i2c_sw header file
//*************************************************************

#include "gpio.h"											//we use gpio

//hardware configuration
#define I2C_PORT				PORTB						//i2c pins on portc
#define I2C_DIR					DDRB						//i2c_port direction
#define I2C_PORT_IN				PINB						//input pins

#define I2C_SCL 				(1<<0) 						//Clock Line
#define I2C_SDA 				(1<<1) 						//Data line
//hardware configuration

#define I2C_ACK					0							//0-> ack, to be consistent with i2c protocol
#define I2C_NOACK				1							//1-> no ack

//i2c commands
#define I2C_CMD_READ			0x01						//i2c command for read
#define I2C_CMD_WRITE			0x00						//i2c command for write

//initialize i2c
void i2c_init(void);

//-----------------START Condition-----------------------
void i2c_start(void);

//------------------STOP Condition--------------------------
void i2c_stop(void);

//------------------RESTART Condition--------------------------
#define i2c_restart()	i2c_start()							//restart=start condition

//-------------------I2C write---------------------------
unsigned char i2c_write(unsigned char dat);

//-------------------I2C read---------------------------
unsigned char i2c_read(unsigned char ack);

//void i2c_delay(unsigned char dly);						//i2c delay. dly not used
//#define i2c_delay(n)			{NOP(); NOP(); NOP(); NOP(); /*NOP(); NOP(); NOP(); NOP();/*NOP(); NOP();*/}

#endif
