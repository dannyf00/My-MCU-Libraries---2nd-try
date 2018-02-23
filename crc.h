#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED

//crc8 calculation
//from ramtron datasheet for fm25v10
//http://www.ramtron.com/files/datasheets/FM25V10_ds.pdf

unsigned char CRC8( unsigned char* pData, int nBytes );

#endif // CRC_H_INCLUDED
