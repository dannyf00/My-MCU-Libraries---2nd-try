//header file for mcp3001

//hardware configuration
//end hardware configuration

//select mcp3001
#define mcp3001_select(cs)		{spi_select(cs);}

//deselect mcp3001
#define mcp3001_deselect(cs)	{spi_deselect(cs);}

void mcp3001_init(void);

unsigned short mcp3001_read(void);

