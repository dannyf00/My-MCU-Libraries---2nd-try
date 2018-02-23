//driver for wii nunchuck
//**********warning***************
//you may have to slow down your i2c sufficiently (to 400kbps)
//for the connection to work
//**********Use 8 x NOP() initially*************
//initialization: need to wait for at least 100ms for power to come on

#ifndef WIINC_H_INCLUDED
#define WIINC_H_INCLUDED

//hardware configuration
//#define WiiNC_Add		0xa4			//nunchuck i2c address
//Normal readings:
//Joystick X: 0(far left), 140(center), 255 (far right)
//Joystick Y: 255(forward), 138 center, 0 (backward)
//Button C: 0(pressed), 1(not pressed)
//Button Z: 0(pressed), 1(not pressed)
//Accelerometer X: 77(tilt full left), 128 (center), 179(tilt full right)
//Accelerometer Y: 181(tilt full forward), 128 (center), 79(tilt full back)
//Accelerometer Z: 70(tilt upside down), 128 (center), 179(tilt full upright)

//end hardware configuration

#define WiiNC_Bc		(1<<1)			//button C, active low
#define WiiNC_Bz		(1<<0)			//Button Z, active low

typedef struct {
	unsigned char JsX;					//joystick x
	unsigned char JsY;					//youstick y
	unsigned char AccX;					//accelerometer X
	unsigned char AccY;					//accelerometer Y
	unsigned char AccZ;					//accelerometer Z
	unsigned char Button;
} WiiNC_T;

//reset the nunchuck
// Nunchuk Init: Initialize the nunchuk by sending I2C commands to make the
// nunchuk "active". This particlular routine is different than others, but
// this one works with generic/knockoffs such as the one I'm using.
void wiinc_init(void);

//read the nunchuck
void wiinc_read(WiiNC_T * wnc);


#endif // WIINC_H_INCLUDED
