/*
 * File:   config.c
 * Author: aizaz
 *
 * Created on October 6, 2023, 10:53 PM
 */

#include <xc.h>
#include "config.h"
#include <stdint.h>

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

 void I2C_write1ByteRegister(uint8_t address, uint8_t data) {
    /* Shift the 7-bit address and add a 0 bit to indicate a write operation */
    uint8_t writeAddress = (uint8_t) (address << 1);

    I2C_open();
    I2C_startCondition();

    I2C_sendData(writeAddress);
    if (I2C_getAckstatBit()) {
        return;
    }

    I2C_sendData(data);
    if (I2C_getAckstatBit()) {
        return;
    }

    I2C_stopCondition();
    I2C_close();
}

