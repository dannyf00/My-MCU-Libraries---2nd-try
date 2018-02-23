//#include <lpc210x.h>				//we use keil
//#include <avr/io.h>				//we use gcc-avr
//#include <pic.h>					//we use picc
//#include <string.h>
#include "7110.h"				//we use nokia 7110 lcd

//////////////////////////////////////////////////////////////////////////////////
// Description : This firmware for Nokia 7110 (SED1565 controller) 96*65 TEST  	//
// Hardware : 	MCU 16F886 , LCD NOKIA7110 / SED1565 Controller					//
// Firmware : 	Rev 0.2                                                        	//
// Date : 		10/15/2009                                                     	//
// by : 		Ken Li                                                        	//
// Compiler : 	PICC STD 9.60PL2 + hi-tide 3.13                         		//
//////////////////////////////////////////////////////////////////////////////////
/* revision history
 * v0.1:		LPC21xx implementation
 * v0.2:		ported to 16F886.
 *
 * */

/**********************************************************
               Global Variable
**********************************************************/
//char page;
//char x,y;

/********************************************************
              ASCII table for 5x7 dots font
********************************************************/

const char font5x7 [] = {
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
                  //0x78,0x46,0x41,0x46,0x78; // 7f &brvbar;
                  };

                  //7e,43,40,43,7e //&Uuml;
                  //7e,43,42,43,7e //&Ouml;
                  //1e,21,21,71,21 //&Ccedil;
                  //3c,42,53,53,72 //&ETH;

//change the following section if porting to a different platform
//#define lcd_set(bits)		lcd_port |= (bits)			//set bit x on lcd_port
//#define lcd_clr(bits)		lcd_port &=~(bits)			//clear bit x on lcd_port
#define lcd_set(bits)		IO_SET(lcd_port, bits)			//set bit x on lcd_port
#define lcd_clr(bits)		IO_CLR(lcd_port, bits)			//clear bit x on lcd_port
#define pin_setup(pins)		IO_OUT(lcd_dir, pins)	//set pins for output


/********************************************************
              lcd clear LCD function
********************************************************/
void lcd_clear(void) {												//clear the screen. takes about 100ms to execute @ 4mhz
	unsigned char col, page;
   	for (page=LCD_PAGE_MIN; page<=LCD_PAGE_MAX; page++)              // 9 page, fill display RAM with 0s.
   	{
        lcd_write_command(0xB0 | page);   		// page address ie:0xB0,0xB1,...,0xB7
        lcd_write_command(0x10 | (LCD_COL_OFFSET >>4));          	// 0x11, most  4 bit column address command 0001 0011
        lcd_write_command(0x0f & LCD_COL_OFFSET);          	// 0x02, least 4 bit column address command 0000 0011
        for (col=LCD_COL_MIN; col<LCD_COL_MAX;col++)      	// 96 column
   			lcd_write_data(0x00);				//wipe it clean
      }
}

/**********************************************************
               Reset LCD Function
**********************************************************/
void lcd_reset(void) {
	IO_SET(lcdcs_port, lcdcs);					//lcd_set(lcd_cs);							//select the lcd
	IO_CLR(lcdres_port, lcdres);				//lcd_clr(lcd_res);							//lcd_res low to reset the display. the lcd going into default state.
	delay_ms(1);								//give the lcd time to reset.
	IO_SET(lcdres_port, lcdres);				//lcd_set(lcd_res);							//pulling the lcd out of reset.
}

