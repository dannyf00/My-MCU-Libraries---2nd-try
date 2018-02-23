#ifndef _L3GD20SPI_H
#define _L3GD20SPI_H

#include "gpio.h"									//we use gpio
#include "spi_sw.h"									//we use software spi

//hardware configuration
#define L3GD20CS_PORT		GPIOE
#define L3GD20CS_DDR		GPIOE
#define L3GD20CS			(1<<3)
//end hardware configuration

#define l3gd20_deselect(cs)	do {IO_SET(L3GD20CS_PORT, cs); IO_OUT(L3GD20CS_PORT, cs);} while (0)
#define l3gd20_select(cs)	do {IO_CLR(L3GD20CS_PORT, cs); IO_OUT(L3GD20CS_PORT, cs);} while (0)

typedef struct {
	//int16_t ACCEL_X, ACCEL_Y, ACCEL_Z;				//accelerometer readings on 3 axies
	int16_t GYRO_X, GYRO_Y, GYRO_Z;				//accelerometer readings on 3 axies
	int8_t TEMP;									//temperature readings
	uint8_t STATUS;
} L3GD20_T;

//global defines
//read / write bit
#define L3GD20_READ				0x80				//read
#define L3GD20_WRITE			0x00				//write

#define L3GD20_INC				0x40				//address auto increments for multi-byte read/write
#define L3GD20_STAY				0x00				//address does not increment

//register map
#define L3GD20_WHO_AM_I			0x0f
#define L3GD20_CTRL_REG1		0x20
#define L3GD20_CTRL_REG2		0x21
#define L3GD20_CTRL_REG3		0x22
#define L3GD20_CTRL_REG4		0x23
#define L3GD20_CTRL_REG5		0x24
#define L3GD20_REFERENCE		0x25
#define L3GD20_OUT_TEMP			0x26
#define L3GD20_STATUS_REG		0x27
#define L3GD20_OUT_X_L			0x28
#define L3GD20_OUT_X_H			0x29
#define L3GD20_OUT_Y_L			0x2a
#define L3GD20_OUT_Y_H			0x2b
#define L3GD20_OUT_Z_L			0x2c
#define L3GD20_OUT_Z_H			0x2d
#define L3GD20_FIFO_CTRL_REG	0x2e
#define L3GD20_FIFO_SRC_REG		0x2f
#define L3GD20_INT1_CFG			0x30
#define L3GD20_INT1_SRC			0x31
#define L3GD20_INT1_TSH_XH		0x32
#define L3GD20_INT1_TSH_XL		0x33
#define L3GD20_INT1_TSH_YH		0x34
#define L3GD20_INT1_TSH_YL		0x35
#define L3GD20_INT1_TSH_ZH		0x36
#define L3GD20_INT1_TSH_ZL		0x37
#define L3GD20_INT1_DURATION	0x38
//global variable

//initialize l3gd20
void l3gd20_init(void);

//read from l3gd20 accelerometer
L3GD20_T *l3gd20a_read(L3GD20_T *l3gd);

//read from l3gd20 temperature
L3GD20_T *l3gd20t_read(L3GD20_T *l3gd);

//read l3gd20 accelerometer + status + temperature
L3GD20_T *l3gd20_read(L3GD20_T *l3gd);

#endif
