/*
 *	LCD interface example
 *	Uses routines from delay.c
 *	This code will interface to a standard LCD controller
 *	like the Hitachi HD44780. It uses it in 4 bit mode, with
 *	the hardware connected as follows (the standard 14 pin
 *	LCD connector is used):
 *
 *	LCD_DATA bits, defined by D4..7, are connected to the LCD data bits 4-7 (high nibble)
 *	PORTA bit 3 is connected to the LCD RS input (register select)
 *	PORTA bit 1 is connected to the LCD EN bit (enable)
 *
 *	To use these routines, set up the port I/O (TRISA, TRISD) then
 *	call lcd_init(), then other routines as required.
 *
 */

/*	design parameters:
 * LC / Frequency meter with user calibration capabilities
 * chip: 	PIC12F675
 * LCD:		HD44780 or compatable, in 4-bit mode and in 3-wire interface
 *   		based on Micah Carrick's hardware design (74hc164).
 * compiler:picc std 9.60pl2
 * IDE:		hi-tide
 *
 * revision history:
 * v0.1		initial porting to pic
 *
 */

//#include	<regx51.h>
//#include <iostm8.h>
//#include <htc.h>						//we use pic
//#include <p24fxxxx.h>					//we use pic24f
//#include <avr/io.h>						//we use gcc-avr
#include "lcd_3wi.h"

#define SPI_CLK	LCD_SCK			//to maintain portability with the spi routines
#define SPI_OUT	LCD_SI			//LCD_RS line also serves as the SPI_OUT dataline

//#define init_ctrl()				IO_OUT(LCD_DIR, LCD_EN | LCD_SCK | LCD_SI)	//LCD_RS, LCD_EN, LCD_RS and LCD_CLK in output mode

//may need to adjust based on compiler optimization settings -> approximately 2ms or more per 16 characters / row
#  if F_CPU > 64000000ul
	#define lcd_delay()				{NOP64(); /*NOP();*/}	//delay(0)		//lcd delay for 20Mhz or higher
#elif F_CPU > 32000000ul
	#define lcd_delay()				{NOP32(); /*NOP();*/}	//delay(0)		//lcd delay for 20Mhz or higher
#elif F_CPU > 16000000ul
	#define lcd_delay()				{NOP16(); /*NOP();*/}	//delay(0)		//lcd delay for 20Mhz or higher
#elif F_CPU > 8000000ul
	#define lcd_delay()				{NOP8(); /*NOP();*/}	//delay(0)		//lcd delay for 20Mhz or higher
#elif F_CPU > 4000000ul
	#define lcd_delay()				{NOP4(); /*NOP();*/}	//delay(0)		//lcd delay for 20Mhz or higher
#else
	#define lcd_delay()				{NOP2(); /*NOP();*/}						//no delay needed for low speed mcu
#endif

#define	LCD_STROBE(rs)	{if (rs) LCD_SET(LCD_RS); else LCD_CLR(LCD_RS); /*lcd_delay(); */LCD_SET(LCD_EN); lcd_delay(); LCD_CLR(LCD_EN);}	//strobe out the data/control

//send a char to the shift register
void spi_send_byte(unsigned char c) {
    unsigned char mask;

    //Enable SPI communication. The SPI Enable signal must be pulsed low for each byte to be sent!
    //SPI_CLK = 0;

    //Ensure a minimum delay of 500ns between falling edge of SPI Enable signal
    //and rising edge of SPI Clock!
    //NOP();

#if 1
	mask = 0x80;                	//Initialize to write and read bit 7
    do  {
		LCD_CLR(SPI_CLK);
		if (c & mask) LCD_SET(SPI_OUT);	//send 1 bit
		else LCD_CLR(SPI_OUT);
		lcd_delay();				//NOP(); NOP();
		LCD_SET(SPI_CLK);			//data sent on the rising edge of clk
        lcd_delay();				//NOP(); NOP();                      //Ensure minimum delay of 500nS between SPI Clock high and SPI Clock Low
        mask = mask >> 1;           //Shift mask so that next bit is written and read from SPI lines
        //lcd_delay();				//NOP(); NOP();                      //Ensure minimum delay of 1000ns between bits
    } while (mask != 0);			//until all bits are sent
#else
	LCD_CLR(SPI_CLK); if (c& 0x80) LCD_SET(SPI_OUT); else LCD_CLR(SPI_OUT); lcd_delay(); LCD_SET(SPI_CLK); lcd_delay();
	LCD_CLR(SPI_CLK); if (c& 0x40) LCD_SET(SPI_OUT); else LCD_CLR(SPI_OUT); lcd_delay(); LCD_SET(SPI_CLK); lcd_delay();
	LCD_CLR(SPI_CLK); if (c& 0x20) LCD_SET(SPI_OUT); else LCD_CLR(SPI_OUT); lcd_delay(); LCD_SET(SPI_CLK); lcd_delay();
	LCD_CLR(SPI_CLK); if (c& 0x10) LCD_SET(SPI_OUT); else LCD_CLR(SPI_OUT); lcd_delay(); LCD_SET(SPI_CLK); lcd_delay();
	LCD_CLR(SPI_CLK); if (c& 0x08) LCD_SET(SPI_OUT); else LCD_CLR(SPI_OUT); lcd_delay(); LCD_SET(SPI_CLK); lcd_delay();
	LCD_CLR(SPI_CLK); if (c& 0x04) LCD_SET(SPI_OUT); else LCD_CLR(SPI_OUT); lcd_delay(); LCD_SET(SPI_CLK); lcd_delay();
	LCD_CLR(SPI_CLK); if (c& 0x02) LCD_SET(SPI_OUT); else LCD_CLR(SPI_OUT); lcd_delay(); LCD_SET(SPI_CLK); lcd_delay();
	LCD_CLR(SPI_CLK); if (c& 0x01) LCD_SET(SPI_OUT); else LCD_CLR(SPI_OUT); lcd_delay(); LCD_SET(SPI_CLK); lcd_delay();
#endif
	LCD_CLR(SPI_CLK);				//clock out the data bit

    //Ensure a minimum delay of 750ns between falling edge of SPI Clock signal
    //and rising edge of SPI Enable!
    //NOP();NOP();
}