/**********************************************************
               Initial LCD Function
							 hardware specific
**********************************************************/
void lcd_init(void) {

	//setting up the output pins
	//pin_setup(lcd_cs | lcd_dc | lcd_sclk | lcd_sda | lcd_res);
	IO_SET(lcdres_port, lcdres); IO_OUT(lcdres_ddr, lcdres);
	IO_SET(lcdcs_port, lcdcs); IO_OUT(lcdcs_ddr, lcdcs);
	IO_OUT(lcddc_ddr, lcddc);
	IO_OUT(lcdsclk_ddr, lcdsclk);
	IO_OUT(lcdsda_ddr, lcdsda);
#if defined(lcd_led)
	IO_SET(lcdled_port, lcdled); IO_OUT(lcdled_ddr, lcdled);	//pin_setup(lcd_led);
#endif
	lcd_reset();
   // the following initialization sequence per datasheet. All needs to be done in 5ms. (X) where X is the command on pg 8-56 of datasheet

	lcd_write_command(lcd_normal); 				// 0b10100110 = 0xA6, lcd in normal display mode (0xA7/0b10100111 negative mode)
	lcd_write_command(adc_reverse); 			// (8) <ADC select> (0xA1/0b10100001 reverse lcd - 0xA0/0b10100000 select normal) - makes display upside down
	lcd_write_command(comm_normal); 			// (15) common output normal (0xC8 reverse)
	lcd_write_command(v5_ratio+0x02); 			// (17) V5 resistor ratio, from 0b00100000 to 0b00100111. adder from 0x00 to 0x07
	lcd_write_command(elec_vol); 				// (18) electronic volume mode, follow by contrast value
	lcd_write_command(0x2c);					//set the contrast to desired value between 0x00 and 0x3f (0x27 appears to be the lowest contrast)
	lcd_write_command(pow_ctrl+0x0f); 			// (16) power control set value (contrast level --> 0x00 lightest to 0x3F darkest), from 0b00101000 to 0b00101111.
   //this concludes the mandatory initialization, as specified on pg 8-56 of the datasheet

	lcd_write_command(lcd_on); 					// lcd on
//   lcd_write_command(lcd_all_off); 			// lcd normal display mode
}

/**********************************************************
               sent 8 bit data to LCD by series
**********************************************************/
void lcd_write_dorc(unsigned char byteforlcd) { // same lcdai 3310

	unsigned char mask = 0x80;					//msb first
	do {
		IO_CLR(lcdsclk_port, lcdsclk);			//lcd_clr(lcd_sclk);	//data sent on the rising edge of sclk line
//      delay_us(2);
		if ((byteforlcd & mask)) IO_SET(lcdsda_port, lcdsda);			//lcd_set(lcd_sda);		// tramission starts from D7, D6, .., D1, D0. if D7 is 0, send 0.
		else IO_CLR(lcdsda_port, lcdsda);								//lcd_clr(lcd_sda);

		IO_SET(lcdsclk_port, lcdsclk);			//lcd_set(lcd_sclk);						//clock out the data
		mask = mask >> 1;						//shift left the next bit.
	} while (mask);
// 	delay_us(10);
}

/**********************************************************
              Sent Command to LCD Function
**********************************************************/
void lcd_write_command(unsigned char byteforlcd_command) {
	IO_CLR(lcddc_port, lcddc);					//lcd_clr(lcd_dc);   							// dc=0 signals lcd command mode. A0 in the datasheet. dc=data or command.
	IO_CLR(lcdcs_port, lcdcs);					//lcd_clr(lcd_cs);   							// chip enabled, negative logic. _cs
	lcd_write_dorc(byteforlcd_command);			//send the command.
	IO_SET(lcdcs_port, lcdcs);					//lcd_set(lcd_cs);   							// chip disabled
}

/**********************************************************
               Sent Data to LCD Function
**********************************************************/
void lcd_write_data(unsigned char byteforlcd_data) {
	IO_SET(lcddc_port, lcddc);					//lcd_set(lcd_dc);   							// display data mode. A0 in the datasheet. dorc=data or command.
	IO_CLR(lcdcs_port, lcdcs);					//lcd_clr(lcd_cs);   							// chip enabled, negative logic. _cs
	lcd_write_dorc(byteforlcd_data);			//send the data.
	IO_SET(lcdcs_port, lcdcs);					//lcd_set(lcd_cs);   							// chip disabled
}

/**********************************************************
               goto xy position on LCD Function
**********************************************************/
void lcd_gotoxy(unsigned char lcd_row, unsigned char lcd_col) {	//lcy_row: 0 - 8 (8th column has only 1 line / D0, lcd_col: 0 - 15.
	char col_addr;
	lcd_write_command(0xB0 + lcd_row);       	// page address set. pg 8-48 in the datasheet.
	col_addr = LCD_COL_OFFSET+(lcd_col*6);		// each font has five columns + 1 blank column. xaddr: 0 - 95 on nokia 7110. with offset
	//lcd_1st_col=0x12: the first column of display starts here. Weird! the datasheet didn't mention it.
	lcd_write_command(0x10 | (col_addr>>4));    // column address 4 most bit set
	lcd_write_command(0x0f & col_addr);         // column address 4 least bit set
}

