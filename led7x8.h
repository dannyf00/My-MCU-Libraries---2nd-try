//header file to drive led7x8 displays

//hardware configuration
#define LED7_DATA_PORT		P2
#define LED7_DATA_DDR		P2
#define LED7_DATA			0xff

#define HC164_PORT			P3
#define HC164_DDR			P3
#define HC164_SCK			(1<<0)
#define HC164_SDA			(1<<1)
//end hardware configuration

#define LED7_DIG			7				//max number of dig
#define LED7_COMMON_ANODE					//define common anode
#define LED7_CA				LED7_COMMON_ANODE

#if defined(LED7_CA)						//common anode
#define LED_ON(pins)		LED7_DATA_PORT =~(pins)
#define LED_OFF(pins)		LED7_DATA_PORT = (pins)
#else										//common cathode
#define LED_ON(pins)		LED7_DATA_PORT = (pins)
#define LED_OFF(pins)		LED7_DATA_PORT =~(pins)
#endif


//initialize the led7 display
void led7_init(void);

//display a char
void led7_write(unsigned char dat);
