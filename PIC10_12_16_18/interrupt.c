#include <htc.h>					//we use picc
#include "gpio.h"
#include "rtc0.h"					//we use rtc0
#include "tmr1.h"					//we use tmr1
//#include "rtc1.h"					//we use tmr1
//#include "rtc2.h"					//we use tmr2
#include "interrupt.h"				//interrupt controller

void interrupt isr(void) {

#ifdef TMR0_IT
	//interrupt isr section for tmr0
	if (T0IE && T0IF) {
		T0IF = 0;					//clear the isr flag
		//TMR0+= tmr0_offset;			//load the offset
		//rtc0_update();
		_tmr0_isr_ptr();				//execute tmr0_isr handler
		//return;
	}
#endif

#ifdef TMR1_IT
	//interrupt isr section for tmr1
	if (TMR1IE && TMR1IF) {
		TMR1IF = 0;					//clear the isr flag
		TMR1H+=tmr1_offset >> 8;	//load up the offset
		TMR1L+=tmr1_offset & 0x00ff;
		//rtc1_update();
		_tmr1_isr_ptr();				//execute tmr1_isr handler
		//return;
	}
#endif

#ifdef TMR2_IT
	//interrupt isr section for tmr1
	if (TMR2IE && TMR2IF) {
		TMR2IF = 0;					//clear the isr flag
		//TMR2 updated automatically by PR2
		//rtc2_update();
		_tmr2_isr_ptr();				//execute tmr2_isr handler
		//return;
	}
#endif
}

