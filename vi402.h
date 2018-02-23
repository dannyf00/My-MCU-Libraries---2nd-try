//header file for vi402
//individual drive for each sigment
//connection:
//port.0 -> A
//port.1 -> B
//...
//port.5 -> F
//port.6 -> G
//port.7 -> DP

//hardware configuration
#define COM_PORT		PORTA
#define COM_DDR			TRISA
#define COM				(1<<0)				//com pin on p1.7

#define DIG0_PORT		PORTB
#define DIG0_DDR		TRISB
#define DIG0			0xff

#define DIG1_PORT		PORTC
#define DIG1_DDR		TRISC
#define DIG1			0xff

//#define DIG2_PORT		P3
//#define DIG2_DDR		P3
//#define DIG2			0xff

//#define DIG3_PORT		P1
//#define DIG3_DDR		P1
//#define DIG3			0x7f

#define DIG_NUMBER		4
//end hardware configuration

typedef union {
    unsigned char dig[DIG_NUMBER];
    unsigned long ul;
} VSEG_TYPE;

extern unsigned char vRAM[DIG_NUMBER];

void lcd_init(void);

//display vSEG
void lcd_display(void);

//translates vram to vseg
void vRAM2SEG(void);
