/*
 * File:   main.c
 * Author: aizaz
 *
 * Created on September 28, 2023, 11:48 AM
 *

#include "I2C_Config.h"
volatile unsigned char Read_data = 0x00;;

#include <xc.h>

void main(void) {
    LED_DIR = 0;
    MATCH_DIR = 0;

    interrupt_init();
    I2C_INIT();
    while (1);
    return;
}
 */

#include <xc.h>
#include <stdint.h>
//#include "config.h"
#define _XTAL_FREQ 4000000 // Fosc
volatile uint8_t RX_Data = 0x00;
//-----------[ Functions Prototypes ]--------------
void I2C_Slave_Init(unsigned char);
void __interrupt() ISR(void);
//==================================================

void main(void) {
    TRISBbits.RB4 = 0;
    TRISBbits.RB5 = 0;
    TRISBbits.RB6 = 0;
    TRISBbits.RB7 = 0;

    TRISD = 0x00;
    LATD = 0x00;
    I2C_Slave_Init(0x40); // Initiate I2C Slave With Address = 64 or 0x40

    while (1) {

    }
    return;
}
//----------------[ END OF MAIN ]-------------------
//==================================================

void __interrupt() ISR(void) {
    if (SSPIF) {
        LATBbits.LB4 = 1;
        CKP = 0; // Hold (Stretch) The Clock Line LOW
        if (SSPOV || WCOL) // Bus Collision or Buffer Overflow
        {
             LATBbits.LB5 = 1;
            char Dummy = SSPBUF; // Read The Last Byte To Clear The Buffer
            SSPOV = 0; // Clear the overflow flag
            WCOL = 0; // Clear the collision bit
            CKP = 1; // Release Clock Line SCL
        }
        if (!R_nW) // Write by master
        {
            
            LATBbits.LB6 = 1;
            //char Dummy = SSPBUF; // Read The Last Byte To Clear The Buffer
            //while (!BF);
            LATD = SSPBUF; // Read The Received Data Byte
            //LATD = RX_Data;
            CKP = 1; // Release Clock Line SCL
        } else if (R_nW) // Read by master
        {
            LATBbits.LB7 = 1;
            char Dummy = SSPBUF; // Read The Last Byte To Clear The Buffer
            BF = 0;
            SSPBUF = RX_Data; // Write Your Data (REMOVE THE DUMMY)
            CKP = 1; // Release Clock Line SCL
            while (BF);
        }
        SSPIF = 0;
    }
}





//void __interrupt() ISR(void) {
//    
//    if (SSPIF) {
//        LATBbits.LB5 = 1;
//        if (!SSPSTATbits.D_nA) { // means only address match occures!
//            LATBbits.LB6 = 1;
//            CKP =0;
//            char Dummy = SSPBUF;
//            LATD = Dummy;
//
//        }
//        if (!R_nW) // Slave Write (Receive)
//        {
//            LATBbits.LB7 = 1;
//            CKP = 0; // Hold The SCL Clock Line
//            RX_Data = SSPBUF; // Read The Buffer Data
//            LATD = RX_Data; // Output The Received Byte
//        }
//         
//         LATBbits.LB4 = 1;
//        CKP = 1; // Release The SCL Clock Line
//        SSPIF = 0; // Clear The Interrupt Flag
//    }
//}
//---------------[ I2C Routines ]-------------------

void I2C_Slave_Init(unsigned char Address) {
    //---[ Configures The I2C In Slave Mode]---
    SSPADD = Address; // Set The I2C Slave Device Address
    SSPSTAT = 0x80;
    SSPCON1 = 0x3E;
    SSPCON2 = 0x01;
    TRISBbits.RB0 = 1; // SCL Set To Input
    TRISBbits.RB1 = 1; // SDA Set To Input
    GIE = 1; // Enable Interrupts
    PEIE = 1;
    SSPIF = 0;
    SSPIE = 1;
    SSPIP = 1;
}