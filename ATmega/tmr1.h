//header file to use tmr1

#define TMR_CS210_NOCLK		0x00		//cs210=no clock selected
#define TMR_CS210_CLK		0x01		//clk/1
#define TMR_CS210_CLK_8		0x02		//clk/8
#define TMR_CS210_CLK_64	0x03		//clk/64
#define TMR_CS210_CLK_256	0x04		//clk/256
#define TMR_CS210_CLK_1024	0x05		//clk/1024
#define TMR_CS210_CLK_EXT_N	0x06		//external clock on Tn pin, negative transistion
#define TMR_CS210_CLK_EXT_P	0x07		//external clock on Tn pin, positive transistion

#define TMR_PS_1x			TMR_CS210_CLK
#define TMR_PS_8x			TMR_CS210_CLK_8
#define TMR_PS_64x			TMR_CS210_CLK_64
#define TMR_PS_256x			TMR_CS210_CLK_256
#define TMR_PS_1024x		TMR_CS210_CLK_1024
#define TMR_PS_MASK			0x07

//tmr period settings
#define TMR_ms				(F_CPU / 1000)				//1ms period - minimum period
#define TMR_1ms				(TMR_ms * 1)				//1ms
#define TMR_2ms				(TMR_ms * 2)				//2ms period
#define TMR_5ms				(TMR_ms * 5)				//5ms period
#define TMR_10ms			(TMR_ms * 10)				//10ms
#define TMR_20ms			(TMR_ms * 20)				//20ms period
#define TMR_50ms			(TMR_ms * 50)				//50ms period
#define TMR_100ms			(TMR_ms * 100)				//100ms
#define TMR_200ms			(TMR_ms * 200)				//200ms period
#define TMR_500ms			(TMR_ms * 500)				//500ms period
#define TMR_1000ms			(TMR_ms * 1000)				//1000ms
#define TMR_2000ms			(TMR_ms * 2000)				//2000ms period
#define TMR_5000ms			(TMR_ms * 5000)				//5000ms period
#define TMR_10000ms			(TMR_ms * 10000)			//10000ms

//reset the tmr
void tmr1_init(unsigned char prescaler, unsigned short period);

//set tmr1 isr ptr
void tmr1_act(void (*isr_ptr)(void));
