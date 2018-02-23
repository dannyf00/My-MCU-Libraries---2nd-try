//hardware configuration
#define UART_PORT		PORTD
#define UART_DDR		DDRD
#define UART_TX			(1<<0)
#define UART_RX			(1<<1)
//end hardware configuration

#define MSB(word_t)		((word_t) >> 8)			//most significant byte
#define LSB(word_t)		((word_t) & 0x00ff)		//least significant byte

#define F_UART				(F_CPU)	//8Mhz		//crystal frequency
#define UART_BR_300		300ul		//buadrate=300
#define UART_BR_600		600ul		//buadrate=600
#define UART_BR_1200		1200ul		//buadrate=1200
#define UART_BR_2400		2400ul		//buadrate=2400
#define UART_BR_4800		4800ul		//buadrate=4800
#define UART_BR_9600		9600ul		//buadrate=9600
#define UART_BR_19200		19200ul		//buadrate=19200
#define UART_BR_38400		38400ul		//buadrate=38400
#define UART_BR_57600		57600ul		//buadrate=57600
#define UART_BR_115200		115200ul	//buadrate=115200

void uart_init(unsigned short bps);

void uart_send_bit(unsigned char bit_t);		//send a bit

//1 start bit (low)
//8 data bit
//1 stop bit (high)
void uart_putch(unsigned char ch);

void uart_putstr(unsigned char *str);
