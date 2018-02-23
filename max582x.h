//header file for max582x

//hardware configuration
#define MAX582XL_ADDR			0x70		//max582xL address
#define MAX582XM_ADDR			0xb0		//max582xM version
#define MAX5822								//define max5822
//#define MAX5821								//define max5821
//#define MAX5820								//define max5820
//end hardware configuration

//max582x commands
#define MAX582X_LOADA_UPDATEALL		0x00	//load a and update all dac output
#define MAX582X_LOADB_UPDATEALL		0x10	//load b and update all dac output
#define MAX582X_LOADA_UPDATENONE	0x40	//load a and update no dac output
#define MAX582X_LOADB_UPDATENONE	0x50	//load b and update no dac output

//not sure
#define MAX582X_LOADA_UPDATEALL1	0x80	//load a and update all dac output
#define MAX582X_LOADA_UPDATEALL2	0x90	//load a and update all dac output

#define MAX582X_LOADALL_UPDATEALL	0xc0	//load all and update all dac output
#define MAX582X_LOADALL_UPDATENONE	0xd0	//load all and update no dac output
#define MAX582X_UPDATEALL			0xe0	//update all dac output - d11-d8 ignored
#define MAX582X_EXT					0xf0	//extended command
#define MAX582X_READ_DACA			0xf1	//read dac a
#define MAX582X_READ_DACB			0xf2	//read dac b

#define MAX582X_EXT_DACB			0x08	//cmd applies to dac b
#define MAX582X_EXT_DACA			0x04	//cmd applies to dac a
#define MAX582X_EXT_POWERUP			0x00	//power up - normal operation
#define MAX582X_EXT_SHUTDOWN0		0x01	//shutdown mode 0 - output floating
#define MAX582X_EXT_SHUTDOWN1		0x02	//shutdown mode 1 - output to ground via 1k resistor
#define MAX582X_EXT_SHUTDOWN2		0x03	//shutdown mode 2 - output to ground via 100k resistor

#ifdef MAX5822
  #define MAX582X_SHIFT				4
#endif

#ifdef MAX5821
  #define MAX582X_SHIFT				6
#endif

#ifdef MAX5820
  #define MAX582X_SHIFT				8
#endif


//select l version address
void max582xl_select(unsigned char add);

//select m version address
void max582xm_select(unsigned char add);

//send a command / data to max582xl
//data in word_t right aligned (lowest 8/10/12 bits effective)
void max582x_write(unsigned char cmd, unsigned short word_t);

//read from max582x
unsigned short max582x_read(unsigned char cmd);

//power mode
void max582x_power(unsigned char mode);
