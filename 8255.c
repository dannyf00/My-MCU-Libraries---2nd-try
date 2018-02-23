#include <regx51.h>							//we use keil c51
#include "gpio.h"
#include "8255.h"							//we use 8255a

//hardware configuration
//#define PPI_CTRL_CS				(1<<6)		//cs line, active low
//end hardware configuration

#define ppi_deselect(cs) 		{IO_SET(PPI_CTRL_PORT, cs); IO_OUT(PPI_CTRL_DDR, cs);}	//deselct the ppi
#define ppi_select(cs) 			{ppi_deselect(cs); IO_CLR(PPI_CTRL_PORT, cs);}	//selct the ppi

//control words
//bit 3 -> _RD
//bit 2 -> _WR
//bit 1 -> A1
//bit 0 -> A0

/*
#define ppi_porta()				{IO_CLR(PPI_CTRL_PORT, PPI_CTRL_A0); IO_CLR(PPI_CTRL_PORT, PPI_CTRL_A1); IO_OUT(PPI_CTRL_DDR, PPI_CTRL_A0 | PPI_CTRL_A1);}	//a10=0b00
#define ppi_portb()				{IO_SET(PPI_CTRL_PORT, PPI_CTRL_A0); IO_CLR(PPI_CTRL_PORT, PPI_CTRL_A1); IO_OUT(PPI_CTRL_DDR, PPI_CTRL_A0 | PPI_CTRL_A1);}	//a10=0b01
#define ppi_portc()				{IO_CLR(PPI_CTRL_PORT, PPI_CTRL_A0); IO_SET(PPI_CTRL_PORT, PPI_CTRL_A1); IO_OUT(PPI_CTRL_DDR, PPI_CTRL_A0 | PPI_CTRL_A1);}	//a10=0b10
#define ppi_ctrl()				{IO_SET(PPI_CTRL_PORT, PPI_CTRL_A0); IO_SET(PPI_CTRL_PORT, PPI_CTRL_A1); IO_OUT(PPI_CTRL_DDR, PPI_CTRL_A0 | PPI_CTRL_A1);}	//a10=0b11

#define ppi_read()				{IO_CLR(PPI_CTRL_PORT, PPI_CTRL_RD); IO_SET(PPI_CTRL_PORT, PPI_CTRL_WR); IO_OUT(PPI_CTRL_DDR, PPI_CTRL_RD | PPI_CTRL_WR);}	//_rd=0, _wr=1
#define ppi_write()				{IO_SET(PPI_CTRL_PORT, PPI_CTRL_RD); IO_CLR(PPI_CTRL_PORT, PPI_CTRL_WR); IO_OUT(PPI_CTRL_DDR, PPI_CTRL_RD | PPI_CTRL_WR);}	//_rd=1, _wr=0
#define ppi_tris()				{IO_SET(PPI_CTRL_PORT, PPI_CTRL_RD); IO_SET(PPI_CTRL_PORT, PPI_CTRL_WR); IO_OUT(PPI_CTRL_DDR, PPI_CTRL_RD | PPI_CTRL_WR);}	//_rd=1, _wr=1

//write to ports
#define ppi_porta_write(val)	{ppi_porta(); PPI_DATA_PORT = (val); ppi_write();}
#define ppi_portb_write(val)	{ppi_portb(); PPI_DATA_PORT = (val); ppi_write();}
#define ppi_portc_write(val)	{ppi_portc(); PPI_DATA_PORT = (val); ppi_write();}
#define ppi_ctrl_write(val)		{ppi_ctrl(); PPI_DATA_PORT = (val); ppi_write();}
*/
//initialize ppi
void ppi_init(void) {
	IO_IN(PPI_DATA_DDR, PPI_DATA);			//all data pins as input
	
	IO_SET(PPI_CTRL_PORT, PPI_CTRL_RD | PPI_CTRL_WR | PPI_CTRL_A0 | PPI_CTRL_A1);	//all control line high
	IO_OUT(PPI_CTRL_DDR, PPI_CTRL_RD | PPI_CTRL_WR | PPI_CTRL_A0 | PPI_CTRL_A1);	//all control as output
}

