//servo driver user timer2. 
//assumptions:
//1. F_CPU = 1Mhz
//2. servo not sensitive to length of off-period: 10ms - 20ms

#include "srvo2.h"							//we use servo drivers from TIMER2

//hardware configuration
//#define SRVO_PORT		PORTC                //output port
//#define SRVO_DDR		TRISC 
#define SRVO_CNT		18					//number of servos supported
//end hardware configuration

//global defines
typedef struct {
	//volatile uint8_t *ddr;				//output direction register
	volatile uint8_t *port;					//port register
	uint8_t pin;							//servo pin mask, for 8-bit types
	uint16_t pr;							//on duration
} SRVO_TypeDef;



//global defines
#define SRVO_ON(srvo)	IO_SET(*(srvo.port), srvo.pin)
#define SRVO_OFF(srvo)	IO_CLR(*(srvo.port), srvo.pin)
#define PSDIV(us)		((us)>>2)			//convert us to tick. 4:1 prescaler -> check PS2..0 settings

//global variables
static volatile uint16_t _stmr_pr;					//servo timer period, in ticks
static volatile uint8_t _sindex;					//servo index from 0..SRVO_CNT
//servo definitions: pin mask + period
//pin mask = 0 -> output on that channel disabled
static SRVO_TypeDef srvos[SRVO_CNT+1] = {			//servos: running at 128:1 prescaler
	&PORTC, 0<<0, PSDIV(1000),						//for the off period: no output, 20,000 ticks
	&PORTA, 1<<0, PSDIV(1000),                     //servo ch 1, on PORTC, 1000 ticks
	&PORTB, 1<<4, PSDIV(1500),                     //servo ch 2, on PORTA, 1500 ticks
	&PORTA, 1<<2, PSDIV(2000),                     //servo ch 3, on PORTB, 2000 ticks
	&PORTB, 1<<6, PSDIV(1000),                     //servo ch 4, on PORTB, 2500 ticks
	&PORTA, 1<<4, PSDIV(1500),                     //servo ch 5, on PORTA, 5000 ticks
	&PORTB, 1<<7, PSDIV(2000),                     //servo ch 6, on PORTB, 2500 ticks
	&PORTC, 1<<0, PSDIV(1000),                     //servo ch 7, on PORTC, 5000 ticks
	&PORTC, 1<<1, PSDIV(2000),                     //servo ch 8, on PORTC, 2500 ticks
	&PORTC, 1<<2, PSDIV(1000),                     //servo ch 9, on PORTC, 2500 ticks
	&PORTC, 1<<3, PSDIV(2000),                     //servo ch 10, on PORTC, 2500 ticks
	&PORTC, 1<<4, PSDIV(1000),                     //servo ch 11, on PORTC, 2500 ticks
	&PORTC, 1<<5, PSDIV(2000),                     //servo ch 12, on PORTC, 2500 ticks
	&PORTC, 1<<6, PSDIV(1000),                     //servo ch 13, on PORTC, 2500 ticks
	&PORTC, 1<<7, PSDIV(2000),                     //servo ch 14, on PORTC, 2500 ticks
	&PORTB, 1<<3, PSDIV(1000),                     //servo ch 15, on PORTB, 2500 ticks
	&PORTB, 1<<2, PSDIV(2000),                     //servo ch 16, on PORTB, 2500 ticks
	&PORTB, 1<<1, PSDIV(1000),                     //servo ch 17, on PORTB, 2500 ticks
	&PORTB, 1<<0, PSDIV(2000),                     //servo ch 18, on PORTB, 2500 ticks
//	&TRISB, &PORTB, 1<<0, PSDIV(2000),             //servo ch 18, on PORTB, 2500 ticks - IF DDR is specified in the SRVO_TypeDef
};

//servor isr to be included in the interrupt routine
//example:
//void interrupt isr(void) {
//	srvo2_isr();							//insert tmr0 isr here
//	...										//other tasks
//}
void srvo2_isr(void) {
	if (TMR2IF) {								//timer0 overflow
		TMR2IF = 0;							//clear the flag
		if (_stmr_pr==0) {					//time has run out for this output?
			SRVO_OFF(srvos[_sindex]);	//turn off the previous servo
			_sindex = (_sindex == SRVO_CNT)?0:(_sindex+1);	//advance the servo index
			SRVO_ON(srvos[_sindex]);	//turn on the servo pin
			_stmr_pr = srvos[_sindex].pr;	//load the servo period
		}
		if ((_stmr_pr & 0xff00) == 0) {		//_strm_pr <=255?
			TMR2 = -_stmr_pr;				//load the offset
			_stmr_pr = 0;
		} else _stmr_pr -= 0x0100;			//if greater than 0x100, let the counter roll and just decrement the period
	}			
}


//initialize the servo using tmr0
//count on internal clock, 8:1 prescaler (4 to achieve a maximum period of 8*256*1us =~2ms)
void srvo2_init(void) {
	//initialize the variable
	TRISA = TRISB = TRISC = 0;					//all pins output
	
	//initialize the pin
	for (_sindex = 0; _sindex<=SRVO_CNT; _sindex++) {
		//IO_OUT(*(srvos[_sindex].ddr), srvos[_sindex].pin); 	//set as output
		SRVO_OFF(srvos[_sindex]);			//servo pin as output, idles low
	}	
	
	//configure the timer2
	TMR2ON = 0;								//stop the timer
	_sindex = 0;							//reset the servo index
	SRVO_ON(srvos[_sindex]);				//turn on the pin
	_stmr_pr = srvos[_sindex].pr;			//load the servo period
	if ((_stmr_pr & 0xff00) == 0) {			//_strm_pr <= 255?
		TMR2 = -_stmr_pr;					//load the offset
		_stmr_pr = 0;
	} else TMR0 = 0;						//reset TMR0
	//T0CS = 0;								//0->count on F_OSC/4
	T2CKPS1 = 0, T2CKPS0 = 1;				//0b00->prescaler = 4:1
	TOUTPS3 = 0, TOUTPS2 = TOUTPS1 = TOUTPS0 = 0;	//0b0000->post scaler = 1:1
	//PSA = 0;								//0->prescaler to timer0
	TMR2IF = 0;								//0->clear the flag
	TMR2IE = 1;								//1->enable tmr1 interrupt
	PEIE = 1;								//1->enable peripheral interrupt for timer1 - not needed for timer0
	TMR2ON = 1;								//1->start the timer
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
	//srvos[sindex].pr = PSDIV(pr);				//update the period
}


//change servo parameters - period
//user has to perform error checking
//pin = pin mask. 0 to disable a channel
void srvo2_setpr(uint8_t sindex, /*uint8_t pin, */uint16_t pr) {
	//srvos[sindex].pin = pin;					//update the pin mask
	srvos[sindex].pr = PSDIV(pr);				//update the period
}
