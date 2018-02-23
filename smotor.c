#include "smotor.h"							//unipolar stepper motor driver

//hardware configuration
//end hardware configuration

//global defines
#define SMOTOR_STPING	8					//number of steppings
#define SMOTOR_ON(pin)	IO_SET(SMOTOR_PORT, pin)
#define SMOTOR_OFF(pin)	IO_CLR(SMOTOR_PORT, pin)
#define SMOTOR_OUT(val)	SMOTOR_PORT = (SMOTOR_PORT & ~(SMOTOR_A | SMOTOR_B | SMOTOR_C | SMOTOR_D) | (val))

//global variables
const uint8_t *_stepping;
volatile uint8_t smotor_index=0;			//smotor current index
//full steps - less torque
const uint8_t _stepping1[SMOTOR_STPING]={
	1<<0, 1<<1, 1<<2, 1<<3,					//active high, D.C.B.A
	1<<0, 1<<1, 1<<2, 1<<3,					//active high, D.C.B.A
};
//alternate full steps - more torque
const uint8_t _stepping1a[SMOTOR_STPING]={
	(1<<3) | (1<<0), (1<<0) | (1<<1) , (1<<1) | (1<<2), (1<<2) | (1<<3),					//active high, D.C.B.A
	(1<<3) | (1<<0), (1<<0) | (1<<1) , (1<<1) | (1<<2), (1<<2) | (1<<3),					//active high, D.C.B.A
};
//half steps
const uint8_t _stepping2[SMOTOR_STPING]={
	1<<0, (1<<0) | (1<<1), 1<<1, (1<<1) | (1<<2),
	1<<2, (1<<2) | (1<<3), 1<<3, (1<<3) | (1<<0),					//active high, D.C.B.A
};
//volatile uint8_t smotor_val=0;				//smotor value

//reset the pins
void smotor_init(void) {
	//motor pins as output, start off
	IO_OUT(SMOTOR_DDR, SMOTOR_A | SMOTOR_B | SMOTOR_C | SMOTOR_D);
	SMOTOR_OFF(SMOTOR_A | SMOTOR_B | SMOTOR_C | SMOTOR_D);

	//default stepping map
	_stepping = _stepping1;
}

//rotate forward
void smotor_inc(void) {
	uint8_t smotor_val=0;					//temp value
	//update the index
	smotor_index=(smotor_index==(SMOTOR_STPING-1))?0:(smotor_index+1);
	//update smotor value
	smotor_val = (_stepping[smotor_index] & (1<<0))?SMOTOR_A:0;
	smotor_val|= (_stepping[smotor_index] & (1<<1))?SMOTOR_B:0;
	smotor_val|= (_stepping[smotor_index] & (1<<2))?SMOTOR_C:0;
	smotor_val|= (_stepping[smotor_index] & (1<<3))?SMOTOR_D:0;
	//output the smotor value
	SMOTOR_OUT(smotor_val);					//output the new value
}

//rotate backward
void smotor_dec(void) {
	uint8_t smotor_val=0;					//temp value
	//update the index
	smotor_index=(smotor_index==0)?(SMOTOR_STPING-1):(smotor_index-1);
	//update smotor value
	smotor_val = (_stepping[smotor_index] & (1<<0))?SMOTOR_A:0;
	smotor_val|= (_stepping[smotor_index] & (1<<1))?SMOTOR_B:0;
	smotor_val|= (_stepping[smotor_index] & (1<<2))?SMOTOR_C:0;
	smotor_val|= (_stepping[smotor_index] & (1<<3))?SMOTOR_D:0;
	//output the smotor value
	SMOTOR_OUT(smotor_val);					//output the new value
}
