//driving multiple servos with TIMER1
//assumptions;
//F_CPU = 1Mhz
//servos not sensitive to off period intervals (10ms - 20ms)

#include "srvo1.h"							//we use srvo driver from timer1

//hardware configuration
#define SRVO_PORT		GPIO
#define SRVO_DDR		TRISIO
#define SRVO_CNT		1					//number of servos supported
//end hardware configuration

//global defines
typedef struct {
	uint8_t pin;							//servo pin mask, for 8-bit types
	uint16_t pr;							//off duration
} SRVO_TypeDef;

//global defines
#define SRVO_ON(pin)	IO_SET(SRVO_PORT, pin)
#define SRVO_OFF(pin)	IO_CLR(SRVO_PORT, pin)
#define PSDIV(us)		((us)>>0)			//convert us to tick. 1:1 prescaler -> check PS2..0 settings

//global variables
volatile uint16_t _stmr_pr;					//servo timer period
volatile uint8_t _sindex;					//servo index from 0..SRVO_CNT
//servo definitions: pin mask + period
SRVO_TypeDef srvos[SRVO_CNT+1] = {			//servos
	0<<0, PSDIV(10000),					//for the off period - do not change
	1<<0, PSDIV(10000),					//output on gpio1
};	


//servor isr to be included in the interrupt routine
//example:
//void interrupt isr(void) {
//	srvo1_isr();							//insert tmr1 isr here
//	...										//other tasks
//}
void srvo1_isr(void) {
	if (TMR1IF) {							//timer1 overflow
		TMR1IF = 0;							//clera the flag
		if (_stmr_pr==0) {					//time has run out for this period
			SRVO_OFF(srvos[_sindex].pin);		//turn off the previous servo
			_sindex = (_sindex == SRVO_CNT)?0:(_sindex+1);	//advance servo index
			SRVO_ON(srvos[_sindex].pin);		//turn on the servo pin
			_stmr_pr = srvos[_sindex].pr;			//load the servo period
		}
		if ((_stmr_pr & 0xffff0000ul) == 0) {	//time is less than 16-bit ticks
			TMR1 = -_stmr_pr;				//load the offset;
			_stmr_pr = 0;					//reset _stmr_pr
		} else _stmr_pr -= 0x10000ul;		//update _stmr_pr
	}			
}

//initialize the servo using tmr1
//count on internal clock, 1:1 prescaler
void srvo1_init(void) {
	//initialize the variable
	

	//initialize the pin
	for (_sindex = 0; _sindex<=SRVO_CNT; _sindex++) {
		IO_OUT(SRVO_DDR, (srvos[_sindex].pin)); 
		IO_CLR(SRVO_PORT, (srvos[_sindex].pin));	//servo pin as output, idles low
	}	
	
	//configure the timer1
	TMR1ON = 0;								//stop the timer
	_sindex = 0;							//reset the servo index
	TMR1 = -srvos[_sindex].pr;				//load servo period
	SRVO_ON(srvos[_sindex].pin);			//turn on the pin
#if defined(TMR1CS1)
	TMR1CS1 = TMR1CS0 = 0;					//count on internal clock F_OSC/4
#else
	TMR1CS = 0;								//0->count on F_OSC/4
#endif
	T1CKPS1 = 0, T1CKPS0 = 0;				//0b00->prescaler = 1:1
	TMR1IF = 0;								//0->clear the flag
	TMR1IE = 1;								//1->enable tmr1 interrupt
	PEIE = 1;								//1->enable peripheral interrupt
	TMR1ON = 1;								//1->start the timer
}

//change servo parameters
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo1_set(uint8_t sindex, uint8_t pin, uint16_t pr) {
	srvos[sindex].pin = pin;				//update the pin mask
	srvos[sindex].pr = PSDIV(pr);			//update the period
}


//change servo parameters - pin
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo1_setpin(uint8_t sindex, uint8_t pin) {
	srvos[sindex].pin = pin;				//update the pin mask
	//srvos[sindex].pr = PSDIV(pr);			//update the period
}


//change servo parameters - period
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo1_setpr(uint8_t sindex, /*uint8_t pin, */uint16_t pr) {
	//srvos[sindex].pin = pin;				//update the pin mask
	srvos[sindex].pr = PSDIV(pr);			//update the period
}

