/*
 * File:   main.c
 * Author: aizaz
 *
 * Created on September 24, 2023, 2:21 PM 
 * 
 * Master Mode
 * 
 */


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
    TRISBbits.RB5 = 0;
    TRISBbits.RB6 = 0;
    TRISBbits.RB7 = 0;
    INIT_SPI();
    INIT_INTERRUPT();
    LATAbits.LA5 = 0; // SS

    while (1) {
        LATBbits.LATB5 ^= 1;
        WRITE_SPI(0x55);
        __delay_ms(500);
        
        WRITE_SPI(0x32);
        __delay_ms(500);
        WRITE_SPI(0xAB);
        
        //        WRITE_SPI(0b11110000);
        //        __delay_ms(2000);
        //        if (received_data)
        //        {
        //            LATDbits.LATD0 ^= 1; //Master Received
        //        }

        //WRITE_SPI(0b01010101);


        //__delay_ms(500);
    }
    return;
}

void __interrupt() ISR(void) {
    if (PIR1bits.SSPIF) {
        INTCONbits.GIE = 0;
        LATDbits.LATD0 = ~LATDbits.LATD0; //Master Received
        received_data = READ_SPI();
        //SSPBUF = 0x00;
        //LATDbits.LATD0 = 0; //Master Received DATA 
        INTCONbits.GIE = 1;
        PIR1bits.SSPIF = 0;
        return;
    }
}

void WRITE_SPI(uchr txdata) {
    SSPBUF = txdata;
    LATBbits.LATB6 ^= 1;
    while (SSPSTATbits.BF == 1); // Wait for SPI interrupt flag
    LATBbits.LATB7 ^= 1;
    //while (!PIR1bits.SSPIF); // Wait for SPI interrupt flag
    LATDbits.LATD1 = ~LATDbits.LATD1; // Master Send
    SSPSTATbits.BF = 0;
    //SSPBUF =0x00;
    //PIR1bits.SSPIF = 0;
}

uchr READ_SPI(void) {
    return SSPBUF;
}

void INIT_SPI(void) {
    TRISCbits.RC7 = 0; // Tx
    TRISBbits.RB0 = 1; // Rx
    TRISBbits.RB1 = 0; // SCLK
    TRISAbits.RA5 = 0; // SS

    ADCON1bits.PCFG = 0b1111; //Making All pins Digital

    SSPSTATbits.SMP = 0; // Input data sampled at middle of data output time
    SSPSTATbits.CKE = 0; // Transmit occurs on transition from Idle to active clock state

    SSPCON1bits.SSPEN = 1; // Enables serial port and configures SCK, SDO, SDI and SS as serial port pins(2)
    SSPCON1bits.CKP = 0; // Idle state for clock is a low level 

    SSPCON1bits.SSPM = 0b0000; // SPI Master mode, clock = FOSC/4(3)
}

void INIT_INTERRUPT(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
    IPR1bits.SSPIP = 1;
}
