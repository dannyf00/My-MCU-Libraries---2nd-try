#ifndef CD4051_H_INCLUDED
#define CD4051_H_INCLUDED

/*	header file for cd4051
 */

//hardware configuration
#define CD4051_PORT			PORTD
#define CD4051_DDR			DDRD
#define CD4051_S0			(1<<0)
#define CD4051_S1			(1<<1)
#define CD4051_S2			(1<<2)
//#define CD4051_INH			(1<<3)			//uncomment if not used
//end hardware configuration

//channel selector
#define CD4051_A0			0x00
#define CD4051_A1			0x01
#define CD4051_A2			0x02
#define CD4051_A3			0x03
#define CD4051_A4			0x04
#define CD4051_A5			0x05
#define CD4051_A6			0x06
#define CD4051_A7			0x07

//initialize cd4051
void cd4051_init(void);

//select a channel
void cd4051_select(unsigned char ch);

#endif // CD4051_H_INCLUDED
