#ifndef CRC16_H_INCLUDED
#define CRC16_H_INCLUDED

//crc16 routines for crc16-ansi / 0xa001 / visual scope

#define CRC_POLY	0x1021	//0xa001	//0x8005	//0x1021	//0xa001

//visual scope's crc16 routine
//Array[] is an 8-byte data array to be sent to Visual Scope
//Rcvbuf is the encoded CRC16 data.
//length is the length
void CRC16_original(unsigned char *Array, unsigned short length,  unsigned short crc_init);

//my implementation
//msb first
unsigned short CRC16(unsigned char *dat, unsigned short length,  unsigned short crc_init);

#endif // CRC16_H_INCLUDED
