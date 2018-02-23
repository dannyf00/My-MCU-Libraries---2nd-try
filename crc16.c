#include "crc16.h"			//crc16 routines for 0xa001

//visual scope's crc16 routine
//Array[] is an 8-byte data array to be sent to Visual Scope
//Rcvbuf is the encoded CRC16 data.
//length is the length
//记住数据被visualscope视为是有符号的，比如dat[10]={0xff,0x7f,0,0,0,0,0,0,0,0}中，传的数据是32767
//即0xff 0x7f=b"0111 1111 1111 1111"
//-------------------------------------------------------------------------------------------
//The data from MCU to computer should be like this:
//-------------------------------------------------------------------------------------------
//Ch1_Data_L,Ch1_Data_H,
//Ch2_Data_L,Ch2_Data_H,
//Ch3_Data_L,Ch3_Data_H,
//Ch4_Data_L,Ch4_Data_H,
//CRC16_L,CRC16_H
/*
以下是CRC校验码生成程序，Array传入的是将要进行CRC校验的数组
数组长度为8 Bytes（本程序中dat[10]后面的两bytes是为CRC码预留的空间）
CRC校验码生成后就放在dat[10]的后两bytes
*/
void CRC16_original(unsigned char *Array, unsigned short length, unsigned short CRC) {
	unsigned short IX, IY;
	//unsigned short CRC=0xffff;
	//CRC = 0xffff; //set all to 1 (initial)
	if (length==0) return ~CRC;
	length--;
	for (IX = 0; IX <= length; IX++) {
		CRC = CRC ^ ((unsigned int) (Array[IX]));
		for (IY = 0; IY <= 7; IY++) {
			if ((CRC & 0x0001) /*!= 0*/) CRC = (CRC >> 1) ^ CRC_POLY;
			else CRC = (CRC >> 1);
		}
	}
	Array[8] = CRC;
	Array[9] = CRC >> 8;
}


//my implementation
//msb first
unsigned short CRC16(unsigned char *dat, unsigned short length, unsigned short CRC) {
	unsigned char IX, IY;
	//unsigned short CRC=0xffff;
	if (length==0) return ~CRC;
	//CRC = 0xffff; //set all to 1 (initial)
	for (IX = 0; IX < length; IX++) {
		CRC = CRC ^ (dat[IX]<<8);	//potentially put (unsigned char/short) in front of dat
		for (IY = 0; IY < 8; IY++) {
			if ((CRC & 0x8000)) CRC = (CRC << 1) ^ CRC_POLY;
			else CRC = (CRC << 1);
		}
	}
	return CRC;
}
