//#include <pic24.h>						//we use pic24f
//#include <string.h>						//we use strcpy
//#include "config.h"						//configuration words
//#include "gpio.h"
//#include "delay.h"						//we use software delay
#include "i2c_sw.h"						//we use software i2c
//#include "lcd_3wi.h"					//we use 3line lcd
//#include "misc.h"						//we use ultoa
#include "wiinc.h"						//we use wii nunchuck

//hardware configuration
#define WiiNC_Add		0xa4			//nunchuck i2c address
//end hardware configuration

//reset the nunchuck
// Nunchuk Init: Initialize the nunchuk by sending I2C commands to make the
// nunchuk "active". This particlular routine is different than others, but
// this one works with generic/knockoffs such as the one I'm using.
void wiinc_init(void) {
	i2c_start();						//send a start condition

	i2c_write(WiiNC_Add | I2C_CMD_WRITE);				//send wii nunchuck address
	i2c_write(0xf0);
	i2c_write(0x55);
	i2c_stop();

	i2c_start();
	i2c_write(WiiNC_Add | I2C_CMD_WRITE);
	i2c_write(0xfb);
	i2c_write(0x00);

	i2c_stop();

}

//read the nunchuck
void wiinc_read(WiiNC_T * wnc) {
	i2c_start();
	i2c_write(WiiNC_Add | I2C_CMD_WRITE);				//send wii nunchuck address
	i2c_write(0x00);					//reset the address to 0
	i2c_stop();

	i2c_start();
	i2c_write(WiiNC_Add | I2C_CMD_READ);	//read from the nunchuck
	wnc->JsX = i2c_read(I2C_ACK);		//read joystick x
	wnc->JsY = i2c_read(I2C_ACK);		//read joystick x
	wnc->AccX= i2c_read(I2C_ACK);		//read joystick x
	wnc->AccY= i2c_read(I2C_ACK);		//read joystick x
	wnc->AccZ= i2c_read(I2C_ACK);		//read joystick x
	wnc->Button= i2c_read(I2C_NOACK);		//read joystick x
	i2c_stop();
}

