#ifndef USII2C_H_INCLUDED
#define USII2C_H_INCLUDED

//#include <avr/io.h>							//we use gcc-avr
#include "gpio.h"
#include "delay.h"							//we use software delays
//#include "usii2c.h"							//we use usispi

//hardware configuration
#define USII2C_PORT		PORTB
#define USII2C_PORT_IN	PINB
#define USII2C_DDR		DDRB
#define USII2C_SCL		(1<<2)
#define USII2C_SDA		(1<<0)
//end hardware configuration

//global defines
#define usii2c_dly(n)	do {NOP();} while (0)
#define I2C_ACK_ERROR	10
#define I2C_ACK			0
#define I2C_NOACK		1
#define I2C_CMD_READ	0x01
#define I2C_CMD_WRITE	0x00
//global variables

//reset the usi_i2c module
void i2c_init(void);

//send data via i2c
uint8_t i2c_write(uint8_t dat);

//read data via i2c
uint8_t i2c_read(uint8_t ack);

//send a start condition
void i2c_start(void);

//send a stop condition
void i2c_stop(void);

//send a restart = stop+start
void i2c_restart(void);

#endif // USII2C_H_INCLUDED
