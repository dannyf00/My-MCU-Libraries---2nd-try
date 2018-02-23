//emulate the pulse output of an encoder
#ifndef ENCOUT_H_INCLUDED
#define ENCOUT_H_INCLUDED

//hardware configuration
#define OUT_PORT		PORTB
#define OUT_DDR			TRISB
#define OUT_A			(1<<0)
#define OUT_B			(1<<1)

//end hardware configuration

#define ENC_CW			0
#define ENC_CCW			1

//reset encoder emulator
void encout_init(void);

//generate a value for the encoder
unsigned char encout_val(signed char step);

//write the value out
void encout_write(unsigned char enc_val);

#endif // ENCOUT_H_INCLUDED
