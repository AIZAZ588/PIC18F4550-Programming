/*
 * File:   I2C_Config.c
 * Author: aizaz
 *
 * Created on October 1, 2023, 10:58 AM
 */


#include "I2C_Config.h"
#include <xc.h>
extern volatile unsigned char Read_data;

void interrupt_init(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
    IPR1bits.SSPIP = 1;
}

void __interrupt() ISR(void) {
    if (SSPIF) {
        MATCH = 1;
        if (!R_nW) // Slave Write (Receive)
        {
            char Dummy = SSPBUF; // Dummy Read
            LED = Dummy;
            CKP = 1; // Release The SCL Clock Line
            while (!BF); // Wait Until Completion
            Read_data = SSPBUF; // Read The Buffer Data
            LED = Read_data; // Output The Received Byte
        }
        MATCH = 0;
        CKP = 1; // Release The SCL Clock Line
        SSPIF = 0; // Clear The Interrupt Flag
    }
}

void I2C_INIT(void) {
    SDA_dir = 1; //
    SCL_dir = 1; //

    SSPADD = 0x40; // Writing address for slave mode
    
    SSPSTAT = 0x80; // Disable Slew Rate Control (Standard Mode)
    SSPCON1 = 0x36; // Select & Enable I2C (Slave Mode)
    SSPCON2 = 0x01; // Enable Clock Stretching
}
