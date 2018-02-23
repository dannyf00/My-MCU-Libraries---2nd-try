#include <regx51.h>
#include "gpio.h"
#include "hc164.h"
#include "vi402.h"

unsigned char sCOM=0x00;

void vi402_init(void) {
    IO_CLR(VI402_PORT, VI402_COM | VI402_COL);	//clear com / col
    IO_OUT(VI402_DDR, VI402_COM | VI402_COL);	//com / col as output
}

void vi402_putch(unsigned char ch) {
    const unsigned char seg_table[]= {			//segment info for common anode led
        0xc0, 										//'0'
        0xf9, 										//'1'
        0xa4, 										//'2'
        0xb0, 										//'3'
        0x99, 										//'4'
        0x92, 										//'5'
        0x82, 										//'6'
        0xf8, 										//'7'
        0x80, 										//'8'
        0x98
    };										//'9'

    hc164_write((~seg_table[ch-'0']) ^ sCOM);		//send the char
}

void vi402_display(unsigned char *str) {
    /*
    	 if (sCOM) {
    	 	sCOM = 0x00;							//invert sCOM
    		IO_CLR(VI402_PORT, VI402_COM);			//invert com
    	} else {
    		sCOM = 0xff;							//invert sCOM
    		IO_SET(VI402_PORT, VI402_COM);			//invert com
    	}
    */
    sCOM ^= 0xff;								//invert sCOM
    if (sCOM) IO_SET(VI402_PORT, VI402_COM);				//flip com
    else IO_CLR(VI402_PORT, VI402_COM);

    vi402_putch(str[0]);					//send char 0
    vi402_putch(str[1]);					//send char 1
    vi402_putch(str[2]);					//send char 2
    vi402_putch(str[3]);					//send char 3

}

