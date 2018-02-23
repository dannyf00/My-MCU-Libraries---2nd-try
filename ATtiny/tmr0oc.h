#ifndef TMR0_H_INCLUDED
#define TMR0_H_INCLUDED

//#include <avr/io.h>							//we use gcc-avr
#include "gpio.h"
#include <avr/interrupt.h>					//we use interrupt

//hardware configuration
//end hardware configuration

//global defines
//prescaler settings
#define TMR0_NOCLK			0x00		//cs210=no clock selected
#define TMR0_PS1x			0x01		//clk/1
#define TMR0_PS8x			0x02		//clk/8
#define TMR0_PS64x			0x03		//clk/64
#define TMR0_PS256x			0x04		//clk/256
#define TMR0_PS1024x		0x05		//clk/1024
#define TMR0_EXTN			0x06		//external clock on Tn pin, negative transistion
#define TMR0_EXTP			0x07		//external clock on Tn pin, positive transistion
#define TMR0_PSMASK		0x07

//rtc period settings
//tmr period settings
#define TMR_us				(F_CPU / 1000 / 1000)		//1us period - minimum period
#define TMR_50us			(TMR_us * 50)				//50us
#define TMR_100us			(TMR_us * 100)				//100us
#define TMR_200us			(TMR_us * 200)				//200us
#define TMR_ms				(TMR_us * 1000)			//ms definition
#define TMR_1ms				(TMR_ms * 1)				//1ms
#define TMR_2ms				(TMR_ms * 2)				//2ms period
#define TMR_5ms				(TMR_ms * 5)				//5ms period
#define TMR_10ms			(TMR_ms * 10)				//10ms
#define TMR_20ms			(TMR_ms * 20)				//20ms period
#define TMR_50ms			(TMR_ms * 50)				//50ms period
//#define TMR_100ms			(TMR_ms * 100)				//100ms
//#define TMR_200ms			(TMR_ms * 200)				//200ms period
//#define TMR_500ms			(TMR_ms * 500)				//500ms period
//#define TMR_1000ms			(TMR_ms * 1000)				//1000ms
//#define TMR_2000ms			(TMR_ms * 2000)				//2000ms period
//#define TMR_5000ms			(TMR_ms * 5000)				//5000ms period
//#define TMR_10000ms			(TMR_ms * 10000)			//10000ms


//reset the tmr
void tmr0_init(unsigned char ps);

//set tmr1 isr ptr
void tmr0_act(void (*isr_ptr)(void));

//for output match ch a/b
void tmr0a_setpr(uint8_t pr);
void tmr0a_act(void (*isr_ptr)(void));
void tmr0b_setpr(uint8_t pr);
void tmr0b_act(void (*isr_ptr)(void));

#endif // TMR0_H_INCLUDED
