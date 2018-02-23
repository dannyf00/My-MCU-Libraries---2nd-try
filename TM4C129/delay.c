#include "delay.h"						//we use software delay


#define DLY_MS	(130)				//5000 @ 40Mhz F_CPU on lm4f120 launchpad kit

//delay a number of cycles
void delay(volatile int dly) {
	while (dly--) NOP();
}

//delay a few us
void delay_us(volatile uint32_t dly_us) {
	delay(dly_us);
	dly_us = dly_us >> 16;
	while (dly_us--) delay(0xffff);		//delay(1);	//adjust dly_us for f_cpu
}

//delay a few ms
void delay_ms(volatile uint32_t dly_ms) {
	while (dly_ms--) delay_us(DLY_MS * (F_CPU / 1000000ul));
}

