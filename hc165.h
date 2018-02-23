/* hc165 header file
 */

//hardware configuration
#define HC165_PORT			PORTE
#define HC165_PORT_IN		PINE
#define HC165_DDR			DDRE
#define HC165_SCK			(1<<0)
#define HC165_MISO			(1<<1)
#define HC165_PL			(1<<3)		//parallel load, active low
//end hardware configuration

//load serial data
#define hc165_load()		do {IO_SET(HC165_PORT, HC165_PL);	IO_CLR(HC165_PORT, HC165_PL);	IO_SET(HC165_PORT, HC165_PL);} while (0)

//initialize hc165
void hc165_init(void);

//read hc165
unsigned char hc165_read(void);
