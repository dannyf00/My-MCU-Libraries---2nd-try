//header file to use tmr1

//prescaler settings
#define TMR_CS210_NOCLK		0x00		//cs210=no clock selected
#define TMR_CS210_CLK		0x01		//clk/1
#define TMR_CS210_CLK_8		0x02		//clk/8
#define TMR_CS210_CLK_64	0x03		//clk/64
#define TMR_CS210_CLK_256	0x04		//clk/256
#define TMR_CS210_CLK_1024	0x05		//clk/1024
#define TMR_CS210_CLK_EXT_N	0x06		//external clock on Tn pin, negative transistion
#define TMR_CS210_CLK_EXT_P	0x07		//external clock on Tn pin, positive transistion

#define TMR_PS_1x		TMR_CS210_CLK
#define TMR_PS_8x		TMR_CS210_CLK_8
#define TMR_PS_64x		TMR_CS210_CLK_64
#define TMR_PS_256x		TMR_CS210_CLK_256
#define TMR_PS_1024x		TMR_CS210_CLK_1024
#define TMR_PS_MASK		0x07

//rtc period settings
#define RTC_10000ms			(RTC_ms * 10000)		//10s period
#define RTC_5000ms			(RTC_ms * 5000)		//5s period
#define RTC_2500ms			(RTC_ms * 2500)		//2.5s period
#define RTC_2000ms			(RTC_ms * 2000)		//2s period
#define RTC_1000ms			(RTC_ms * 1000)		//1s period
#define RTC_500ms			(RTC_ms * 500)		//500ms period
#define RTC_250ms			(RTC_ms * 250)		//250ms period
#define RTC_200ms			(RTC_ms * 200)		//200ms period
#define RTC_100ms			(RTC_ms * 100)		//100ms period
#define RTC_50ms			(RTC_ms * 50)			//50ms period
#define RTC_25ms			(RTC_ms * 25)			//25ms period
#define RTC_20ms			(RTC_ms * 20)			//20ms period
#define RTC_10ms			(RTC_ms * 10)			//10ms period
#define RTC_5ms				(RTC_ms * 5)			//5ms period
#define RTC_2ms				(RTC_ms * 2)			//2ms period
#define RTC_1ms				(RTC_ms * 1)			//1ms period - minimum period
#define RTC_ms				(F_CPU / 1000)		//ms definition

typedef struct {
	unsigned char half_sec;
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned char day;
} RTC_TIME;

extern volatile RTC_TIME _rtc1;


//reset the tmr
void rtc1_init(unsigned long period);

//set tmr1 isr ptr
void rtc1_act(void (*isr_ptr)(void));

//update rtc1
void rtc1_update(void);
