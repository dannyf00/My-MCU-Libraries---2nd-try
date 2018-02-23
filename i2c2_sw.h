#ifndef __I2C2_SW_H
#define __I2C2_SW_H

//*************************************************************
//i2c_sw header file
//*************************************************************

#include "gpio.h"											//we use gpio

//hardware configuration
#define I2C2_PORT				GPIOB						//i2c pins on portc
#define I2C2_DIR				GPIOB						//i2c_port direction
#define I2C2_PORT_IN			GPIOB						//input pins

#define I2C2_SCL 				(1<<4) 						//Clock Line
#define I2C2_SDA 				(1<<5) 						//Data line
//hardware configuration

#define I2C_ACK					0							//0-> ack, to be consistent with i2c protocol
#define I2C_NOACK				(!I2C_ACK)							//1-> no ack

//i2c commands
#define I2C_CMD_READ			0x01						//i2c command for read
#define I2C_CMD_WRITE			0x00						//i2c command for write

//global defines

//initialize i2c
void i2c2_init(void);

//-----------------START Condition-----------------------
void i2c2_start(void);

//------------------STOP Condition--------------------------
void i2c2_stop(void);

//------------------RESTART Condition--------------------------
#define i2c2_restart()	do {i2c2_stop(); i2c2_start();} while (0)		//restart=start condition

//-------------------I2C write---------------------------
unsigned char i2c2_write(unsigned char dat);

//-------------------I2C read---------------------------
unsigned char i2c2_read(unsigned char ack);

//void i2c_delay(unsigned char dly);						//i2c delay. dly not used
//#define i2c_delay(n)			{NOP(); NOP(); NOP(); NOP(); /*NOP(); NOP(); NOP(); NOP();/*NOP(); NOP();*/}

//buffered writes
int8_t i2c2_writes(uint8_t DeviceAddr, uint8_t RegAddr, uint8_t *pBuffer, uint8_t NumByteToRead);

//buffered reads
int8_t i2c2_reads(uint8_t DeviceAddr, uint8_t RegAddr, uint8_t *pBuffer, uint8_t NumByteToRead);
#endif
