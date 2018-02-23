//#include <avr/io.h>							//we use gcc-avr
//multiple servo driven by ATmega328p TIMER2
//assumptions:
//1. F_CPU = 1Mhz
//2. servo not sensitive to off-state timing (10ms - 20ms)

#include "srvo2.h"								//we use timer2 to drive multiple servos

//hardware configuration
#define SRVO_PORT			PORTD
#define SRVO_DDR			DDRD
#define SRVO_CNT			8				//srvo counts
//end hardware configuration

//global defines
#define SRVO_ON(pin)	IO_SET(SRVO_PORT, pin)
#define SRVO_OFF(pin)	IO_CLR(SRVO_PORT, pin)
#define PSDIV(us)		((us)>>3)			//convert us to tick. 8:1 prescaler -> check PS2..0 settings

typedef struct {
	uint8_t pin;							//servo pin mask, for 8-bit types
	uint16_t pr;							//on duration
} SRVO_TypeDef;


//global variables
static volatile uint16_t _stmr_pr;					//servo timer period, in ticks
static volatile uint8_t _sindex;					//servo index from 0..SRVO_CNT
//servo definitions: pin mask + period
//pin mask = 0 -> output on that channel disabled
//servo definitions: pin mask + period
//pin mask = 0 -> output on that channel disabled
static SRVO_TypeDef srvos[SRVO_CNT+1] = {			//servos: running at 128:1 prescaler
	{0<<0, PSDIV(10000)},					//for the off period: no output, 20,000 ticks
	{1<<0, PSDIV(1000)},                     //servo ch 1, on GPIO0, 1000 ticks
	{1<<1, PSDIV(1500)},                     //servo ch 2, on GPIO1, 1500 ticks
	{1<<2, PSDIV(2000)},                     //servo ch 3, on GPIO2, 2000 ticks
	{1<<3, PSDIV(2500)},                     //servo ch 4, on GPIO4, 2500 ticks
	{1<<4, PSDIV(5000)},                     //servo ch 5, on GPIO5, 5000 ticks
	{1<<5, PSDIV(7000)},                     //servo ch 5, on GPIO5, 5000 ticks
	{1<<6, PSDIV(8000)},                     //servo ch 5, on GPIO5, 5000 ticks
	{1<<7, PSDIV(9000)},                     //servo ch 5, on GPIO5, 5000 ticks
};

//servor isr to be included in the interrupt routine
ISR(TIMER2_OVF_vect) {
	//clear the flag
	if (_stmr_pr==0) {					//time has run out for this output?
		SRVO_OFF(srvos[_sindex].pin);	//turn off the previous servo
		_sindex = (_sindex == SRVO_CNT)?0:(_sindex+1);	//advance the servo index
		SRVO_ON(srvos[_sindex].pin);	//turn on the servo pin
		_stmr_pr = srvos[_sindex].pr;	//load the servo period
	}
	if ((_stmr_pr & 0xff00) == 0) {		//_strm_pr <=255?
		TCNT2 = -_stmr_pr;				//load the offset
		_stmr_pr = 0;
	} else _stmr_pr -= 0x0100;			//if greater than 0x100, let the counter roll and just decrement the period
}


//initialize the servo using tmr2
//count on internal clock, 8:1 prescaler (4 to achieve a maximum period of 8*256*1us =~2ms)
void srvo2_init(void) {
	//initialize the variable

	//initialize the pin
	for (_sindex = 0; _sindex<=SRVO_CNT; _sindex++) {
		IO_OUT(SRVO_DDR, srvos[_sindex].pin); IO_CLR(SRVO_PORT, srvos[_sindex].pin);	//servo pin as output, idles low
	}

	//configure the timer1
	//TMR1ON = 0;							//stop the timer
	TCCR2B = (TCCR2B &~0x07) | (0x00 & 0x07);	//stop timer2
	_sindex = 0;							//reset the servo index
	SRVO_ON(srvos[_sindex].pin);			//turn on the pin
	_stmr_pr = srvos[_sindex].pr;			//load the servo period
	if ((_stmr_pr & 0xff00) == 0) {			//_strm_pr <= 255?
		TCNT2 = -_stmr_pr;					//load the offset
		_stmr_pr = 0;
	} else TCNT2 = 0;						//reset TMR0
	TCCR2B = 	(0<<COM2A1) | (0<<COM2A0) |	//0b00->oc2a pins normal port operations
				(0<<COM2B1) | (0<<COM2B0) |	//0b00->oc2b pins normal port operations
				(0<<WGM21) | (0<<WGM20);	//wgm2..0=0b000->normal operation
	TCCR2B|= (0<<WGM22);					//wgm2..0=0b000->normal operation
	TIFR2 |= (1<<TOV2);						//clear overflow flag by writing '1' to it
	TIMSK2|= (1<<TOIE2);					//enable overflow interrupt
	TCCR2B = (TCCR2B &~0x07) | (0x02 & 0x07);	//prescaler set to 8:1, start the timer
	//PEIE = 1;								//1->enable peripheral interrupt for timer1 - not needed for timer0
	//TMR1ON = 1;								//1->start the timer
}

//change servo parameters
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo2_set(uint8_t sindex, uint8_t pin, uint16_t pr) {
	srvos[sindex].pin = pin;					//update the pin mask
	srvos[sindex].pr = PSDIV(pr);				//update the period
}


//change servo parameters - pin
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo2_setpin(uint8_t sindex, uint8_t pin) {
	srvos[sindex].pin = pin;					//update the pin mask
	//srvos[sindex].pr = pr;					//update the period
}


//change servo parameters - period
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo2_setpr(uint8_t sindex, /*uint8_t pin, */uint16_t pr) {
	//srvos[sindex].pin = pin;					//update the pin mask
	srvos[sindex].pr = PSDIV(pr);				//update the period
}

