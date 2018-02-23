#ifndef _LSM303_H
#define _LSM303_H

#include "gpio.h"									//we use gpio
#include "i2c_sw.h"									//we use software i2c

//hardware configuration
//end hardware configuration

//global defines
#define LSM303ACCEL_I2CADDR				0x32		//0b0011 001x
#define LSM303MAG_I2CADDR				0x3c		//0b0011 110x

//lsm303 register map
//accelerometer
#define LSM303_CTRL_REG1_A				0x20
#define LSM303_CTRL_REG2_A				0x21
#define LSM303_CTRL_REG3_A				0x22
#define LSM303_CTRL_REG4_A				0x23
#define LSM303_CTRL_REG5_A				0x24
#define LSM303_CTRL_REG6_A				0x25
#define LSM303_REFERENCE_A				0x26
#define LSM303_STATUS_A					0x27
#define LSM303_OUT_X_L_A				0x28
#define LSM303_OUT_X_H_A				0x29
#define LSM303_OUT_Y_L_A				0x2A
#define LSM303_OUT_Y_H_A				0x2B
#define LSM303_OUT_Z_L_A				0x2C
#define LSM303_OUT_Z_H_A				0x2D
#define LSM303_FIFO_CTRL_REG_A			0x2E
#define LSM303_FIFO_SRC_REG_A			0x2F
#define LSM303_INT1_CFG_A				0x30
#define LSM303_INT1_SRC_A				0x31
#define LSM303_INT1_THS_A				0x32
#define LSM303_INT1_DURATION_A			0x33
#define LSM303_INT2_CFG_A				0x34
#define LSM303_INT2_SRC_A				0x35
#define LSM303_INT2_THS_A				0x36
#define LSM303_INT2_DURATION_A			0x37
#define LSM303_CLICK_CFG_A				0x38
#define LSM303_CLICK_SRC_A				0x39
#define LSM303_CLICK_THS_A				0x3A
#define LSM303_TIME_LIMIT_A				0x3B
#define LSM303_TIME_LATENCY_A			0x3C
#define LSM303_TIME_WINDOW_A			0x3D

//magnetometer
#define LSM303_CRA_REG_M				0x00
#define LSM303_CRB_REG_M				0x01
#define LSM303_MR_REG_M					0x02
#define LSM303_OUT_X_H_M				0x03
#define LSM303_OUT_X_L_M				0x04
#define LSM303_OUT_Z_H_M				0x05
#define LSM303_OUT_Z_L_M				0x06
#define LSM303_OUT_Y_H_M				0x07
#define LSM303_OUT_Y_L_M				0x08
#define LSM303_SR_REG_M					0x09
#define LSM303_IRA_REG_M				0x0A
#define LSM303_IRB_REG_M				0x0B
#define LSM303_IRC_REG_M				0x0C
#define LSM303_TEMP_OUT_H_M				0x31
#define LSM303_TEMP_OUT_L_M				0x32


typedef struct {
	int16_t ACCEL_X, ACCEL_Y, ACCEL_Z;
	//int16_t GYRO_X, GYRO_Y, GYRO_Z;
	int16_t MAG_X, MAG_Y, MAG_Z;
	int16_t TEMP;									//actual temerature = TEMP / 340 + 36.53C
	float ACCEL_FS;									//full scale (g). Full scale = 32768 (16 bits)
	//float GYRO_FS;								//full scale (d/s). Full scale = 32768 (16 bits)
	float MAG_FS;									//full scale (d/s). Full scale = 32768 (16 bits)
	//int16_t ACCEL_X_BIAS, ACCEL_Y_BIAS, ACCEL_Z_BIAS;
	//int16_t GYRO_X_BIAS, GYRO_Y_BIAS, GYRO_Z_BIAS;
} LSM303_T;


//global variables

//read from lsm303
uint8_t lsm303_read(uint8_t i2c_addr, uint8_t addr);

//write to lsm303
uint8_t lsm303_write(uint8_t i2c_addr, uint8_t addr, uint8_t dat);

//reset lsm303
void lsm303_init(void);

//read ACCELEROMETER
LSM303_T *lsm303a_read(LSM303_T *lsm);

//read MAGNETOMETER
LSM303_T *lsm303m_read(LSM303_T *lsm);

//read MAGNETOMETER temperature
LSM303_T *lsm303t_read(LSM303_T *lsm);

//read lsm303, accelerometer + magnetometer
LSM303_T *lsm303_reads(LSM303_T *lsm);

//in place of lsm303_reada() - not yet working

void lsm303_read1(LSM303_T *lsm);

#endif
