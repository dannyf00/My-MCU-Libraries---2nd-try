#include <htc.h>						//we use picc
#include "lcd_hw.h"						//we use onboard hardware lcd

//global variable
	const unsigned char _7seg_font[]={
		0x3f,									//'0'
		0x06,									//'1'
		0x5b,									//'2'
		0x4f,									//'3'
		0x66,									//'4'
		0x6d,									//'5'
		0x7d,									//'6'
		0x07,									//'7'
		0x7f,									//'8'
		0x6f,									//'9'
		0x77,									//'A'
		0x7c,									//'b'
		0x39,									//'C'
		0x5e,									//'d'
		0x79,									//'E'
		0x71,									//'F'
		0x40};									//' '
	
	
//initialize the lcd
void lcd_init(void) {
	//set up lcdcon
	LCDEN = 0;							//turn off the lcd
	SLPEN = 1;							//no lcd drive in sleep mode
	VLCDEN = 1;							//enable lcd bias voltage
	CS1=0, CS0=0;						//0b00 -> Fosc / 8192. 0b01 = Timer1/32, 0b1x = LFINTOSC(31khz)/32
	LMUX1=(LCD_COM & LCD_COM2) >> 1;
	LMUX0=(LCD_COM & LCD_COM1);			//0b00 -> static(COM0); 0b01 -> 1/2 (COM0..1); 0b10 -> 1/3 (COM0..2); 0b11 -> 1/4 (COM0..3)
	
	//set up lcdps
	WFT = 0;							//1=wave form change on the boundary, 0=in between
	switch (LCD_COM) {
		case LCD_COM0:		BIASMD = 0;	break;	//has to be set to 0
		case LCD_COM1:		BIASMD = 1; break;	//1=1/2 bias. 0=1/3 bias
		case LCD_COM2:		BIASMD = 0;	break;	//1=1/3 bias. 0=1/2 bias
		case LCD_COM3:		BIASMD = 0;	break;	//has to be set to 0
	}
	//LCDA=1, WA=1;						//set the status bits
	
	//set up the prescaler
	LP3=(LCD_PS & 0x08) >> 3;
	LP2=(LCD_PS & 0x04) >> 2;
	LP1=(LCD_PS & 0x02) >> 1;
	LP0=(LCD_PS & 0x01) >> 0;				//lcd prescaler. 1:1(0b0000) -> 16:1 (0b1111)
	
	//enable the segments - need customization
	LCDSE0 = 0xff;						//enable lcd0..7
	LCDSE1 = 0xff;						//enable lcd8..15
	LCDSE2 = 0xff;						//enable lcd16..23
	//LCDSE3 = 0xff;						//enable lcd24..31
	//LCDSE4 = 0xff;						//enable lcd32..39
	//LCDSE5 = 0xff;						//enable lcd40..47
	
	//enable the output - set by lcdsex automatically
	//TRISA = 0x00;						//porta as output
	//TRISB = 0x00;						//portb as output
	//TRISC = 0x00;						//portc as output
	//TRISD = 0x00;						//portd as output
	//TRISE = 0x00;						//porte as output
	
	LCDEN = 1;							//enable the lcd
}

//display data on lcd
void lcd_display(unsigned char * vRAM) {
	unsigned char index;

	//set up the data - will need triming
	//vRAM[] is numerical
	LCDDATA0 = _7seg_font[vRAM[0]];
	LCDDATA1 = _7seg_font[vRAM[1]];
	LCDDATA2 = _7seg_font[vRAM[2]];
	LCDDATA3 = _7seg_font[vRAM[3]];
	LCDDATA4 = _7seg_font[vRAM[4]];
	LCDDATA5 = _7seg_font[vRAM[5]];
	LCDDATA6 = _7seg_font[vRAM[6]];
	LCDDATA7 = _7seg_font[vRAM[7]];
	LCDDATA8 = _7seg_font[vRAM[8]];
	LCDDATA9 = _7seg_font[vRAM[9]];
	LCDDATA10 = _7seg_font[vRAM[10]];
	LCDDATA11 = _7seg_font[vRAM[11]];
}

//display a ul
void lcd_display_ul(unsigned long ul) {
	unsigned char index=0;
	
	LCDDATA0 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA1 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA2 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA3 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA4 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA5 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA6 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA7 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA8 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA9 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA10 = _7seg_font[ul % 10]; ul = ul / 10;
	LCDDATA11 = _7seg_font[ul % 10]; ul = ul / 10;
}	