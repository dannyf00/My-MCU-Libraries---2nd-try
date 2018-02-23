//hardware configuration
#define TC77_PORT			P2
#define TC77_PORT_IN		P2
#define TC77_DDR			P2
#define TC77_SCK			(1<<0)
#define TC77_SIO			(1<<2)
#define TC77_DLY			400					//first conversion time, in ms
//end hardware configuration

void tc77_init(void);							//reset tc77

#define TC77_CMD_CONVERT	0x00				//continuous conversion mode
#define TC77_CMD_SHUTDOWN	0xff				//shut down mode

#define tc77_select(cs)		{IO_CLR(TC77_PORT, cs); IO_OUT(TC77_DDR, cs);}	//select cs
#define tc77_deselect(cs)	{IO_SET(TC77_PORT, cs); IO_IN(TC77_DDR, cs);}	//deselect cs

//read from tc77
//assume that device has been selected prior
signed short tc77_read(void);					//read a word from tc77

//write to tc77
//assume that device has been selected prior
signed short tc77_write(signed short word_t);		//write a word to tc77
