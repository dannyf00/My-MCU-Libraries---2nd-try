//header file for max7219/max7221

//hardware configuration
#define MAX7221_CS			(1<<1)			//cs pin for max7221 and load pin on max7219

#define MAX7221_INTSTY_DEFAULT				MAX7221_INTSTY15	//default intensity
#define MAX7221_SCANLIMIT_DEFAULT			MAX7221_SCANLIMIT7	//default scanlimit
//end hardware configuration

//max7221 definitions
#define MAX7221_NOP			0x00			//nop
#define MAX7221_DIG0		0x01			//nop
#define MAX7221_DIG1		0x02			//nop
#define MAX7221_DIG2		0x03			//nop
#define MAX7221_DIG3		0x04			//nop
#define MAX7221_DIG4		0x05			//nop
#define MAX7221_DIG5		0x06			//nop
#define MAX7221_DIG6		0x07			//nop
#define MAX7221_DIG7		0x08			//nop
#define MAX7221_MODE		0x09			//nop
#define MAX7221_INTSTY		0x0a			//nop
#define MAX7221_SCANLIMIT	0x0b			//nop
#define MAX7221_SHUTDOWN	0x0c			//nop
#define MAX7221_TEST		0x0f			//nop

#define MAX7221_INTSTY1		0x00			//intensity 1/16th
#define MAX7221_INTSTY2		0x01			//intensity 2/16th
#define MAX7221_INTSTY3		0x02			//intensity 3/16th
#define MAX7221_INTSTY4		0x03			//intensity 4/16th
#define MAX7221_INTSTY5		0x04			//intensity 5/16th
#define MAX7221_INTSTY6		0x05			//intensity 6/16th
#define MAX7221_INTSTY7		0x06			//intensity 7/16th
#define MAX7221_INTSTY8		0x07			//intensity 8/16th
#define MAX7221_INTSTY9		0x08			//intensity 9/16th
#define MAX7221_INTSTY10	0x09			//intensity 10/16th
#define MAX7221_INTSTY11	0x0a			//intensity 11/16th
#define MAX7221_INTSTY12	0x0b			//intensity 12/16th
#define MAX7221_INTSTY13	0x0c			//intensity 13/16th
#define MAX7221_INTSTY14	0x0d			//intensity 14/16th
#define MAX7221_INTSTY15	0x0e			//intensity 15/16th

#define MAX7221_SCANLIMIT0	0x00			//scanLIMIT limited to dig0
#define MAX7221_SCANLIMIT1	0x01			//scanLIMIT limited to dig0..1
#define MAX7221_SCANLIMIT2	0x02			//scanLIMIT limited to dig0..2
#define MAX7221_SCANLIMIT3	0x03			//scanLIMIT limited to dig0..3
#define MAX7221_SCANLIMIT4	0x04			//scanLIMIT limited to dig0..4
#define MAX7221_SCANLIMIT5	0x05			//scanLIMIT limited to dig0..5
#define MAX7221_SCANLIMIT6	0x06			//scanLIMIT limited to dig0..6
#define MAX7221_SCANLIMIT7	0x07			//scanLIMIT limited to dig0..7

#define MAX7221_TEST_ENABLE	0x01			//enable test mode - all segments on
#define MAX7221_TEST_NORMAL	0x00			//disable test mode and return to normal

//#define max7221_write(cmd, val)	{spi_write(cmd); spi_write(val);}

//initialize the chip - bring it out of shutdown mode
void max7221_init(void);

//send a char to the chip
void max7221_putc(unsigned char str);

//send a string to the chip
void max7221_display(unsigned char *str);

//send a num to the chip
void max7221_display_ul(unsigned long ul);
