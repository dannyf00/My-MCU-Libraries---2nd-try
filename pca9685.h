#ifndef PCA9685_H_INCLUDED
#define PCA9685_H_INCLUDED

//#include <avr/io.h>						//we use gcc-avr
#include "gpio.h"
//#include "delay.h"						//we use software delays
#include "i2c_sw.h"							//we use software i2c

//hardware configuration
#define PCA9685_A50		0x10				//0x1A5..0
//end hardware configuration

//global defines

//global variables

//reset pca9865
void pca9685_init(void);

//write to pca9685
void pca9685_write(uint8_t addr, uint16_t on_tick, uint16_t off_tick);

//set period and duty cycle - period fixed to 4096
#define pca9685_set(ch, dc)		pca9685_write(0x06 + ((ch) & 0x0f) * 4, 0, (dc))

//set all channels
#define pca9685_setall(dc) 		pca9685_write(250, 0, (dc))	//channel ALL at 250

#endif // PCA9685_H_INCLUDED
