//module to drive unipolar motors
#include <regx51.h>							//we use keil c51
#include "gpio.h"
#include "unipolar.h"						//we use the unipolar motor driver

//hardware configuration
//end hardware configuration

#define UNI_ON(pins)		IO_SET(UNI_PORT, pins)	//low to drive the winding
#define UNI_OFF(pins)		IO_CLR(UNI_PORT, pins)	//high to stop the drive

#define UNI_FORWARD			0			//go forward
#define UNI_BACKWARD		1			//going backward
#define UNI_STOP			2			//stop - don't move


//motor phase, in 8 steps (4 steps repeating itself)
//A->AB->B->BC->C->CD->D->DA->loop back
code const unsigned char _uni_phase[]={	//motor phase
	UNI_A,								//A is on
	UNI_A | UNI_B,						//A and B are on
	UNI_B,								//B is on
	UNI_B | UNI_C,						//B and C are on
	UNI_C,								//C is on
	UNI_C | UNI_D,						//C and D are on
	UNI_D,								//D is on
	UNI_D | UNI_A						//D and A are on
	};

/*
//motor phase, in 4 steps (4 steps repeating itself)
//A->A->C->D->loop back
code const unsigned char _uni_phase[]={	//motor phase
	UNI_A,								//A is on
	UNI_B,								//B is on
	UNI_C,								//C is on
	UNI_D,								//D is on
	UNI_A,								//A is on
	UNI_B,								//B is on
	UNI_C,								//C is on
	UNI_D								//D is on
	};
*/

//initialize the ports
void uni_init(void) {
	UNI_OFF(UNI_A | UNI_B | UNI_C | UNI_D);	//set the pins
	IO_OUT(UNI_DDR, UNI_A | UNI_B | UNI_C | UNI_D);	//pins as output
}

//drive the motor in one direction
void uni_drive(unsigned char direction) {
	static unsigned char position=7;

	//process 4 phases
	if (_uni_phase[position] & UNI_A) UNI_ON(UNI_A);
	else UNI_OFF(UNI_A);

	if (_uni_phase[position] & UNI_B) UNI_ON(UNI_B);
	else UNI_OFF(UNI_B);

	if (_uni_phase[position] & UNI_C) UNI_ON(UNI_C);
	else UNI_OFF(UNI_C);

	if (_uni_phase[position] & UNI_D) UNI_ON(UNI_D);
	else UNI_OFF(UNI_D);

	//update stepping
	switch (direction) {
		case UNI_FORWARD: 		position = (position == 7)? 0: (position + 1);		//moving forward
								break;
		case UNI_BACKWARD:		position = (position == 0)? 7: (position - 1);		//moving backward
								break;
		default:				break; 	//does nothing
	}
}
