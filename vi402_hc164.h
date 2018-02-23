//hardware configuration
#define VI402_PORT			P2
#define VI402_DDR			P2
#define VI402_COM			(1<<6)
#define VI402_COL			(1<<7)
//end hardware configuration

void vi402_init(void);

void vi402_display(unsigned char * str);
