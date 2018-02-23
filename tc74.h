//for tc74
#define TC74_ADDR_A0				0x90			//TC74 at A0
#define TC74_ADDR_A1				0x92			//TC74 at A1
#define TC74_ADDR_A2				0x94			//TC74 at A2
#define TC74_ADDR_A3				0x96			//TC74 at A3
#define TC74_ADDR_A4				0x98			//TC74 at A4
#define TC74_ADDR_A5				0x9a			//TC74 at A5
#define TC74_ADDR_A6				0x9c			//TC74 at A6
#define TC74_ADDR_A7				0x9e			//TC74 at A7
#define TC74_CMD_READ				0x01			//read bit
#define TC74_CMD_WRITE				0x00			//write bit
#define TC74_CMD_RTR				0x00			//read temperature
#define TC74_CMD_RWCR				0x01			//read / write the configuration register
#define TC74_MASK_STANDBY			0x80			//mask for shutdown
#define TC74_MASK_READY				0x40			//data ready

void tc74_select(unsigned char addr);		//select tc74

void tc74_write(unsigned char cmd, unsigned char data_t);

signed char tc74_read(unsigned char cmd);

#define TC74_GET_TEMP()				tc74_read(TC74_CMD_RTR)	//read tc74 temperature register
#define tc74_get_temp()				TC74_GET_TEMP()

#define TC74_GET_CONFIG()			tc74_read(TC74_CMD_RWCR)	//read tc74 configuration register
#define tc74_get_config()			TC74_GET_CONFIG()

void tc74_shutdown(void);
