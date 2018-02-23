#include "mpu6050.h"												//use mpu6050

//hardware configuration
//end hardware configuration

//global defines

//global variables
//debias variables
int16_t debias_ax=0;
int16_t debias_ay=0;
int16_t debias_az=0;
int16_t debias_gx=0;
int16_t debias_gy=0;
int16_t debias_gz=0;

//read mpu6050
uint8_t mpu6050_read(uint8_t addr) {
	uint8_t dat;
	i2c_start(); 													//start condition
	i2c_write(MPU6050_I2CADDR | I2C_CMD_WRITE); 					//second the id
	i2c_write(addr); 												//send the channel
	i2c_restart();													//restart
	i2c_write(MPU6050_I2CADDR | I2C_CMD_READ);						//send the read command
	dat=i2c_read(I2C_NOACK);										//read from mpu6050, no acknowledgement
	i2c_stop();
	return dat;
}

//write mpu6050
uint8_t mpu6050_write(uint8_t addr, uint8_t dat) {
	i2c_start(); 
	i2c_write(MPU6050_I2CADDR | I2C_CMD_WRITE); 
	i2c_write(addr); 
	i2c_write(dat); 
	i2c_stop();
	return 0;
}

//initialize mpu6050
//full default settings
//gyro sensitivity: 1000d/s
//accel sensitivity: 4g
void mpu6050_init(MPU6050_T *mpu) {
	//set up the chip
	mpu6050_write(MPU6050_PWR_MGMT_1, 0x00);						//wake up mpu6050
	mpu6050_write(MPU6050_SMPLRT_DIV, 0x07);						//set sampling rate divider.
	mpu6050_write(MPU6050_CONFIG,     0x06);						//set config: sync input disabled, dlpf set to 44Hz.
	mpu6050_write(MPU6050_GYRO_CONFIG,0x10);						//set gyro config: 0x00=250d/s, 0x08=500d/s, 0x10=1000d/s, 0x18=2000d/s
	mpu6050_write(MPU6050_ACCEL_CONFIG, 0x08);						//set accelerometer config: 0x00=2g, 0x08=4g, 0x10=8g, 0x18=16g. was 0x09
	mpu->ACCEL_FS = 4.0f / 32768;									//g reading, in 1/1000 of a g
	mpu->GYRO_FS = 250.0f / 32768;
}

//caliberate / debias the mpu
//mpu6050 has to be level during the caliberation
void mpu6050_cal(MPU6050_T *mpu) {
	int32_t sum[6]={0, 0, 0, 0, 0, 0};								//summation matrix. ax, ay, az, gx, gy, gz
	uint16_t count=256;												//caliberation count
	while (count--) {
		mpu6050_reada(mpu);
		sum[0]+=mpu->ACCEL_X;
		sum[1]+=mpu->ACCEL_Y;
		sum[2]+=mpu->ACCEL_Z;
		sum[3]+=mpu->GYRO_X;
		sum[4]+=mpu->GYRO_Y;
		sum[5]+=mpu->GYRO_Z;
	}
	mpu->ACCEL_X_BIAS=sum[0]/count;
	mpu->ACCEL_Y_BIAS=sum[1]/count;
	mpu->ACCEL_Z_BIAS=sum[2]/count;
	mpu->GYRO_X_BIAS=sum[3]/count;
	mpu->GYRO_Y_BIAS=sum[4]/count;
	mpu->GYRO_Z_BIAS=sum[5]/count;
}

//read mpu6050 accel data
void mpu6050_reada(MPU6050_T *mpu) {
	uint16_t dat;													//temp variable
	
	i2c_start(); 													//start condition
	i2c_write(MPU6050_I2CADDR | I2C_CMD_WRITE); 					//second the id
	i2c_write(MPU6050_ACCEL_XOUT_H); 								//send the channel
	
	//restart
	i2c_restart();													//restart
	i2c_write(MPU6050_I2CADDR | I2C_CMD_READ);						//send the read command
	
	//read accel_x
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_ACK);
#if defined(MPU6050_DEBIAS)
	mpu->ACCEL_X += ((int16_t) dat - mpu->ACCEL_X) >> MPU6050_DEBIAS_WT;
#else
	mpu->ACCEL_X = dat;
#endif
	
	//read accel_y
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_ACK);
#if defined(MPU6050_DEBIAS)
	mpu->ACCEL_Y += ((int16_t) dat - mpu->ACCEL_Y) >> MPU6050_DEBIAS_WT;
#else
	mpu->ACCEL_Y=dat;
#endif

	//read accel_z
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_NOACK);
#if defined(MPU6050_DEBIAS)
	mpu->ACCEL_Z += ((int16_t) dat - mpu->ACCEL_Z) >> MPU6050_DEBIAS_WT;
