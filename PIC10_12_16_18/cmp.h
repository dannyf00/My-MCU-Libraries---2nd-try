#ifndef _CMP_H
#define _CMP_H

#if defined(_16F690) || defined(_16F684)
//header file for comparator 1 on 16f690
//hardware configuration
//configure CMP1
#define CMP1OUT_PORT		PORTA
#define CMP1OUT_DDR			TRISA
#define CMP1OUT				(1<<2)			//CMP1out on porta.2

//configure CMP1IN+
#define CMP1INP_DDR			TRISA
#define CMP1INP				(1<<0)			//CMP1IN+ on porta.0/an0
#define CMP1INP_ANS			ANS0

//configure CMP1IN-
#define CMP1INN_DDR			TRISA
#define CMP1INN				(1<<1)			//CMP12in0 on porta.1
#define CMP1INN_ANS			ANS1			//porta.1=ans1

//configure CMP2
#define CMP2OUT_PORT		PORTC
#define CMP2OUT_DDR			TRISC
#define CMP2OUT				(1<<4)			//CMP1out on portc.4

//configure CMP2IN+
#define CMP2INP_DDR			TRISC
#define CMP2INP				(1<<0)			//CMP1IN+ on portc.0/an4
#define CMP2INP_ANS			ANS4

//configure CMP2IN-
#define CMP2INN_DDR			TRISC
#define CMP2INN				(1<<1)			//CMP12in0 on portc.1
#define CMP2INN_ANS			ANS5			//portc.1=ans5
//end hardware configuration

//CMCON0 bits
//CMP1OUT bit
//#define CMP1_OE				0x40			//route CMP1's output to CMP1OUT
//#define CMP1_OD				0x00			//CMP1OUT internal

//CMP1POL/CMP1INV bit
#define CMP1_POLP			0x00			//output positive logic
#define CMP1_POLN			0x10			//output negative logic

//CMP2OUT bit
//#define CMP2_OE				0x80			//route CMP1's output to CMP1OUT
//#define CMP2_OD				0x00			//CMP1OUT internal

//CMP2POL/CMP2INV bit
#define CMP2_POLP			0x00			//output positive logic
#define CMP2_POLN			0x20			//output negative logic

//CIS bit
#define CMP_INVERT			0x08			//CxIN+ to CIN-, CxIN- to CIN+
#define CMP_NORMAL			0x00			//normal

//CM2..0 bits
#define CMP_MODE0			0x00			//comparators off
#define CMP_MODE1			0x01			//mode 1
#define CMP_MODE2			0x02			//mode 2
#define CMP_MODE3			0x03			//mode 3
#define CMP_MODE4			0x04			//mode 4
#define CMP_MODE5			0x05			//mode 5
#define CMP_MODE6			0x06			//mode 6
#define CMP_MODE7			0x07			//mode 7

#else
	#warning CVR module not defined on this chip!
#endif

//configure cmcon1
//cmcon1 not configured

//initialize the comparator
void cmp_init(unsigned char cmcon);

#endif

