#ifndef _MPU6050_H
#define _MPU6050_H

#include "gpio.h"										//use gpio
#include "i2c_sw.h"										//we use software i2c

//hardware configuration
//#define MPU6050_DEBIAS									//defined to automatically debias gyro/accelerometer readings
#define MPU6050_DEBIAS_WT				3				//debias weight for new data
//end hardware configuration

//global defines
#define MPU6050_I2CADDR			0xd0					//i2c address when ad0 is ground
//#define MPU6050_I2CADDR			0xd2				//i2c address when ad0 is set
//register map
#define MPU6050_SELF_TEST_X				0x0d
#define MPU6050_SELF_TEST_Y				0x0e
#define MPU6050_SELF_TEST_Z				0x0f
#define MPU6050_SELF_TEST_A				0x10
#define MPU6050_SMPLRT_DIV				0x19
#define MPU6050_CONFIG					0x1a
#define MPU6050_GYRO_CONFIG				0x1b
#define MPU6050_ACCEL_CONFIG			0x1c
#define MPU6050_MOT_THR					0x1f
#define MPU6050_FIFO_EN					0x23
#define MPU6050_I2C_MST_CTRL			0x24
#define MPU6050_I2C_SLV0_ADDR			0x25
#define MPU6050_I2C_SLV0_REG			0x26
#define MPU6050_I2C_SLV0_CTRL			0x27
#define MPU6050_I2C_SLV1_ADDR			0x28
#define MPU6050_I2C_SLV1_REG			0x29
#define MPU6050_I2C_SLV1_CTRL			0x2a
#define MPU6050_I2C_SLV2_ADDR			0x2b
#define MPU6050_I2C_SLV2_REG			0x2c
#define MPU6050_I2C_SLV2_CTRL			0x2d
#define MPU6050_I2C_SLV3_ADDR			0x2e
#define MPU6050_I2C_SLV3_REG			0x2f
#define MPU6050_I2C_SLV3_CTRL			0x30
#define MPU6050_I2C_SLV4_ADDR			0x31
#define MPU6050_I2C_SLV4_REG			0x32
#define MPU6050_I2C_SLV4_DO				0x33
#define MPU6050_I2C_SLV4_CTRL			0x34
#define MPU6050_I2C_SLV4_DI				0x35
#define MPU6050_I2C_MST_STATUS			0x36
#define MPU6050_INT_PIN_CFG 			0x37
#define MPU6050_INT_ENABLE				0x38
#define MPU6050_INT_STATUS				0x3a
#define MPU6050_ACCEL_XOUT_H			0x3b
#define MPU6050_ACCEL_XOUT_L			0x3c
#define MPU6050_ACCEL_YOUT_H			0x3d
#define MPU6050_ACCEL_YOUT_L			0x3e
#define MPU6050_ACCEL_ZOUT_H			0x3f
#define MPU6050_ACCEL_ZOUT_L			0x40
#define MPU6050_TEMP_OUT_H				0x41
#define MPU6050_TEMP_OUT_L				0x42
#define MPU6050_GYRO_XOUT_H				0x43
#define MPU6050_GYRO_XOUT_L				0x44
#define MPU6050_GYRO_YOUT_H				0x45
#define MPU6050_GYRO_YOUT_L				0x46
#define MPU6050_GYRO_ZOUT_H				0x47
#define MPU6050_GYRO_ZOUT_L				0x48
#define MPU6050_EXT_SENS_DATA_00		0x49
#define MPU6050_EXT_SENS_DATA_01		0x4a
#define MPU6050_EXT_SENS_DATA_02		0x4b
#define MPU6050_EXT_SENS_DATA_03		0x4c
#define MPU6050_EXT_SENS_DATA_04		0x4d
#define MPU6050_EXT_SENS_DATA_05		0x4e
#define MPU6050_EXT_SENS_DATA_06		0x4f
#define MPU6050_EXT_SENS_DATA_07		0x50
#define MPU6050_EXT_SENS_DATA_08		0x51
#define MPU6050_EXT_SENS_DATA_09		0x52
#define MPU6050_EXT_SENS_DATA_10		0x53
#define MPU6050_EXT_SENS_DATA_11		0x54
#define MPU6050_EXT_SENS_DATA_12		0x55
#define MPU6050_EXT_SENS_DATA_13		0x56
#define MPU6050_EXT_SENS_DATA_14		0x57
#define MPU6050_EXT_SENS_DATA_15		0x58
#define MPU6050_EXT_SENS_DATA_16		0x59
#define MPU6050_EXT_SENS_DATA_17		0x5a
#define MPU6050_EXT_SENS_DATA_18		0x5b
#define MPU6050_EXT_SENS_DATA_19		0x5c
#define MPU6050_EXT_SENS_DATA_20		0x5d
#define MPU6050_EXT_SENS_DATA_21		0x5e
#define MPU6050_EXT_SENS_DATA_22		0x5f
#define MPU6050_EXT_SENS_DATA_23		0x60
#define MPU6050_I2C_SLV0_DO				0x63
#define MPU6050_I2C_SLV1_DO				0x64
#define MPU6050_I2C_SLV2_DO				0x65
#define MPU6050_I2C_SLV3_DO				0x66
#define MPU6050_I2C_MST_DELAY_CTRL		0x67
#define MPU6050_SIGNAL_PATH_RESET		0x68
#define MPU6050_MOT_DETECT_CTRL			0x69
#define MPU6050_USER_CTRL				0x6a
#define MPU6050_PWR_MGMT_1				0x6b
#define MPU6050_PWR_MGMT_2				0x6c
#define MPU6050_FIFO_COUNTH				0x72
#define MPU6050_FIFO_COUNTL				0x73
#define MPU6050_FIFO_R_W				0x74
#define MPU6050_WHO_AM_I				0x75

typedef struct {
	int16_t ACCEL_X, ACCEL_Y, ACCEL_Z;
	int16_t GYRO_X, GYRO_Y, GYRO_Z;
	int16_t TEMP;						//actual temerature = TEMP / 340 + 36.53C
	float ACCEL_FS;						//full scale (g). Full scale = 32768 (16 bits)
	float GYRO_FS;						//full scale (d/s). Full scale = 32768 (16 bits)
	int16_t ACCEL_X_BIAS, ACCEL_Y_BIAS, ACCEL_Z_BIAS;
	int16_t GYRO_X_BIAS, GYRO_Y_BIAS, GYRO_Z_BIAS;
} MPU6050_T;

//global defines

//global variables

//macros

//read mpu6050
uint8_t mpu6050_read(uint8_t addr);

//write mpu6050
uint8_t mpu6050_write(uint8_t addr, uint8_t dat);

//initialize mpu6050
void mpu6050_init(MPU6050_T *mpu);

//caliberate mpu6050 - to generate the bias
void mpu6050_cal(MPU6050_T *mpu);

//read mpu6050 accel data
void mpu6050_reada(MPU6050_T *mpu);

//read mpu6050 gyro data
void mpu6050_readg(MPU6050_T *mpu);

//read mpu6050 temp
void mpu6050_readt(MPU6050_T *mpu);

//read mpu6050 accel, temp and gyro data
void mpu6050_reads(MPU6050_T *mpu);

//read the fifo
void mpu6050_fifo(void);

#endif
