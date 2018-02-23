#ifndef AWU_H
#define AWU_H

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines
//timebase selector
#define AWU_TB0x			0x00		//no interrupt
#define AWU_TB1x			0x01		//timebase = 1x
#define AWU_TB2x			0x02		//timebase = 2x
#define AWU_TB4x			0x03		//timebase = 4x
#define AWU_TB8x			0x04		//timebase = 8x
#define AWU_TB16x			0x05		//timebase = 16x
#define AWU_TB32x			0x06		//timebase = 32x
#define AWU_TB64x			0x07		//timebase = 64x
#define AWU_TB128x			0x08		//timebase = 128x
#define AWU_TB256x			0x09		//timebase = 256x
#define AWU_TB512x			0x0a		//timebase = 512x
#define AWU_TB1024x			0x0b		//timebase = 1024x
#define AWU_TB2048x			0x0c		//timebase = 2048x
#define AWU_TB4096x			0x0d		//timebase = 4096x
#define AWU_TB10240x		0x0e		//timebase = 10240x
#define AWU_TB61440x		0x0f		//timebase = 61440x


//global variables

//reset awu
//may need to adjust TBR register for desired duration
void awu_init(uint8_t ps);

//install awu handler
void awu_act(void (*isr_ptr)(void));

#endif
