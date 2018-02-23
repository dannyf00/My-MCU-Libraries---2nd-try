//#include <regx51.h>							//we use keil c51
#include <htc.h>								//we use picc
#include "gpio.h"
//#include "tmr0.h"								//we use tmr0
//#include "rtc1.h"
#include "vi402.h"								//we use vi402, segment drive

//global variables
VSEG_TYPE vSEG;					//display buffer  - for segment information

unsigned char vRAM[DIG_NUMBER];	//display buffer

void lcd_init(void) {
	IO_CLR(COM_PORT, COM);		//clear com
	IO_OUT(COM_DDR, COM);		//com as output

#ifdef DIG0_PORT
	IO_CLR(DIG0_PORT, DIG0);	//clear dig0
	IO_OUT(DIG0_DDR, DIG0);		//dig0 as output
#endif

#ifdef DIG1_PORT
	IO_CLR(DIG1_PORT, DIG1);	//clear dig1
	IO_OUT(DIG1_DDR, DIG1);		//dig1 as output
#endif

#ifdef DIG2_PORT
	IO_CLR(DIG2_PORT, DIG2);	//clear dig2
	IO_OUT(DIG2_DDR, DIG2);		//dig2 as output
#endif

#ifdef DIG3_PORT
	IO_CLR(DIG3_PORT, DIG3);	//clear dig3
	IO_OUT(DIG3_DDR, DIG3);		//dig3 as output
#endif
}

//display vSEG
void lcd_display(void) {
	static unsigned char sCOM=0xff;

	//output segment data
#ifdef DIG0_PORT
	DIG0_PORT = vSEG.dig[0] ^ sCOM;
#endif

#ifdef DIG1_PORT
	DIG1_PORT = vSEG.dig[1] ^ sCOM;
#endif

#ifdef DIG2_PORT
	DIG2_PORT = vSEG.dig[2] ^ sCOM;
#endif

#ifdef DIG3_PORT
	DIG3_PORT = vSEG.dig[3] ^ sCOM;
#endif

	//send com
	if (sCOM) IO_SET(COM_PORT, COM);		//flip com
	else IO_CLR(COM_PORT, COM);	//clear com
	sCOM ^= 0xff;				//flip com
	//IO_SET(COM_PORT, COM);				//for sim only

}

//translates vram to vseg
void vRAM2SEG(void) {
	const unsigned char _7seg_font[]= {
		0x3f,						//'0'
		0x06,						//'1'
		0x5b,						//'2'
		0x4f,						//'3'
		0x66,						//'4'
		0x6d,						//'5'
		0x7d,						//'6'
		0x07,						//'7'
		0x7f,						//'8'
		0x6f,						//'9'
		0x77,						//'A'
		0x7c,						//'b'
		0x39,						//'C'
		0x5e,						//'d'
		0x79,						//'E'
		0x71,						//'F'
		0x40,						//'-'
		0x00						//' '
	};

	//vSEG.ul +=0x11;
	vSEG.dig[0]=_7seg_font[(vRAM[0]>17)?17:vRAM[0]];
	vSEG.dig[1]=_7seg_font[(vRAM[1]>17)?17:vRAM[1]];
	vSEG.dig[2]=_7seg_font[(vRAM[2]>17)?17:vRAM[2]];
	vSEG.dig[3]=_7seg_font[(vRAM[3]>17)?17:vRAM[3]];

	//vRAM[3]=(vRAM[3]==17)?vRAM[3]=0:(vRAM[3]+1);
	//lcd_display();
}

