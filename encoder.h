//read encoders

#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED


//hardware configuration
#define ENC_PORT			PORTB				 	//inputs on portb
#define ENC_DDR				TRISB
#define ENC_A				(1<<9)				//rotary A on p.2, CN22
#define ENC_B				(1<<8)				//rotary B on p.5, CN21
#define ENC_CLICKS			4			//max clicks
//end of hardware configuration

//reset the encoder
void encoder_init(void);

//read the encoder
signed char encoder_read();

#endif // ENCODER_H_INCLUDED
