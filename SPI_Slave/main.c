/*
 * File:   main.c
 * Author: aizaz
 *
 * Created on September 24, 2023, 4:06 PM
 */
//SLAVE Mode


#include <xc.h>
#define _XTAL_FREQ 4000000

typedef unsigned char uchr;

void INIT_SPI(void);
void INIT_INTERRUPT(void);
void WRITE_SPI(uchr);
uchr READ_SPI(void);
void __interrupt() ISR(void);

volatile uchr received_data = 0;

void main(void) {
    TRISD = 0;
    TRISBbits.TRISB5 = 0; // Received Data
    TRISBbits.TRISB6 = 0; // Write Data
    INIT_SPI();
    INIT_INTERRUPT();
    while (1) {
        if (!PORTAbits.RA5) {

            if (received_data) {
                LATD = received_data;}
//            } else {
//                WRITE_SPI(0x32);
//
//            }
        }
        // __delay_ms();
    }
    //__delay_ms(100);


    return;
}

void WRITE_SPI(uchr txdata) {
    LATBbits.LATB6 = 1; // Slave Send
    SSPBUF = txdata;
    while (SSPSTATbits.BF == 0); // Wait for SPI interrupt flag
    LATBbits.LATB6 = 0; // Slave Send
    
}

void __interrupt() ISR(void) {
    if (PIR1bits.SSPIF) {
        INTCONbits.GIE = 0;
        LATBbits.LATB5 ^= 1; //Received Data
        received_data = READ_SPI();
        SSPBUF = 0x00;
        //        LATBbits.LATB5 = 0;
        SSPSTATbits.BF = 0;
        INTCONbits.GIE = 1;
        PIR1bits.SSPIF = 0;
        return;
    }
}

uchr READ_SPI(void) {
    return SSPBUF;
}

void INIT_SPI(void) {
    TRISCbits.RC7 = 0; // Tx
    TRISBbits.RB0 = 1; // Rx
    TRISBbits.RB1 = 1; // SCLK
    TRISAbits.RA5 = 1; // SS

    ADCON1bits.PCFG = 0b1111; //Making All pins Digital

    SSPSTATbits.SMP = 0; // Input data sampled at middle of data output time
    SSPSTATbits.CKE = 0; // Transmit occurs on transition from Idle to active clock state

    SSPCON1bits.SSPEN = 1; // Enables serial port and configures SCK, SDO, SDI and SS as serial port pins(2)
    SSPCON1bits.CKP = 0; // Idle state for clock is a low level 

    SSPCON1bits.SSPM = 0b0100; // SPI Slave mode, clock = SCK pin, SS pin control enabled(3)
}

void INIT_INTERRUPT(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
    IPR1bits.SSPIP = 1;
}
