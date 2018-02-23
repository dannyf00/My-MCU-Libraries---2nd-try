#include "pca9685.h"						//we use pca9685

//hardware configuration
//end hardware configuration

//global defines
#define PCA9685_PS		30					//default pwm prescaler = 25000000Hz / (4096*FREQ) - 1. default = 30 -> 200Hz freq

//global variables

//reset pca9865
void pca9685_init(void) {
	//reset the i2c module
	i2c_init();

#if defined(PCA9685_PS)
	//set prescaler
	i2c_start();								//send the start condition
	i2c_write((PCA9685_A50 | 0x80) | I2C_CMD_WRITE);	//send the write command
	i2c_write(0xfe);							//write to prescaler address
	i2c_write((PCA9685_PS<3)?3:PCA9685_PS);		//send the prescaler, minimum of 3
	i2c_stop();									//send stop condition
#endif
}

//write to pca9685
void pca9685_write(uint8_t addr, uint16_t on_tick, uint16_t off_tick) {
	i2c_start();								//send the start condition
	i2c_write((PCA9685_A50 | 0x80) | I2C_CMD_WRITE);	//send the write command
	i2c_write(addr);							//write to the control register address
	i2c_write(on_tick); i2c_write((on_tick>>8) & 0x0f);	//set on tick, lsb first
	i2c_write(off_tick); i2c_write((off_tick>>8) & 0x0f);	//set off tick, lsb first
	i2c_stop();									//send stop condition
}

