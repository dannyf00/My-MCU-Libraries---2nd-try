/***********************************************************************************
Project:          SHTxx demo program (V2.1)
Filename:         SHTxx_Sample_Code.c

Prozessor:        mega128L
Compiler:         icc avr
Cystal:           7.3728MHz

Autor:            fxl
Copyrigth:        (c) Sensirion AG
***********************************************************************************/

//hardware configuration
#define SHT_PORT		PORTB
#define SHT_DDR			DDRB
#define SHT_PORT_IN		PINB
#define SHT_SCK			(1<<0)	//sck pin
#define SHT_DATA		(1<<1)	//data pin

#define SHT_DLY			1
#define SHT_DELAY()		delay(SHT_DLY)
#define SHT_SET(sck)	{IO_OUT(SHT_DDR, sck); IO_SET(SHT_PORT, sck);  SHT_DELAY();}	//set sck
#define SHT_CLR(sck);	{IO_OUT(SHT_DDR, sck); IO_CLR(SHT_PORT, sck);  SHT_DELAY();}	//clear sck
#define SHT_HIGH(data)	{IO_IN(SHT_DDR, data); SHT_DELAY();}	//float data high
#define SHT_LOW(data)	{IO_OUT(SHT_DDR, data); IO_CLR(SHT_PORT, data); SHT_DELAY();}	//drive data low

typedef struct
{ unsigned short i;
  float f;
} value_t;

typedef struct {
	float Temp;
	float Humi;
	float DewPoint;
} SHT_t;

//----------------------------------------------------------------------------------
// modul-var
//----------------------------------------------------------------------------------
//enum {TEMP,HUMI};
#define SHT_TEMP		0
#define SHT_HUMI		1

#define SHT_noACK 		0
#define SHT_ACK   		1
                            //adr  command  r/w
#define SHT_CMD_STATUS_REG_W 0x06   //000   0011    0
#define SHT_CMD_STATUS_REG_R 0x07   //000   0011    1
#define SHT_CMD_MEASURE_TEMP 0x03   //000   0001    1
#define SHT_CMD_MEASURE_HUMI 0x05   //000   0010    1
#define SHT_CMD_RESET        0x1e   //000   1111    0

//----------------------------------------------------------------------------------
unsigned char sht_write(unsigned char value);
//----------------------------------------------------------------------------------
// writes a byte on the Sensibus and checks the acknowledge

//----------------------------------------------------------------------------------
unsigned char sht_read(unsigned char ack);
//----------------------------------------------------------------------------------
// reads a byte form the Sensibus and gives an acknowledge in case of "ack=1"

//----------------------------------------------------------------------------------
void sht_start(void);
//----------------------------------------------------------------------------------
// generates a transmission start
//       _____         ________
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______

//----------------------------------------------------------------------------------
void sht_reset(void);
//----------------------------------------------------------------------------------
// communication reset: DATA-line=1 and at least 9 SCK cycles followed by transstart
//       _____________________________________________________         ________
// DATA:                                                      |_______|
//          _    _    _    _    _    _    _    _    _        ___     ___
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______

//----------------------------------------------------------------------------------
unsigned char sht_softreset(void);
//----------------------------------------------------------------------------------
// resets the sensor by a softreset

//----------------------------------------------------------------------------------
unsigned char sht_read_statusreg(unsigned char *p_value, unsigned char *p_checksum);
//----------------------------------------------------------------------------------
// reads the status register with checksum (8-bit)

//----------------------------------------------------------------------------------
unsigned char sht_write_statusreg(unsigned char *p_value);
//----------------------------------------------------------------------------------
// writes the status register with checksum (8-bit)

//----------------------------------------------------------------------------------
unsigned char sht_measure(unsigned short *p_value, unsigned char *p_checksum, unsigned char mode);
//----------------------------------------------------------------------------------
// makes a measurement (humidity/temperature) with checksum

void sht_calc(float *p_humidity ,float *p_temperature);

//--------------------------------------------------------------------
float sht_calc_dewpoint(float h,float t);
//--------------------------------------------------------------------
// calculates dew point
// input:   humidity [%RH], temperature [?]
// output:  dew point [?]

unsigned char sht_ez(SHT_t * sht_ptr);
