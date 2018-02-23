//*************************************************************
//i2c_sw header file
//*************************************************************

//hardware configuration
#define I2C_PORT				PORTC		//i2c pins on portc
#define I2C_DIR					TRISC		//i2c_port direction
//#define I2C_SDA 				(1<<4) 		//Data line
//#define I2C_SCL 				(1<<3) 		//Clock Line
//end hardware configuration

#define I2C_ACK					0					//0->ack, per i2c protocol
#define I2C_NOACK				1					//1->no ack, per i2c protocol
#define I2C_SET(bits)			I2C_PORT |= (bits)	//set bits on i2c
#define I2C_CLR(bits)			I2C_PORT &=~(bits)	//clear bits on i2c
#define I2C_FLP(bits)			I2C_PORT ^= (bits)	//flip bits on i2c
#define I2C_OUT(bits)			I2C_DIR &=~(bits)		//set bits to output
#define I2C_HIZ(bits)			I2C_DIR |= (bits)		//set bits to hi-z/input/float
//#define I2C_HIGH(bits)			I2C_SET(bits); I2C_OUT(bits); i2c_delay(1)		//let bits float to high
#define I2C_HIGH(bits)			I2C_HIZ(bits); i2c_delay(1)		//let bits float to high
#define I2C_LOW(bits)			I2C_CLR(bits); I2C_OUT(bits); i2c_delay(1)	//pull bits low
#define I2C_ACK_ERROR	0xf0		//max number of loops before ack times out

#define I2C_TWSR_STATUS_MASK	0xf8		//status mark for twsr
#define I2C_TWSR_START			0x08		//start condition has been sent
#define I2C_TWSR_RESTART		0x10		//a repeated start condition has been sent
#define I2C_TWSR_SLAW_ACK		0x18		//SLA+W has been sent, and acknowledge received
#define I2C_TWSR_SLAW_NOACK		0x20		//SLW+W sent, and no acknowledge received
#define I2C_TWSR_DATA_ACK		0x28		//data has been sent, and acknolwedge received
#define I2C_TWSR_DATA_NOACK		0x30		//data has been sent, and no acknowledge received
#define I2C_TWSR_ARBITRATION	0x38		//arbritration lost
#define I2C_TWSR_ACK			0x08		//acknowledge bit

//initialize i2c
void i2c_init(void);

//-----------------START Condition-----------------------
void i2c_start(void);

//-----------------repeat START Condition-----------------------
void i2c_restart(void);

//------------------STOP Condition--------------------------
void i2c_stop(void);

//-------------------I2C write---------------------------
unsigned char i2c_write(unsigned char dat);

//-------------------I2C read---------------------------
unsigned char i2c_read(unsigned char ack);

//void i2c_delay(unsigned char dly);						//i2c delay. dly not used
#define i2c_delay(n)			delay(n)
