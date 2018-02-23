#ifndef _MCP3204_H
#define _MCP3204_H

#include "gpio.h"
#include "delay.h"
#include "spi_sw.h"

//hardware configuration
#define MCP3204_PORT		SPI_PORT
#define MCP3204_DDR			SPI_DDR
#define MCP3204_CS			(1<<4)		//cs on pb.4
//end hardware configuration

//mcp3204 configuration
#define MCP3204_CH0			0x08		//single-ended ch0, 0b1000
#define MCP3204_CH1			0x09		//single-ended ch1, 0b1001
#define MCP3204_CH2			0x0a		//single-ended ch2, 0b1010
#define MCP3204_CH3			0x0b		//single-ended ch3, 0b1011
#define MCP3204_CH0_CH1		0x00		//differential, ch0 - ch1, 0b0000
#define MCP3204_CH1_CH0		0x01		//differential, ch1 - ch0, 0b0001
#define MCP3204_CH2_CH3		0x02		//differential, ch2 - ch3, 0b0010
#define MCP3204_CH3_CH2		0x03		//differential, ch3 - ch2, 0b0011
#define MCP3204_START_BIT	0x10		//start bit, 0b1

//mcp3208 configuration, in addition to above
#define MCP3208_CH0		MCP3204_CH0
#define MCP3208_CH1		MCP3204_CH1
#define MCP3208_CH2		MCP3204_CH2
#define MCP3208_CH3		MCP3204_CH3
#define MCP3208_CH4		0x0c
#define MCP3208_CH5		0x0d
#define MCP3208_CH6		0x0e
#define MCP3208_CH7		0x0f
#define MCP3208_CH0_CH1		MCP3204_CH0_CH1		//differential, ch0 - ch1, 0b0000
#define MCP3208_CH1_CH0		MCP3204_CH1_CH0		//differential, ch1 - ch0, 0b0001
#define MCP3208_CH2_CH3		MCP3204_CH2_CH3		//differential, ch2 - ch3, 0b0010
#define MCP3208_CH3_CH2		MCP3204_CH3_CH2		//differential, ch3 - ch2, 0b0011
#define MCP3208_CH4_CH5		0x4			//differential, ch4 - ch5, 0b0011
#define MCP3208_CH5_CH4		0x5			//differential, ch4 - ch5, 0b0011
#define MCP3208_CH6_CH7		0x6			//differential, ch4 - ch5, 0b0011
#define MCP3208_CH7_CH6		0x7			//differential, ch4 - ch5, 0b0011

unsigned short mcp3204_read(unsigned char config_byte);

#endif
