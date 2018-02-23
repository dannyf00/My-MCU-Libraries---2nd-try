#ifndef _LED7_H
#define _LED7_H
//header file to drive led7x8 displays statically

//hardware configuration
#define SR_PORT				PORTD
#define SR_DDR				DDRD
#define SR_SCK				(1<<0)			//serial clock
#define SR_SDA				(1<<1)			//serial data - rising edge
#define SR_STROBE			(1<<2)			//strobe - optional

#define LED7_CA								//define common anode. comment out for common cathode
//end hardware configuration

extern unsigned char const led7_font[];		//led7 font
#define LED7_DOT			16				//'.' - dot
#define LED7_SPACE			17				//' ' - space

//initialize the led7 display
void led7_init(void);

//display a char
void led7_write(unsigned char dat);

//if sr_strobe is defined
#if defined(SR_STROBE)
#define led7_strobe()		do {IO_CLR(SR_PORT, SR_STROBE); IO_SET(SR_PORT, SR_STROBE); IO_CLR(SR_PORT, SR_STROBE);} while (0)
#else
#define led7_strobe()
#endif

#endif
