#include "5110.h"					//we use nokia 5110 lcd

//hardware configuration
//end hardware configuration

//global defines
#define LCD_CMD			0				//dc=0 to send lcd command
#define LCD_DATA		1				//dc=1 to send lcd data

#define LCD_NORMAL		0x00		// normal black on green
#define LCD_UNDERLINE	0x80
#define LCD_STRIKE		0x10
#define LCD_OVERLINE	0x01
#define LCD_REVERSE		0xff		//green on black
#define LCD_SET			0x02		//set
#define LCD_CLR			0x04		//clear
#define LCD_XOR			0x08		//xor

//LCD display lines
#define LCD_Line0		0		//1st line of lcd display
#define LCD_Line1		1		//1st line of lcd display
#define LCD_Line2		2		//1st line of lcd display
#define LCD_Line3		3		//1st line of lcd display
#define LCD_Line4		4		//1st line of lcd display
#define LCD_Line5		5		//1st line of lcd display
#define LCD_Line6		6		//1st line of lcd display
#define LCD_Line7		7		//1st line of lcd display

//global variables
const unsigned char font5x7 [] = {
                  0x00,0x00,0x00,0x00,0x00,  // 20 space
                  0x00,0x00,0x5f,0x00,0x00,  // 21 !
                  0x00,0x07,0x00,0x07,0x00,  // 22 "
                  0x14,0x7f,0x14,0x7f,0x14,  // 23 #
                  0x24,0x2a,0x7f,0x2a,0x12,  // 24 $
                  0x23,0x13,0x08,0x64,0x62,  // 25 %
                  0x36,0x49,0x55,0x22,0x50,  // 26 &
                  0x00,0x05,0x03,0x00,0x00,  // 27 '
                  0x00,0x1c,0x22,0x41,0x00,  // 28 (
                  0x00,0x41,0x22,0x1c,0x00,  // 29 )
                  0x14,0x08,0x3e,0x08,0x14,  // 2a *
                  0x08,0x08,0x3e,0x08,0x08,  // 2b +
                  0x00,0x50,0x30,0x00,0x00,  // 2c ,
                  0x08,0x08,0x08,0x08,0x08,  // 2d -
                  0x00,0x60,0x60,0x00,0x00,  // 2e .
                  0x20,0x10,0x08,0x04,0x02,  // 2f /
                  0x3e,0x51,0x49,0x45,0x3e,  // 30 0
                  0x00,0x42,0x7f,0x40,0x00,  // 31 1
                  0x42,0x61,0x51,0x49,0x46,  // 32 2
                  0x21,0x41,0x45,0x4b,0x31,  // 33 3
                  0x18,0x14,0x12,0x7f,0x10,  // 34 4
                  0x27,0x45,0x45,0x45,0x39,  // 35 5
                  0x3c,0x4a,0x49,0x49,0x30,  // 36 6
                  0x01,0x71,0x09,0x05,0x03,  // 37 7
                  0x36,0x49,0x49,0x49,0x36,  // 38 8
                  0x06,0x49,0x49,0x29,0x1e,  // 39 9
                  0x00,0x36,0x36,0x00,0x00,  // 3a :
                  0x00,0x56,0x36,0x00,0x00,  // 3b ;
                  0x08,0x14,0x22,0x41,0x00,  // 3c <
                  0x14,0x14,0x14,0x14,0x14,  // 3d =
                  0x00,0x41,0x22,0x14,0x08,  // 3e >
                  0x02,0x01,0x51,0x09,0x06,  // 3f ?
                  0x32,0x49,0x79,0x41,0x3e,  // 40 @
                  0x7e,0x11,0x11,0x11,0x7e,  // 41 A
                  0x7f,0x49,0x49,0x49,0x36,  // 42 B
                  0x3e,0x41,0x41,0x41,0x22,  // 43 C
                  0x7f,0x41,0x41,0x22,0x1c,  // 44 D
                  0x7f,0x49,0x49,0x49,0x41,  // 45 E
                  0x7f,0x09,0x09,0x09,0x01,  // 46 F
                  0x3e,0x41,0x49,0x49,0x7a,  // 47 G
                  0x7f,0x08,0x08,0x08,0x7f,  // 48 H
                  0x00,0x41,0x7f,0x41,0x00,  // 49 I
                  0x20,0x40,0x41,0x3f,0x01,  // 4a J
                  0x7f,0x08,0x14,0x22,0x41,  // 4b K
                  0x7f,0x40,0x40,0x40,0x40,  // 4c L
                  0x7f,0x02,0x0c,0x02,0x7f,  // 4d M
                  0x7f,0x04,0x08,0x10,0x7f,  // 4e N
                  0x3e,0x41,0x41,0x41,0x3e,  // 4f O
                  0x7f,0x09,0x09,0x09,0x06,  // 50 P
                  0x3e,0x41,0x51,0x21,0x5e,  // 51 Q
                  0x7f,0x09,0x19,0x29,0x46,  // 52 R
                  0x46,0x49,0x49,0x49,0x31,  // 53 S
                  0x01,0x01,0x7f,0x01,0x01,  // 54 T
                  0x3f,0x40,0x40,0x40,0x3f,  // 55 U
                  0x1f,0x20,0x40,0x20,0x1f,  // 56 V
                  0x3f,0x40,0x38,0x40,0x3f,  // 57 W
                  0x63,0x14,0x08,0x14,0x63,  // 58 X
                  0x07,0x08,0x70,0x08,0x07,  // 59 Y
                  0x61,0x51,0x49,0x45,0x43,  // 5a Z
                  0x00,0x7f,0x41,0x41,0x00,  // 5b [
                  0x02,0x04,0x08,0x10,0x20,  // 5c 55
                  0x00,0x41,0x41,0x7f,0x00,  // 5d ]
                  0x04,0x02,0x01,0x02,0x04,  // 5e ^
                  0x40,0x40,0x40,0x40,0x40,  // 5f _
                  0x00,0x01,0x02,0x04,0x00,  // 60 `
                  0x20,0x54,0x54,0x54,0x78,  // 61 a
                  0x7f,0x48,0x44,0x44,0x38,  // 62 b
                  0x38,0x44,0x44,0x44,0x20,  // 63 c
                  0x38,0x44,0x44,0x48,0x7f,  // 64 d
                  0x38,0x54,0x54,0x54,0x18,  // 65 e
                  0x08,0x7e,0x09,0x01,0x02,  // 66 f
                  0x0c,0x52,0x52,0x52,0x3e,  // 67 g
                  0x7f,0x08,0x04,0x04,0x78,  // 68 h
                  0x00,0x44,0x7d,0x40,0x00,  // 69 i
                  0x20,0x40,0x44,0x3d,0x00,  // 6a j
                  0x7f,0x10,0x28,0x44,0x00,  // 6b k
                  0x00,0x41,0x7f,0x40,0x00,  // 6c l
                  0x7c,0x04,0x18,0x04,0x78,  // 6d m
                  0x7c,0x08,0x04,0x04,0x78,  // 6e n
                  0x38,0x44,0x44,0x44,0x38,  // 6f o
                  0x7c,0x14,0x14,0x14,0x08,  // 70 p
                  0x08,0x14,0x14,0x18,0x7c,  // 71 q
                  0x7c,0x08,0x04,0x04,0x08,  // 72 r
                  0x48,0x54,0x54,0x54,0x20,  // 73 s
                  0x04,0x3f,0x44,0x40,0x20,  // 74 t
                  0x3c,0x40,0x40,0x20,0x7c,  // 75 u
                  0x1c,0x20,0x40,0x20,0x1c,  // 76 v
                  0x3c,0x40,0x30,0x40,0x3c,  // 77 w
                  0x44,0x28,0x10,0x28,0x44,  // 78 x
                  0x0c,0x50,0x50,0x50,0x3c,  // 79 y
                  0x44,0x64,0x54,0x4c,0x44,  // 7a z
                  0x00,0x08,0x36,0x41,0x00,  // 7b {
                  0x00,0x00,0x7f,0x00,0x00,  // 7c |
                  0x00,0x41,0x36,0x08,0x00,  // 7d }
                  0x10,0x08,0x08,0x10,0x08,  // 7e ~
                  0x78,0x46,0x41,0x46,0x78}; // 7f &brvbar;

                  //7e,43,40,43,7e //&Uuml;
                  //7e,43,42,43,7e //&Ouml;
                  //1e,21,21,71,21 //&Ccedil;
                  //3c,42,53,53,72 //&ETH;


