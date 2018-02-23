#ifndef __MISC_H
#define __MISC_H

#define ULTOA_SEPARATOR			','			//000 separators

#define ultoa				ultoa_dec		//ultoa defaults to ultoa_dec
#define  ltoa				 ltoa_dec		//ltoa defaults to ltoa_dec

//turn a ul to decimal string, with no leading zeros
unsigned char ultoa_dec(unsigned char * str, unsigned long ul, unsigned char length);

//turn a ul to decimal string, with leading zeros
unsigned char ultoa_0(unsigned char * str, unsigned long ul, unsigned char length);

//fast routines to turn a ul to decimal string, with leading zeros
unsigned char ultoa_fast(unsigned char * str, unsigned long ul, unsigned char length);

//turn a ul to binary string, with leading zeros
unsigned char ultoa_bin(unsigned char * str, unsigned long ul, unsigned char length);

//turn a ul to hex string, with leading zeros
unsigned char ultoa_hex(unsigned char * str, unsigned long ul, unsigned char length);

//convert ul to string, with 000 separators
unsigned char ultoa_s(unsigned char *str, unsigned long ul, unsigned char length);

//turn a l to decimal string, with no leading zeros
unsigned char ltoa_dec(unsigned char * str, signed long ul, unsigned char length);

//turn a ul to decimal string, with leading zeros
unsigned char ltoa_0(unsigned char * str, signed long ul, unsigned char length);

//turn a ul to binary string, with leading zeros
unsigned char ltoa_bin(unsigned char * str, signed long ul, unsigned char length);

//turn a ul to hex string, with leading zeros
unsigned char ltoa_hex(unsigned char * str, signed long ul, unsigned char length);

//convert ul to string, with 000 separators
unsigned char ltoa_s(unsigned char *str, signed long ul, unsigned char length);

//convert a double to string, with different decimal points
unsigned char ftoc1(unsigned char * str, double f, unsigned char length);
unsigned char ftoc2(unsigned char * str, double f, unsigned char length);
unsigned char ftoc3(unsigned char * str, double f, unsigned char length);
unsigned char ftoc4(unsigned char * str, double f, unsigned char length);

//convert ul (8-digit) to ascii
void ul8toa(char * str, uint32_t num);
//convert ul (8-digit) to ascii, fast
void ul8toa_fast(char *str, uint32_t num);
#endif /*MISC_H_*/
