/*
 * File:   main.c
 * Author: aizaz
 *
 * Created on September 28, 2023, 11:48 AM
 */


#include <xc.h>
//#include "config.h"
#include <stdint.h>


//#define I2C_RW_BIT 1 
#define _XTAL_FREQ 8000000
#define Baud_Rate 100000 // 100kHz

//----------functions----------------- 

void port_initalization(void);
void i2c_initalization(void);
static void I2C_interruptFlagPolling(void);
static void I2C_open(void);
static void I2C_close(void);
static void I2C_startCondition(void);
static void I2C_stopCondition(void);
static void I2C_sendData(uint8_t byte);
static uint8_t I2C_getAckstatBit(void);
static void I2C_write1ByteRegister(uint8_t address, uint8_t data);

void main(void) {
    TRISD = 0x00;
    LATD = 0x00;
    TRISBbits.RB2 = 0;
    TRISBbits.RB3 = 0;
    TRISBbits.RB4 = 0;
    TRISBbits.RB5 = 0;
    TRISBbits.RB6 = 0;
    TRISBbits.RB7 = 0;
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    port_initalization();
    i2c_initalization();
    I2C_write1ByteRegister(0x40, 0xAB);
    LATD = 0xAB;

    while (1);// {
//        I2C_write1ByteRegister(0x40, 0xAB);
//        LATD = 0xAB;
//        __delay_ms(500);
//        LATD = 0x00;
//        LB2 = LB3 = LB4 = LB5 = LB6 = LB7 = 0;
//        __delay_ms(500);
//    }

    return;
}

void port_initalization(void) {
    ADCON1bits.PCFG = 0xF;
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
}

void i2c_initalization(void) {
    SSPCON1bits.SSPM3 = 1; // Master Mode
    SSPADD = (_XTAL_FREQ / (Baud_Rate * 4)) - 1;
}

static void I2C_interruptFlagPolling(void) {
    /* Polling Interrupt Flag */

    while (!PIR1bits.SSPIF) {
        ;
    }
    /* Clear the Interrupt Flag */
    PIR1bits.SSPIF = 0;
}

static void I2C_open(void) {
    /* Clear IRQ */
    PIR1bits.SSPIF = 0;
    /* I2C Master Open */
    SSPCON1bits.SSPEN = 1;
}

static void I2C_close(void) {
    /* Disable I2C1 */
    SSPCON1bits.SSPEN = 0;
}

static void I2C_startCondition(void) {
    /* Start Condition*/
    SSPCON2bits.SEN = 1;
    I2C_interruptFlagPolling();
}

static void I2C_stopCondition(void) {
    /* Stop Condition */
    SSPCON2bits.PEN = 1;
    I2C_interruptFlagPolling();
}

static void I2C_sendData(uint8_t byte) {
    SSPBUF = byte;
    I2C_interruptFlagPolling();
}

static uint8_t I2C_getAckstatBit(void) {
    /* Return ACKSTAT bit */
    return SSPCON2bits.ACKSTAT;
}

static void I2C_write1ByteRegister(uint8_t address, uint8_t data) {
    /* Shift the 7-bit address and add a 0 bit to indicate a write operation */
    //uint8_t writeAddress = (uint8_t) (address << 1);
    LATBbits.LB2 = 1;
    I2C_open();
    LATBbits.LB3 = 1;
    I2C_startCondition();
    LATBbits.LB4 = 1;

    I2C_sendData(address);
    if (I2C_getAckstatBit()) {
        LATCbits.LC0 = 1;
        return;
    }
    LATBbits.LB5 = 1;
    I2C_sendData(data);
    if (I2C_getAckstatBit()) {
        LATCbits.LC1 = 1;
        return;
    }
    LATBbits.LB6 = 1;
    I2C_stopCondition();
    I2C_close();
    LATBbits.LB7 = 1;
}
