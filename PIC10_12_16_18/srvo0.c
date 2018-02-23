//servo driver user timer0. 
//assumptions:
//1. F_CPU = 1Mhz
//2. servo not sensitive to length of off-period: 10ms - 20ms

#include "srvo0.h"							//we use servo drivers from TIMER0

//hardware configuration
#define SRVO_PORT		LATB                //output port
#define SRVO_DDR		TRISB 
#define SRVO_CNT		8					//number of servos supported
//end hardware configuration

//global defines
typedef struct {
	uint8_t pin;							//servo pin mask, for 8-bit types
	uint16_t pr;							//on duration
} SRVO_TypeDef;



//global defines
#define SRVO_ON(pin)	IO_SET(SRVO_PORT, pin)
#define SRVO_OFF(pin)	IO_CLR(SRVO_PORT, pin)
#define PSDIV(us)		((us)>>3)			//convert us to tick. 8:1 prescaler -> check PS2..0 settings

//global variables
static volatile uint16_t _stmr_pr;					//servo timer period, in ticks
static volatile uint8_t _sindex;					//servo index from 0..SRVO_CNT
//servo definitions: pin mask + period
//pin mask = 0 -> output on that channel disabled
static SRVO_TypeDef srvos[SRVO_CNT+1] = {			//servos: running at 128:1 prescaler
	0<<0, PSDIV(20000),					//for the off period: no output, 20,000 ticks
	1<<0, PSDIV(1000),                     //servo ch 1, on GPIO0, 1000 ticks
	1<<1, PSDIV(1500),                     //servo ch 2, on GPIO1, 1500 ticks
	1<<2, PSDIV(2000),                     //servo ch 3, on GPIO2, 2000 ticks
	1<<3, PSDIV(2500),                     //servo ch 4, on GPIO4, 2500 ticks
	1<<4, PSDIV(5000),                     //servo ch 5, on GPIO5, 5000 ticks
	1<<5, PSDIV(2500),                     //servo ch 4, on GPIO4, 2500 ticks
	1<<6, PSDIV(5000),                     //servo ch 5, on GPIO5, 5000 ticks
	1<<7, PSDIV(2500),                     //servo ch 4, on GPIO4, 2500 ticks
};	

//servor isr to be included in the interrupt routine
//example:
//void interrupt isr(void) {
//	srvo0_isr();							//insert tmr0 isr here
//	...										//other tasks
//}
void srvo0_isr(void) {
	if (T0IF) {								//timer0 overflow
		T0IF = 0;							//clear the flag
		if (_stmr_pr==0) {					//time has run out for this output?
			SRVO_OFF(srvos[_sindex].pin);	//turn off the previous servo
			_sindex = (_sindex == SRVO_CNT)?0:(_sindex+1);	//advance the servo index
			SRVO_ON(srvos[_sindex].pin);	//turn on the servo pin
			_stmr_pr = srvos[_sindex].pr;	//load the servo period
		}
		if ((_stmr_pr & 0xff00) == 0) {		//_strm_pr <=255?
			TMR0 = -_stmr_pr;				//load the offset
			_stmr_pr = 0;
		} else _stmr_pr -= 0x0100;			//if greater than 0x100, let the counter roll and just decrement the period
	}			
}


//initialize the servo using tmr0
//count on internal clock, 8:1 prescaler (4 to achieve a maximum period of 8*256*1us =~2ms)
void srvo0_init(void) {
	//initialize the variable
	
	//initialize the pin
	for (_sindex = 0; _sindex<=SRVO_CNT; _sindex++) {
		IO_OUT(SRVO_DDR, srvos[_sindex].pin); IO_CLR(SRVO_PORT, srvos[_sindex].pin);	//servo pin as output, idles low
	}	
	
	//configure the timer1
	//TMR1ON = 0;							//stop the timer
	_sindex = 0;							//reset the servo index
	SRVO_ON(srvos[_sindex].pin);			//turn on the pin
	_stmr_pr = srvos[_sindex].pr;			//load the servo period
	if ((_stmr_pr & 0xff00) == 0) {			//_strm_pr <= 255?
		TMR0 = -_stmr_pr;					//load the offset
		_stmr_pr = 0;
	} else TMR0 = 0;						//reset TMR0
	T0CS = 0;								//0->count on F_OSC/4
	PS2=0, PS1 = 1, PS0 = 0;				//0b010->8:1	//T1CKPS1 = 0, T1CKPS0 = 0;				//0b00->prescaler = 2:1
	PSA = 0;								//0->prescaler to timer0
	T0IF = 0;								//0->clear the flag
	T0IE = 1;								//1->enable tmr1 interrupt
	//PEIE = 1;								//1->enable peripheral interrupt for timer1 - not needed for timer0
	//TMR1ON = 1;								//1->start the timer
}

#if 0
//initialize the servo using tmr0
//count on internal clock, 128:1 prescaler (128 to achieve a maximum period of 128*256*1us = 32.7ms
void srvo0_init1(void) {
	//initialize the variable
	
	//initialize the pin
	for (_sindex = 0; _sindex<=SRVO_CNT; _sindex++) {
		IO_OUT(SRVO_DDR, srvos[_sindex].pin); IO_CLR(SRVO_PORT, srvos[_sindex].pin);	//servo pin as output, idles low
	}	
	
	//configure the timer1
	//TMR1ON = 0;								//stop the timer
	_sindex = 0;							//reset the servo index
	TMR0 = -srvos[_sindex].pr;				//load servo period
	SRVO_ON(srvos[_sindex].pin);			//turn on the pin
	T0CS = 0;								//0->count on F_OSC/4
	PS2=0, PS1 = 1, PS0 = 0;				//0b010->8:1	//T1CKPS1 = 0, T1CKPS0 = 0;				//0b00->prescaler = 1:1
	PSA = 0;								//0->prescaler to timer0
	T0IF = 0;								//0->clear the flag
	T0IE = 1;								//1->enable tmr1 interrupt
	//PEIE = 1;								//1->enable peripheral interrupt
	//TMR1ON = 1;								//1->start the timer
}
#endif

//change servo parameters
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo0_set(uint8_t sindex, uint8_t pin, uint16_t pr) {
	srvos[sindex].pin = pin;					//update the pin mask
	srvos[sindex].pr = PSDIV(pr);				//update the period
}


//change servo parameters - pin
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo0_setpin(uint8_t sindex, uint8_t pin) {
	srvos[sindex].pin = pin;					//update the pin mask
	//srvos[sindex].pr = PSDIV(pr);				//update the period
}


//change servo parameters - period
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo0_setpr(uint8_t sindex, /*uint8_t pin, */uint16_t pr) {
	//srvos[sindex].pin = pin;					//update the pin mask
	srvos[sindex].pr = PSDIV(pr);				//update the period
}