//write to the lcd
void lcd_write(uint8_t dat) {
	uint8_t mask = 0x80;					//mask, msb first
	
	//pull cs low to enable serial communications
	IO_CLR(lcdcs_port, lcdcs);
	do {
		IO_CLR(lcdsclk_port, lcdsclk);		//clear sclk -> data on the rising edge
		if (dat & mask) IO_SET(lcdsda_port, lcdsda);
		else IO_CLR(lcdsda_port, lcdsda);
		IO_SET(lcdsclk_port, lcdsclk);		//send data
		mask = mask >> 1;					//shift the next bit
	} while (mask);
	IO_SET(lcdcs_port, lcdcs);				//pull cs high to disable serial communications
	
}

//write command
void lcd_write_command(uint8_t cmd) {
	IO_CLR(lcddc_port, lcddc);				//clear dc to send command
	lcd_write(cmd);							//send the command
}

//write data
void lcd_write_data(uint8_t dat) {
	IO_SET(lcddc_port, lcddc);				//set dc to send data
	lcd_write(dat);							//send the data
}

//go to xy
//row: 0..5
//col: 0..83 (6 columns per char)
void lcd_gotoxy(uint8_t row, uint8_t col) {
	lcd_write_command(0x80 | col);			//send the column command
	lcd_write_command(0x40 | row);			//send the row command
}

