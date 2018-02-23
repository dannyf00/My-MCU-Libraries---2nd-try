#ifndef _TMR1_H
#define _TMR1_H
//header file to use tmr1

#include "gpio.h"

#define TMR1_NOCLK			0x00		//cs210=no clock selected
#define TMR1_PS1x			0x01		//clk/1
#define TMR1_PS2x			0x02		//clk/2
#define TMR1_PS4x			0x03		//clk/4
#define TMR1_PS8x			0x04		//clk/8
#define TMR1_PS16x			0x05		//clk/8
#define TMR1_PS32x			0x06		//clk/32
#define TMR1_PS64x			0x07		//clk/64
#define TMR1_PS128x			0x08		//clk/64
#define TMR1_PS256x			0x09		//clk/256
#define TMR1_PS512x			0x0a		//clk/256
#define TMR1_PS1024x		0x0b		//clk/1024
#define TMR1_PS2048x		0x0c		//clk/1024
#define TMR1_PS4096x		0x0d		//clk/1024
#define TMR1_PS8192x		0x0e		//clk/1024
#define TMR1_PS16384x		0x0f		//clk/1024
#define TMR1_PSMASK			TMR1_PS16384x

//tmr period settings
#define TMR_ms				(F_CPU / 1000)				//1ms period - minimum period
#define TMR_1ms				(TMR_ms * 1)				//1ms
#define TMR_2ms				(TMR_ms * 2)				//2ms period
#define TMR_5ms				(TMR_ms * 5)				//5ms period
#define TMR_10ms			(TMR_ms * 10)				//10ms
#define TMR_20ms			(TMR_ms * 20)				//20ms period
#define TMR_50ms			(TMR_ms * 50)				//50ms period
#define TMR_100ms			(TMR_ms * 100)				//100ms
#define TMR_200ms			(TMR_ms * 200)				//200ms period
#define TMR_500ms			(TMR_ms * 500)				//500ms period
#define TMR_1000ms			(TMR_ms * 1000)				//1000ms
#define TMR_2000ms			(TMR_ms * 2000)				//2000ms period
#define TMR_5000ms			(TMR_ms * 5000)				//5000ms period
#define TMR_10000ms			(TMR_ms * 10000)			//10000ms

//reset the tmr
void tmr1_init(uint8_t prescaler, uint16_t period);

//set tmr1 isr ptr
void tmr1_act(void (*isr_ptr)(void));
#endif
