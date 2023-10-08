extern volatile unsigned char Read_data;

#define MATCH_DIR TRISBbits.RB6
#define MATCH LATBbits.LB6

#define SDA_dir TRISBbits.RB0
#define SCL_dir TRISBbits.RB1

#define LED_DIR TRISD
#define LED     PORTD
#define _XTAL_FREQ 4000000
#define Baud_Rate 100000 // 100kHz

void __interrupt() ISR(void);
void I2C_INIT(void);

void interrupt_init(void);
