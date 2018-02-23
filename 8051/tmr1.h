#ifndef __TMR1_H
#define __TMR1_H

//initialize the timer
//prescaler not used - for compatability reasons only
//8-bit period

#define TMR1_16BIT						//if use 16-bit timer

//predefined intervals for the rtc
#define TMR_ms					(F_CPU / 1000)				//how many ticks to trigger in 1ms
#define TMR_1ms					(TMR_ms * 1)			//how many ticks to trigger in 1ms
#define TMR_2ms					(TMR_ms * 2)			//how many ticks to trigger in 2ms
#define TMR_5ms					(TMR_ms * 5)			//how many ticks to trigger in 5ms
#define TMR_10ms				(TMR_ms * 10)			//how many ticks to trigger in 10ms
#define TMR_20ms				(TMR_ms * 20)			//how many ticks to trigger in 20ms
#define TMR_50ms				(TMR_ms * 50)			//how many ticks to trigger in 50ms

#ifdef TMR1_16BIT
	void tmr1_init(unsigned char prescaler, unsigned short period);
#else
	void tmr1_init(unsigned char prescaler, unsigned char period);
#endif
//set up the isr handler
void tmr1_act(void (*isr_ptr)(void));	//set up the isr pointer


#endif //tmr1_h
