#include "lsm303.h"									//we use lsm303

//hardware configuration
//end hardware configuration

//global defines

//global variables

//read from lsm303
uint8_t lsm303_read(uint8_t i2c_addr, uint8_t addr) {
	uint8_t dat;
	i2c_start(); 									//start condition
	i2c_write(i2c_addr | I2C_CMD_WRITE); 			//second the id
	i2c_write(addr); 								//send the channel
	i2c_restart();									//restart
	i2c_write(i2c_addr | I2C_CMD_READ);				//send the read command
	dat=i2c_read(I2C_NOACK);						//read from mpu6050, no acknowledgement
	i2c_stop();
	return dat;
}

//write to lsm303
uint8_t lsm303_write(uint8_t i2c_addr, uint8_t addr, uint8_t dat) {
	i2c_start(); 
	i2c_write(i2c_addr | I2C_CMD_WRITE); 
	i2c_write(addr); 
	i2c_write(dat); 
	i2c_stop();
	return 0;
}

//reset lsm303
void lsm303_init(void) {
	//reset accelerometer
	lsm303_write(LSM303ACCEL_I2CADDR, LSM303_CTRL_REG1_A,
		0x40 |										//power mode. 50Hz sampling
		0x00 |										//bit 3: 0=normal mode, 1=low power mode
		0x04 |										//Z axis enabled
		0x02 |										//Y axis enabled
		0x01 |										//X axis enabled
		0x00
	);
	//lsm303_write(LSM303ACCEL_I2CADDR, LSM303_CTRL_REG2_A, 0X00);
	//lsm303_write(LSM303ACCEL_I2CADDR, LSM303_CTRL_REG3_A, 0X00);
	lsm303_write(LSM303ACCEL_I2CADDR, LSM303_CTRL_REG4_A,
		0x00 |										//0x80: OUTPUT DATA continously updated
		0x00 |										//0x00 lsb (default), 0x40 (msb)
		0x00 |										//full scale: 0=2g, 1=4g, 2=8g, 3=16g
		0x08 |										//00: disable high resolution output. 0x08: enable high resolution output
		0x00 |										//spi interface selection. 0=4-wire, 1=3-wire
		0x00
	);

	//reset magnatometer
	lsm303_write(LSM303MAG_I2CADDR, LSM303_CRA_REG_M,
		0x80 |										//0x80: enable temperature sensor, 0x00: disable
		0x14 |										//minimum data rate = 30Hz
		0x00);
	
	lsm303_write(LSM303MAG_I2CADDR, LSM303_CRB_REG_M,
		(0x04 << 5) |								//gain setting. 0x01..0x07, left shift 5
		0x00);
	
	lsm303_write(LSM303MAG_I2CADDR, LSM303_MR_REG_M,
		0x00 |										//devicde mode: 0x00=continuous conversion, 0x01=single conversion, 0x02/0x03=sleep mode
		0x00);
	
}

//read ACCELEROMETER
LSM303_T *lsm303a_read(LSM303_T *lsm) {
	uint16_t dat;
	
	//read accelerometer
	i2c_start();									//send a start condition
	i2c_write(LSM303ACCEL_I2CADDR | I2C_CMD_WRITE);	//Send the write
	i2c_write(LSM303_OUT_X_L_A | (0x80));					//start with accelerometer X lsb
	i2c_restart();									//restart
	i2c_write(LSM303ACCEL_I2CADDR | I2C_CMD_READ);	//send the read
	
	//read accel x
	dat = i2c_read(I2C_ACK);
	dat|= i2c_read(I2C_ACK) << 8;					//lsb first
	lsm->ACCEL_X = dat;
	
	//read accel y
	dat = i2c_read(I2C_ACK);
	dat|= i2c_read(I2C_ACK) << 8;					//lsb first
	lsm->ACCEL_Y = dat;
	
	//read accel z
	dat = i2c_read(I2C_ACK);
	dat|= i2c_read(I2C_NOACK) << 8;					//lsb first
	lsm->ACCEL_Z = dat;
	
	i2c_stop();
	
	return lsm;
}

