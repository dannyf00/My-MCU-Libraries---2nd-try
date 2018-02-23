//hardware configuration
#define UART_PORT		P2
#define UART_DDR		P2
#define UART_TX			(1<<0)
#define UART_RX			(1<<1)
//end hardware configuration

#define MSB(word_t)		((word_t) >> 8)			//most significant byte
#define LSB(word_t)		((word_t) & 0x00ff)		//least significant byte

#define UART_9600BPS	(F_CPU / 9600/*-40*/)			//duration per bit, in cpu ticks
#define UART_4800BPS	(F_CPU / 4800/*-40*/)			//duration per bit, in cpu ticks
#define UART_2400BPS	(F_CPU / 2400/*-40*/)			//duration per bit, in cpu ticks
#define UART_1200BPS	(F_CPU / 1200/*-40*/)			//duration per bit, in cpu ticks
//#define UART_300BPS		(F_CPU / 300/*-40*/)			//duration per bit, in cpu ticks
//#define UART_110BPS		(F_CPU / 110/*-40*/)			//duration per bit, in cpu ticks

void uart_init(unsigned short bps);

void uart_send_bit(unsigned char bit_t);		//send a bit

//1 start bit (low)
//8 data bit
//1 stop bit (high)
void uart_putch(unsigned char ch);

void uart_putstr(unsigned char *str);
