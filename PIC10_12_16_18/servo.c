//using pic12f675 to drive a servo
//servo period defined by SERVO_PR
//servo's on time defined by servo_set() / _servo_dc
//tmr1 to generate SERVO_PR
//tmr0 to generate _servo_dc
//servo resolution defined by SERVO_MIN

#include <htc.h>						//we use picc
#include "gpio.h"
#include "servo.h"						//we use servo

//hardware configuration
//end hardware configuration

unsigned short _servo_dc=1000;			//SERVO dc (0..SERVO_PR), in  us
unsigned short _servo_counter=0;		//SERVO on counter

void interrupt isr(void) {
	if (T0IF) {							//tmr0 to generate SERVO_dly
		T0IF = 0;						//clear the flag
		TMR0 += - SERVO_MIN * (F_CPU / 1000000ul);	//load the offset
		_servo_counter+= SERVO_MIN;		//update _SERVO_counter;
		if (_servo_counter >= _servo_dc) {	//on time has been reached
			//_SERVO_counter = 0;		//reset SERVO counter
			T0IE = 0;					//disable the interrupt
			IO_CLR(SERVO_PORT, SERVO);	//clear the SERVO pin
		}
	}
	
	if (TMR1IF) {						//servo_pr has been reached
		TMR1IF = 0;						//clear the flag
		TMR1H+ = ((-SERVO_PR) * (F_CPU / 1000000ul)) >> 8;	//load the offset
		TMR1L+ = ((-SERVO_PR) * (F_CPU / 1000000ul));

		//set up tmr0
		TMR0 = - SERVO_MIN * (F_CPU / 1000000ul);	//load the offset
		//T0IF = 0;						//clear the flag
		T0IE = 1;						//enable the tmr0 interrupt

		//set the output pin
		IO_SET(SERVO_PORT, SERVO);		//set the SERVO pin
		_servo_counter = 0;				//reset SERVO counter
	}
}

//initialize the servo
void servo_init(void) {
	IO_CLR(SERVO_PORT, SERVO);			//clear SERVO0
	IO_OUT(SERVO_DDR, SERVO);			//SERVO0 as output

	//tmr1_init();						//initialize tmr1
	TMR1ON = 0;							//turn off the tmr
	TMR1CS = 0;							//clocked by F_CPU
	T1CKPS1=0, T1CKPS0=0;				//prescaler = 1:1
	TMR1H = ((-SERVO_PR) * (F_CPU / 1000000ul)) >> 8;	//load the offset
	TMR1L = (-SERVO_PR) * (F_CPU / 1000000ul);
	
	TMR1IF = 0;							//clear the flag
	TMR1IE = 1;							//enable the interrupt
	PEIE = 1;							//enable periopheral interrupt

	TMR1ON = 1;							//turn on the tmr
	
	//tmr0_init();						//initialize tmr0
	T0CS = 0;							//clocked by internal pulse
	PSA = 1;							//prescaler assigned to wdt
	//TMR0 = (-_SERVO_dc) * (F_CPU / 1000000ul);	//load the offset
	
	T0IF = 0;							//clear the flag
	T0IE = 0;							//not yet enable interrupt
}

//set servo dc
void servo_setdc(unsigned short dc) {
	_servo_dc = dc;						//set servo dc
}