//send a char to current position
void lcd_chr(const uint8_t chr, uint8_t attribute) {
	uint8_t index;
	const unsigned char * font_ptr;

	//check chr range
	if (chr < ' '/*0x20*/) return;
	if (chr > '~'/*0x7f*/) return;

	index=chr-' ';							//calculate the offset
	font_ptr = font5x7+(index + (index << 2));	//calculate the first column	
	//lcd_write_data(0x00);					//send an empty column
	if (attribute==LCD_REVERSE) {
		lcd_write_data(~*font_ptr++);			//send the 1st column
		lcd_write_data(~*font_ptr++);			//send the 2nd column
		lcd_write_data(~*font_ptr++);			//send the 3rd column
		lcd_write_data(~*font_ptr++);			//send the 4th column
		lcd_write_data(~*font_ptr++);			//send the 5th column
		lcd_write_data(~0x00);					//send the last / empty column
	} else {
		lcd_write_data(*font_ptr++ | attribute);			//send the 1st column
		lcd_write_data(*font_ptr++ | attribute);			//send the 2nd column
		lcd_write_data(*font_ptr++ | attribute);			//send the 3rd column
		lcd_write_data(*font_ptr++ | attribute);			//send the 4th column
		lcd_write_data(*font_ptr++ | attribute);			//send the 5th column
		lcd_write_data(0x00 | attribute);					//send the last / empty column
	}
}

//put strings
void lcd_str(uint8_t row, uint8_t col, uint8_t *str, uint8_t attribute) {
	lcd_gotoxy(row, col);					//go to the current cursor
	while (*str) lcd_chr(*str++, attribute);
}

/**********************************************************
           Write a string at current screen position
**********************************************************/
//void lcd_display_attr(uint8_t LCD_Line, uint8_t *str, uint8_t attribute) {
//
//	lcd_str(LCD_Line, 0, str, attribute);
//}

//send an image to current position
void lcd_img(uint8_t *img, uint8_t col_pix) {
	while (col_pix--) {
		lcd_write_data(*img++);			//send the 1st column
	}
	//lcd_write_data(~0x00);					//send the last / empty column
}


//clear the lcd
void lcd_clear(void) {
	uint8_t index;
	lcd_gotoxy(0,0);						//clear from the beginning
	for (index=0; index<(48/8)*(84/6); index++) {	//48/8 = 6 rows, 84/6=14 cols
		lcd_write_data(0x00);
		lcd_write_data(0x00);
		lcd_write_data(0x00);
		lcd_write_data(0x00);
		lcd_write_data(0x00);
		lcd_write_data(0x00);
	}
}

//soft reset the lcd
void lcd_reset(void) {
	IO_SET(lcdcs_port, lcdcs);				//pull up cs
	IO_CLR(lcdres_port, lcdres);			//clear reset
	delay_ms(1);							//wait a little
	IO_SET(lcdres_port, lcdres);			//pull up reset
}



//reset the lcd
void lcd_init(void) {
	//set up the pins
	IO_CLR(lcdres_port, lcdres);			//res low
	IO_CLR(lcdcs_port, lcdcs); IO_OUT(lcdcs_ddr, lcdcs);				//cs as output
	IO_CLR(lcddc_port, lcddc); IO_OUT(lcddc_ddr, lcddc);
	IO_CLR(lcdsda_port, lcdsda); IO_OUT(lcdsda_ddr, lcdsda);
	IO_CLR(lcdsclk_port, lcdsclk); IO_OUT(lcdsclk_ddr, lcdsclk);
	
	//set up the command
 	lcd_write_command(0x20 | 0x01);				//LcdWrite(LCD_C, 0x21 );  // LCD Extended Commands. Power-up, Vertical model, use extended instruction set
  	lcd_write_command(0x80 | 0x31);				//LcdWrite(LCD_C, 0xB1 );  // Set LCD Vop (Contrast). 
  	lcd_write_command(0x04 | 0x00);				//LcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04. 0x00..0x03
  	lcd_write_command(0x10 | 0x04);				//LcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13. 0x00..0x07
  	lcd_write_command(0x20 | 0x00);				//LcdWrite(LCD_C, 0x20 );  // LCD Basic Commands
  	lcd_write_command(0x08 | 0x04);				//LcdWrite(LCD_C, 0x0C );  // LCD in normal mode. 0x00=blank, 0x04=normal, 0x01=all segments on, 0x05=inverse mode
}

