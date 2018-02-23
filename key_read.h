//header file to read rows of keys via hc164

//hardware configuration
//hc164 configuration
#define HC164_PORT			P3
#define HC164_DDR			P3
#define HC164_SCK			(1<<2)
#define HC164_SDO			(1<<3)

//row configuration
#define KEYROW_PORT			P0
#define KEYROW_PORT_IN		P0
#define KEYROW_DDR			P0

//end hardware configuration

//reset the hc164
void key_init(void);

//read a row
unsigned char key_read(unsigned char row);