#else
	mpu->ACCEL_Z=dat;
#endif

	i2c_stop();
}

//read mpu6050 temp data
void mpu6050_readt(MPU6050_T *mpu) {
	uint16_t dat;													//temp variable
	
	i2c_start(); 													//start condition
	i2c_write(MPU6050_I2CADDR | I2C_CMD_WRITE); 					//second the id
	i2c_write(MPU6050_TEMP_OUT_H); 									//send the channel
	
	//restart
	i2c_restart();													//restart
	i2c_write(MPU6050_I2CADDR | I2C_CMD_READ);						//send the read command
	
	//read temp
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_NOACK);
	mpu->TEMP=dat;

	i2c_stop();
	
}

//read mpu6050 gyro data
void mpu6050_readg(MPU6050_T *mpu) {
	uint16_t dat;													//temp variable
	
	i2c_start(); 													//start condition
	i2c_write(MPU6050_I2CADDR | I2C_CMD_WRITE); 					//second the id
	i2c_write(MPU6050_GYRO_XOUT_H); 								//send the channel
	
	//restart
	i2c_restart();													//restart
	i2c_write(MPU6050_I2CADDR | I2C_CMD_READ);						//send the read command
	
	//read gyro_x
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_ACK);
#if defined(MPU6050_DEBIAS)
	mpu->GYRO_X += ((int16_t) dat - mpu->GYRO_X) >> MPU6050_DEBIAS_WT;
#else
	mpu->GYRO_X=dat;
#endif

	//read gyro_y
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_ACK);
#if defined(MPU6050_DEBIAS)
	mpu->GYRO_Y += ((int16_t) dat - mpu->GYRO_Y) >> MPU6050_DEBIAS_WT;
#else
	mpu->GYRO_Y=dat;
#endif

	//read gyro_z
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050, no acknowledgement
	dat|= i2c_read(I2C_NOACK);
#if defined(MPU6050_DEBIAS)
	mpu->GYRO_Z += ((int16_t) dat - mpu->GYRO_Z) >> MPU6050_DEBIAS_WT;
#else
	mpu->GYRO_Z=dat;
#endif

	i2c_stop();
	
}

//read mpu6050 accel, temp and gyro data
void mpu6050_reads(MPU6050_T *mpu) {
	uint16_t dat;													//temp variable
	
	i2c_start(); 													//start condition
	i2c_write(MPU6050_I2CADDR | I2C_CMD_WRITE); 					//second the id
	i2c_write(MPU6050_ACCEL_XOUT_H); 								//send the channel
	
	//restart
	i2c_restart();													//restart
	i2c_write(MPU6050_I2CADDR | I2C_CMD_READ);						//send the read command
	
	//read accel_x
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_ACK);
#if defined(MPU6050_DEBIAS)
	mpu->ACCEL_X += ((int16_t) dat - mpu->ACCEL_X) >> MPU6050_DEBIAS_WT;
#else
	mpu->ACCEL_X=dat;
#endif

	//read accel_y
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_ACK);
#if defined(MPU6050_DEBIAS)
	mpu->ACCEL_Y += ((int16_t) dat - mpu->ACCEL_Y) >> MPU6050_DEBIAS_WT;
#else
	mpu->ACCEL_Y=dat;
#endif

	//read accel_z
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_ACK);
#if defined(MPU6050_DEBIAS)
	mpu->ACCEL_Z += ((int16_t) dat - mpu->ACCEL_Z) >> MPU6050_DEBIAS_WT;
#else
	mpu->ACCEL_Z=dat;
#endif

	//read temp
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_ACK);
	mpu->TEMP=dat;

	//read gyro_x
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_ACK);
#if defined(MPU6050_DEBIAS)
	mpu->GYRO_X += ((int16_t) dat - mpu->GYRO_X) >> MPU6050_DEBIAS_WT;
#else
	mpu->GYRO_X=dat;
#endif

	//read gyro_y
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050,  acknowledgement
	dat|= i2c_read(I2C_ACK);
#if defined(MPU6050_DEBIAS)
	mpu->GYRO_Y += ((int16_t) dat - mpu->GYRO_Y) >> MPU6050_DEBIAS_WT;
#else
	mpu->GYRO_Y=dat;
#endif

	//read gyro_z
	dat = i2c_read(I2C_ACK)<<8;										//read from mpu6050, no acknowledgement
	dat|= i2c_read(I2C_NOACK);
#if defined(MPU6050_DEBIAS)
	mpu->GYRO_Z += ((int16_t) dat - mpu->GYRO_Z) >> MPU6050_DEBIAS_WT;
#else
	mpu->GYRO_Z=dat;
#endif

	i2c_stop();
	
}

//read the fifo - to be implemented
void mpu6050_fifo(void) {
}
