//header file for rotary encoders
//switches active low

//hardware configuration
#define ENC1_PORT			PORTB				 	//inputs on portb
#define ENC1_DDR			TRISB
#define ENC1_A				(1<<10)				//rotary A on p.2
#define ENC1_B				(1<<11)				//rotary B on p.5
//end of hardware configuration

//define port type:
//"unsigned int" (a 32-bit type) for 32-bit ports
//"unsigned char" for 8-bit ports
//change PORT_TYPE if you are compiling for a differrent platform

//define PORT_TYPE			unsigned long		//works for 32-bit ports
//#define PORT_TYPE			unsigned char		//works for 8-bit ports

//reset the encoder
void encoder1_init(void);

//determine increment / decrement of the encoder
unsigned char encoder1_read(void);