/**********************************************************
           Convert bitmap to charractor Function
**********************************************************/
void lcd_chr(unsigned char charsel, unsigned char attribute) {
	//char char_row, char_data;
	const unsigned char * font_ptr;
	int char_pos;

	if (charsel < ' '/*0x20*/) return;
	if (charsel > '~'/*0x7f*/) return;					//check for illegal characters

	//lcd_gotoxy(lcd_row, lcd_col);			//go to (lcd_row, lcd_col)
	char_pos=charsel-' ';
	font_ptr = font5x7 + (char_pos + (char_pos << 2));	//font data start at font5x7[char_pos * 5]
	if (attribute == LCD_REVERSE) {
		//for (char_row = 0; char_row < 5; char_row++) // 5 bytes. each char is 6 column + 8 row, with the last col being empty
		{
			//char_data=font5x7[char_pos/**5*/+char_row];
			//char_data = *font_ptr++;
	 		lcd_write_data(~*font_ptr++);       // send font data to lcd
	 		lcd_write_data(~*font_ptr++);       // send font data to lcd
	 		lcd_write_data(~*font_ptr++);       // send font data to lcd
	 		lcd_write_data(~*font_ptr++);       // send font data to lcd
	 		lcd_write_data(~*font_ptr++);       // send font data to lcd
			//lcd_write_data(char_data | attribute);
		}
		//   lcd_write_data(~0x00); // blank side pixels for each font, white char on black background
		lcd_write_data(~0x00);
		//lcd_write_data(0x00 | attribute); // blank side pixels for each font
	} else {
		//for (char_row = 0; char_row < 5; char_row++) // 5 bytes. each char is 6 column + 8 row, with the last col being empty
		{
			//char_data=font5x7[char_pos/**5*/+char_row];
			//char_data = *font_ptr++;
	 		//lcd_write_data(~char_data);		// send font data to lcd
			lcd_write_data(*font_ptr++ | attribute);
			lcd_write_data(*font_ptr++ | attribute);
			lcd_write_data(*font_ptr++ | attribute);
			lcd_write_data(*font_ptr++ | attribute);
			lcd_write_data(*font_ptr++ | attribute);
		}
		//   lcd_write_data(~0x00); 			// blank side pixels for each font, white char on black background
		//lcd_write_data(~0x00);
		lcd_write_data(0x00 | attribute); 		// blank side pixels for each font
	}
}

/**********************************************************
           Write a string at current screen position
**********************************************************/
void lcd_str(unsigned char lcd_row, unsigned char lcd_col, unsigned char *str, unsigned char attribute) {

	lcd_gotoxy(lcd_row, lcd_col);				//go to the current cursor
	while (*str)
		lcd_chr(*str++, attribute);
}

/**********************************************************
           Write a string at current screen position
**********************************************************/
//void lcd_display_attr(unsigned char LCD_Line, unsigned char *str, unsigned char attribute) {

//	lcd_str(LCD_Line, 0, str, attribute);
//}

/**********************************************************
 set/clear pixel at lcd_row and lcd_col
**********************************************************/
void lcd_pixel(unsigned char lcd_row, unsigned char lcd_col, unsigned char set_clr) { //row: 0 - 63, col: 0-131
 	char x,y;

// 	if (lcd_row>ROW_RES) return;
// 	if (lcd_col>COL_RES) return; 				//check for illegal addresses

 	x=lcd_row/8;
 	y=1<<(lcd_row % 8);
	lcd_write_command(0xB0 + x);       			// page address set. pg 8-48 in the datasheet.
	lcd_write_command(0x10 | (lcd_col>>4));     // column address 4 most bit set
	lcd_write_command(0x0f & lcd_col);          // column address 4 least bit set
 	lcd_write_data(y);
}
