#ifndef __25LC_H
#define __25LC_H

//#include "spi_sw.h"
//hearder file for _25lc chips

//hardware configuration
//_wp low and _hold high
//cs select chips
#define _25LC_16BIT		1			//if the chip requires 16-bit address
#define _25LC_CS0		(1<<4)		//cs0
#define _25LC_CS1		(1<<5)		//cs1

//#define _25LC_CS_ALL	(_25LC_CS0 | _25LC_CS1)	//all cs pins
//end hardware configuration

//commands
#define _25LC_CMD_READ	0x03		//=0b00000011, read command, OR
#define _25LC_CMD_WRITE	0x02		//=0b00000010, write command, OR
#define _25LC_CMD_WREN	0x06		//=0b00001100, write-enable latch
#define _25LC_CMD_WRDI	0x04		//=0b00000100, write-disable
#define _25LC_CMD_RDSR	0x05		//=0b00000101, write status register
#define _25LC_CMD_WRSR	0x01		//=0b00000001, write status register
#define _25LC_CMD_PE	0x42		//=0b01000010, page erase
#define _25LC_CMD_SE	0xd8		//=0b11011000, sector erase
#define _25LC_CMD_CE	0xc7		//=0b11000111, chip erase
#define _25LC_CMD_RDID	0xab		//=0b10101101, wake-up from deep power down and read id
#define _25LC_CMD_DPD	0xb9		//=0b10111001, enter deep power down

//status register bits
#define _25LC_WPEN_BP1	(1<<3)		//bp1 bit in wpen
#define _25LC_WPEN_BP0	(1<<2)		//bp0 bit in wpen
#define _25LC_WPEN_WEL	(1<<1)		//write-enable-latch bit in wpen. 1=write-enabled, 0=write-diabled
#define _25LC_WPEN_WIP	(1<<0)		//write-in-progress bit in wpen. 1=a write in progress. 0= write done.

//return status register bit status
#define _25LC_WIP()		(_25lc_read_status() & _25LC_WPEN_WIP)	//is 25lc busy? 1 = busy, 0 = no
#define _25LC_WEL()		(_25lc_read_status() & _25LC_WPEN_WEL)	//is 25lc write-enabled? 1 = write-enabled, and 0=write disabled
#define _25LC_BP0()		(_25lc_read_status() & _25LC_WPEN_BP0)	//status register's bp0 bit
#define _25LC_BP1()		(_25lc_read_status() & _25LC_WPEN_BP1)	//status register's bp1 bit

//send the write-enable latch command
#define _25LC_SEND_WREN()		{_25lc_select(_25LC_CS); spi_write(_25LC_CMD_WREN); _25lc_deselect(_25LC_CS);}	//spi_delay(1)

#define _25LC_MSB(var)	((var) >> 8)	//msb of var
#define _25LC_LSB(var)	((var) & 0x00ff)		//lsb of var

//cs pin casted to "unsigned int" on a 32-bit port.
//may need to change it on a 8-bit port

//#define _25lc_select(cs)			IO_CLR(SPI_PORT, cs)	//select cs

//#define _25lc_deselect(cs)			IO_SET(SPI_PORT, cs)	//deselect the chip

//initialize _25lc
void _25lc_init(void);

//select cs
void _25lc_select(unsigned char cs);

//deselect cs
void _25lc_deselect(unsigned char cs);

//write a byte to 25lc
void _25lc_write(unsigned short address, unsigned char data_t);

//read a byte from 25lc
unsigned char _25lc_read(unsigned short address);

//read 25lc status
unsigned char _25lc_read_status(void);

//write 25lc status
void _25lc_write_status(unsigned char status);

//erase a page that address is within
void _25lc_page_erase(unsigned short address);

//eraese a sector that address is within
void _25lc_sector_erase(unsigned short address);

//erase the chip
void _25lc_chip_erase(void);

//enter deep power down mode
void _25lc_power_down(void);

//release from deep power down mode, and read chip id
unsigned char _25lc_read_ID(void);

#endif
