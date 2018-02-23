//header file for ad7321

//hardware configuration
#define AD7321_0			(1<<3)
//end hardware configuration

//adc mode + channel
#define AD7321_CTRL_CH0_CH1			0x0100		//fully differential, mode1=1, mode0=0, add0=0
#define AD7321_CTRL_CH0				0x0000		//se, mode1=0, mode0=0, add0=0
#define AD7321_CTRL_CH1				0x0400		//se, mode1=1, mode0=0, add0=0

//power mode
#define AD7321_CTRL_FULLSHUTDOWN	0x80c0		//full shutdown
#define AD7321_CTRL_AUTOSHUTDOWN	0x8080		//auto shutdown
#define AD7321_CTRL_STANDBY			0x8040		//standby
#define AD7321_CTRL_NORMAL			0x8000		//normal model

//coding
#define AD7321_CTRL_SIGNED			0x0020		//coding = 1 -> 2's complement
#define AD7321_CTRL_UNSIGNED		0x0000		//coding = 0 -> straight binary

//reference
#define AD7321_CTRL_EXTREF			0x0000		//ref = 1 -> external reference is used
#define AD7321_CTRL_INTREF			0x0010		//ref = 0 -> internal reference is used

//sequencing
#define AD7321_CTRL_SEQ00			0x0000		//seq=0b00 -> sequencing not used
#define AD7321_CTRL_SEQ				0x0008		//seq=0b10 -> sequencing used
#define AD7321_CTRL_SEQ11			0x000c		//seq=0b11 -> sequencing not used

//default value for control register
//normal mode, ch0, unsigned, internal ref, sequencing not used
#define AD7321_CTRL_DEFAULT			(AD7321_CTRL_NORMAL)


//sequence
#define AD7321_CTRL_NOSEQ			0x00

//select ad7321
#define ad7321_select(cs)	{spi_select(cs);}

//deselect ad7321
#define ad7321_deselect(cs)	{spi_deselect(cs);}

//reset ad7321
void ad7321_init(void);

//send a word to ad7321
unsigned char ad7321_write(unsigned short word_t);

//read a word from ad7321
unsigned short ad7321_read(void);