//read MAGNETOMETER
LSM303_T *lsm303m_read(LSM303_T *lsm) {
	uint16_t dat;
	
	//read magnetometer
	i2c_start();									//send a start condition
	i2c_write(LSM303MAG_I2CADDR | I2C_CMD_WRITE);	//Send the write
	i2c_write(LSM303_OUT_X_H_M | (0x80));					//start with accelerometer X lsb
	i2c_restart();									//restart
	i2c_write(LSM303MAG_I2CADDR | I2C_CMD_READ);	//send the read
	
	//read mag x
	dat = i2c_read(I2C_ACK) << 8;
	dat|= i2c_read(I2C_ACK);						//msb first
	lsm->MAG_X = dat;
	
	//read mag Z
	dat = i2c_read(I2C_ACK) << 8;
	dat|= i2c_read(I2C_ACK);						//msb first
	lsm->MAG_Z = dat;
	
	//read mag Y
	dat = i2c_read(I2C_ACK) << 8;
	dat|= i2c_read(I2C_NOACK);						//msb first
	lsm->MAG_Y = dat;
	i2c_stop();
	
	return lsm;
}

//read MAGNETOMETER temperature
LSM303_T *lsm303t_read(LSM303_T *lsm) {
	uint16_t dat;
	
	//read magnetometer temperature
	i2c_start();									//send a start condition
	i2c_write(LSM303MAG_I2CADDR | I2C_CMD_WRITE);	//Send the write
	i2c_write(LSM303_TEMP_OUT_H_M | (1<<7));					//start with accelerometer X lsb
	i2c_restart();									//restart
	i2c_write(LSM303MAG_I2CADDR | I2C_CMD_READ);	//send the read
	
	//read mag temperature
	dat = i2c_read(I2C_ACK) << 8;
	dat|= i2c_read(I2C_NOACK);						//msb first
	lsm->TEMP = dat;

	i2c_stop();
	
	return lsm;
}

//read lsm303, accelerometer + magnetometer
LSM303_T *lsm303_reads(LSM303_T *lsm) {
	lsm303a_read(lsm);								//read accelerometer
	lsm303m_read(lsm);								//read magnetometer
	lsm303t_read(lsm);								//read temperature
	return lsm;
}

void lsm303_read1(LSM303_T *lsm) {
	
	//read the accelerometer
	lsm->ACCEL_X=lsm303_read(LSM303ACCEL_I2CADDR, LSM303_OUT_X_L_A) | (lsm303_read(LSM303ACCEL_I2CADDR, LSM303_OUT_X_H_A) << 8);
	lsm->ACCEL_Y=lsm303_read(LSM303ACCEL_I2CADDR, LSM303_OUT_Y_L_A) | (lsm303_read(LSM303ACCEL_I2CADDR, LSM303_OUT_Y_H_A) << 8);
	lsm->ACCEL_Z=lsm303_read(LSM303ACCEL_I2CADDR, LSM303_OUT_Z_L_A) | (lsm303_read(LSM303ACCEL_I2CADDR, LSM303_OUT_Z_H_A) << 8);
	//read the magnetometer
	lsm->MAG_X=lsm303_read(LSM303MAG_I2CADDR, LSM303_OUT_X_L_M) | (lsm303_read(LSM303MAG_I2CADDR, LSM303_OUT_X_H_M) << 8);
	lsm->MAG_Y=lsm303_read(LSM303MAG_I2CADDR, LSM303_OUT_Y_L_M) | (lsm303_read(LSM303MAG_I2CADDR, LSM303_OUT_Y_H_M) << 8);
	lsm->MAG_Z=lsm303_read(LSM303MAG_I2CADDR, LSM303_OUT_Z_L_M) | (lsm303_read(LSM303MAG_I2CADDR, LSM303_OUT_Z_H_M) << 8);
	//read the temperature
	lsm->TEMP=lsm303_read(LSM303MAG_I2CADDR, LSM303_TEMP_OUT_L_M) | (lsm303_read(LSM303MAG_I2CADDR, LSM303_TEMP_OUT_H_M) << 8);
}