/* write a byte to the LCD in 4/8 bit mode */
void lcd_write(unsigned char c, unsigned char rs) {
	unsigned char spi_mask;					//spi byte to be transmitted

	spi_mask = 0x00;						//reset spi mask
	if (c & 0x80) spi_mask |= LCD_D7;
	if (c & 0x40) spi_mask |= LCD_D6;
	if (c & 0x20) spi_mask |= LCD_D5;
	if (c & 0x10) spi_mask |= LCD_D4;

#if LCD_8BIT == 0							//in 4bit mode
	spi_send_byte(spi_mask);				//send the highest 4 bits;
	LCD_STROBE(rs);

	spi_mask = 0x00;						//reset spi_mask
	if (c & 0x08) spi_mask |= LCD_D7;
	if (c & 0x04) spi_mask |= LCD_D6;
	if (c & 0x02) spi_mask |= LCD_D5;
	if (c & 0x01) spi_mask |= LCD_D4;
#else									//in 8bit mode
	if (c & 0x08) spi_mask |= LCD_D3;
	if (c & 0x04) spi_mask |= LCD_D2;
	if (c & 0x02) spi_mask |= LCD_D1;
	if (c & 0x01) spi_mask |= LCD_D0;
#endif
	spi_send_byte(spi_mask);				//send the highest 4 bits;
	LCD_STROBE(rs);
}

/*
 * 	Clear and home the LCD
 */
void lcd_clear(void) {
	//LCD_CLR(LCD_RS);
	lcd_write(0x01, 0);	//clear the lcd
	delay_ms(2*2);		//2ms delay
}

/* write a string of chars to the LCD */
void lcd_puts(unsigned char * s) {
	//LCD_SET(LCD_RS);	// write characters
	while(*s) {
		lcd_write(*s++, 1);
	}
}


/* write one character to the LCD */
void lcd_putch(unsigned char c) {
	//LCD_SET(LCD_RS);	// write characters
	lcd_write( c, 1);
}

/*
 * Go to the specified position
 */
void lcd_goto(unsigned char pos) {
	//LCD_CLR(LCD_RS);
	lcd_write(0x80+pos, 0);
}

/* initialise the LCD - put into 4 bit mode */
void lcd_init(void) {
	//init_ctrl();			//set up the control pins
	IO_OUT(LCD_DIR, LCD_EN | LCD_SCK | LCD_SI);		//set up the control pins
	LCD_CLR(LCD_EN | LCD_RS | LCD_SCK);

	delay_ms(15*2);		// wait 15mSec after power applied,
	spi_send_byte(LCD_D4|LCD_D5);	//send 0x03
	LCD_STROBE(0);
	delay_ms(5*2);			//delay 5ms

	LCD_STROBE(0);
	delay_us(200);			//delay 200us

	LCD_STROBE(0);
	delay_us(200);			//delay 200us

#if LCD_8BIT == 0			//in 4-bit mode
	spi_send_byte(LCD_D5);		//send 0x02 -> 4 bit mode
	LCD_STROBE(0);
	lcd_write(LCD_FOUR_BIT & LCD_LINES_5X7, 0); // function control, 4bit, 2line, 5x8 dots
#else
	lcd_write(LCD_EIGHT_BIT & LCD_LINES_5X7, 0); // function control, 8bit, 2line, 5x8 dots
#endif

	lcd_write(LCD_DISPLAY_ON & LCD_CURSOR_OFF & LCD_BLINK_OFF, 0);	//display on, cursor off, blink off
	//lcd_clear();	// Clear screen
	lcd_write(LCD_SHIFT_DISPLAY_OFF & LCD_SHIFT_CURSOR_RIGHT, 0); // Set entry Mode, increment, don't shift.
}

void lcd_display(unsigned char LCD_Line, unsigned char * str) {
	lcd_goto(LCD_Line);
	lcd_puts(str);
}

//load a 8-byte data to cgram
void lcd_cgram(unsigned char cgaddr, const unsigned char * cgdata) {
	unsigned char i;
	lcd_write(LCD_CGRAM | (cgaddr * 8), 0);		//send the command
	for (i=0; i<8; i++) lcd_write(cgdata[i], 1);	//send the cgdata
}
