//send1 header file

//hardware configuration
#define SEND1_PORT			P2
#define SEND1_DDR			P2
#define SEND1_SCO			(1<<0)		//send1 sck/sdo pin
#define SEND1_DLY			(10)		//time delay to send 1, in us - for 10k/4.7n network
//#define SEND1_DLY			(20)		//time delay to send 1, in us - for 10k/4.7n network
//define SEND1_DLY			(10)		//time delay to send 1, in ms - for 10k/47nf network
//end hardware configuration

//initialize send1
void send1_init(void);

//send a byte
void send1_write(unsigned char dat);
