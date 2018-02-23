#ifndef SERVO_H_
#define SERVO_H_

//using pic12f675 to drive a servo
//servo period defined by SERVO_PR
//servo's on time defined by servo_set() / _servo_dc
//tmr1 to generate SERVO_PR
//tmr0 to generate _servo_dc
//servo resolution defined by SERVO_MIN

//hardware configuration
#define SERVO_PORT		GPIO
#define SERVO_DDR		TRISIO
#define SERVO			(1<<0)			//servo output pin
#define SERVO_PR		(20000)			//SERVO peroid, in us. 16-bit. watch for overflow
#define SERVO_MIN		50				//SERVO duty cycle minimum resolution, in  us
//end hardware configuration

//set servo dc
void servo_setdc(unsigned short dc);

//initialize the servo
void servo_init(void);

#endif /*SERVO_H_*/

