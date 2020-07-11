#ifndef _SSD1306_H					//driver for ssd1306 oled displays
#define _SSD1306_H

#include "gpio.h"					//we use F_CPU + gpio functions
#include "i2c1_sw.h"				//we use software i2c

//hardware configuration
#define SSD_ADDR		0x78					//0x7a or 0x78
//end hardware configuration

//global defines

//global variables


//performance stats, on a STM32F100RB, //number of ticks / 10
		//ssd_writes6x8(0, 0, vRAM);				//3770
		//ssd_writes8x16(0, 0, vRAM);				//8432
		//ssd_writes10x16(0, 0, vRAM);				//9502
		//ssd_writes14x24(0, 0, vRAM);				//17373
		//ssd_writes16x32(0, 0, vRAM);				//25071
		//ssd_writes(0, 0, vRAM, font6x8);			//3602
		//ssd_writes(0, 0, vRAM, font8x16);			//8270
		//ssd_writes(0, 0, vRAM, font10x16);		//9342
		//ssd_writes(0, 0, vRAM, font14x24);		//17226
		//ssd_writes(0, 0, vRAM, font16x32);		//25110

//font maps
extern const char font6x8[];
extern const char font8x16[];
extern const char font10x16[];
extern const char font12x16[];
extern const char font14x24[];
extern const char font16x32[];
//map structure: first four bytes = width, height, first char and last char
//followed by bitmap data

//text rendering function
void ssd_writec(char page, char col, char ch, const char *font);
void ssd_writes(char page, char col, char*ch, const char *font);

//write char 6x8 font
//void ssd_writec6x8(char page, char col, char ch);
#define ssd_writec6x8(page, col, ch)		ssd_writec(page, col, ch, font6x8)
//write a strong, null-terminated, 6x8 font
//void ssd_writes6x8(char page, char col, char *str);
#define ssd_writes6x8(page, col, str)		ssd_writes(page, col, str, font6x8)

//write char 8x16 font
//void ssd_writec8x16(char page, char col, char ch);
#define ssd_writec8x16(page, col, ch)		ssd_writec(page, col, ch, font8x16)

//write a strong, null-terminated, 8x16 font
//void ssd_writes8x16(char page, char col, char *str);
#define ssd_writes8x16(page, col, str)		ssd_writes(page, col, str, font8x16)

//write char 10x16 font
//void ssd_writec10x16(char page, char col, char ch);
#define ssd_writec10x16(page, col, ch)		ssd_writec(page, col, ch, font10x16)

//write a strong, null-terminated, 10x16 font
//void ssd_writes10x16(char page, char col, char *str);
#define ssd_writes10x16(page, col, str)		ssd_writes(page, col, str, font10x16)

//write char 12x16 font
#define ssd_writec12x16(page, col, ch)		ssd_writec(page, col, ch, font12x16)

//write a strong, null-terminated, 12x16 font
#define ssd_writes12x16(page, col, str)		ssd_writes(page, col, str, font12x16)

//write char 14x24 font - numbers only
//void ssd_writec14x24(char page, char col, char ch);
#define ssd_writec14x24(page, col, ch)		ssd_writec(page, col, ch, font14x24)

//write a strong, null-terminated, 14x24 font, numbers only
//void ssd_writes14x24(char page, char col, char *str);
#define ssd_writes14x24(page, col, str)		ssd_writes(page, col, str, font14x24)

//write char 16x32 font - numbers only
//void ssd_writec16x32(char page, char col, char ch);
#define ssd_writec16x32(page, col, ch)		ssd_writec(page, col, ch, font16x32)

//write a strong, null-terminated, 16x32 font, numbers only
//void ssd_writes16x32(char page, char col, char *str);
#define ssd_writes16x32(page, col, str)		ssd_writes(page, col, str, font16x32)

//go to a x/page (0..7) and y/col(0..127)
void ssd_gotoxy(char page, char col);

//go to a row/page - for compatability with old code
#define ssd_goto(line)		ssd_gotoxy(line, 0)

//clear screen
void ssd_clear(void);

//initilize the display
void ssd_init(void);

#endif
