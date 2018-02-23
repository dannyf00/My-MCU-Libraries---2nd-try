//header file for rotary encoders
//switches active low

//hardware configuration
#define ENC_PORT			PORTB				 	//inputs on portb
#define ENC_DDR				TRISB
#define ENC_A				(1<<12)				//rotary A on p.2
#define ENC_B				(1<<13)				//rotary B on p.5
//end of hardware configuration

//define port type:
//"unsigned int" (a 32-bit type) for 32-bit ports
//"unsigned char" for 8-bit ports
//change PORT_TYPE if you are compiling for a differrent platform

//define PORT_TYPE			unsigned long		//works for 32-bit ports
//#define PORT_TYPE			unsigned char		//works for 8-bit ports

//reset the encoder
void encoder2_init(void);

//determine increment / decrement of the encoder
unsigned char encoder2_read(void);
