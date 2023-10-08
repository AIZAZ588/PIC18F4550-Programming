//extern volatile __bit WriteSuccessful;
//#define TIMEOUT_COUNT 1000 // Define a timeout count

#define SDA_dir TRISBbits.RB0
#define SCL_dir TRISBbits.RB1

#define LED_DIR TRISD
#define LED     LATD

#define ERROR_DIR TRISBbits.RB7
#define ERROR LATBbits.LB7

#define ACK_DIR TRISBbits.RB6
#define ACK LATBbits.LB6

#define _XTAL_FREQ 4000000
#define Baud_Rate 100000 // 100kHz

void I2C_INIT(void);


//
//unsigned char I2C_Read(void);
//void I2C_Send_ACK(void);
//void I2C_Send_NACK(void);
//void __interrupt() ISR(void);

//void interrupt_init(void);

#define LED1 LATBbits.LB2
#define LED2 LATBbits.LB3
#define LED3 LATBbits.LB4
#define LED4 LATBbits.LB5

//volatile unsigned char Read_data = 0;
void I2C_Master_Init(void);
void I2C_Wait(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_ACK(void);
void I2C_NACK(void);
unsigned char I2C_Write(unsigned char Data);