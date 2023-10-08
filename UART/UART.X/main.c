#include <xc.h>                                                                                                      
#define _XTAL_FREQ 8000000 // 8MHz, used by the delay_ms() function
void init_eusart(unsigned long async_baud_rate){
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 1;
    
    SPBRG = (unsigned char)((( _XTAL_FREQ / 4)/async_baud_rate)-1);
    TXSTAbits.BRGH =1;              // high baud rate
    BAUDCONbits.BRG16 = 1;          // 16 bit baud rate
    TXSTAbits.SYNC = 0;             // Sync =0;
    RCSTAbits.SPEN = 1;             // Enable serial port
    TXSTAbits.TXEN = 1;             // Enable transmssion
    RCSTAbits.CREN = 1;             // Enable continous recepitions
    
    PIR1bits.RC1IF = 0;             // clear flag
    PIE1bits.RCIE = 1;              // set RCIE interrupt enable
    IPR1bits.RCIP = 1;              // high priority
    RCONbits.IPEN = 1;              // Enable priority leveles
    INTCONbits.PEIE =1;             // Enable peripheral interrupt
 
}

void esuart_tx_data(unsigned char uc8_data){
    while(PIR1bits.TXIF == 0);      //wait until TXIF gets low
    TXREG = uc8_data;
}

unsigned char eusart_Rx_data(void){
    while(PIR1bits.RCIF == 0);      // wait until RCIF gets low
    return RCREG;                   // retrive data from reception register
}

void eusat_tx_str(unsigned char *ptr){
    while(*ptr != 0){
     esuart_tx_data(*ptr++);   
    }
}

void main(void){
    unsigned char serial_data;
    init_eusart(115200);
    while(1){
        serial_data = eusart_Rx_data();
        eusat_tx_str(&serial_data);         // Tx same data to pc
    }
}