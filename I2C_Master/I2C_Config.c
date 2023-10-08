/*
 * File:   I2C_Config.c
 * Author: aizaz
 *
 * Created on October 1, 2023, 10:58 AM
 */


#include "I2C_Config.h"
#include <xc.h>
//extern volatile __bit WriteSuccessful;

//void interrupt_init(void) {
//    INTCONbits.GIE = 1;
//    INTCONbits.PEIE = 1;
//    PIR1bits.SSPIF = 0;
//    PIE1bits.SSPIE = 1;
//    IPR1bits.SSPIP = 1;
//}
//-------------------------------------------------------------------------

//==================== Master I2C code=========================

void I2C_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
void I2C_Start()
{
  //---[ Initiate I2C Start Condition Sequence ]---
  I2C_Wait();
  SEN = 1;
}

void I2C_Stop()
{
  //---[ Initiate I2C Restart Condition Sequence ]---
  I2C_Wait();
  RSEN = 1;
}
void I2C_ACK(void)
{
  //---[ Send ACK - For Master Receiver Mode ]---
  I2C_Wait();
  ACKDT = 0; // 0 -> ACK, 1 -> NACK
  ACKEN = 1; // Send ACK Signal!
}
void I2C_NACK(void)
{
  //---[ Send NACK - For Master Receiver Mode ]---
  I2C_Wait();
  ACKDT = 1; // 1 -> NACK, 0 -> ACK
  ACKEN = 1; // Send NACK Signal!
}
unsigned char I2C_Write(unsigned char Data)
{
  //---[ Send Byte, Return The ACK/NACK ]---
  I2C_Wait();
  SSPBUF = Data;
  I2C_Wait();
  return ACKSTAT;
}

void I2C_INIT(void) {
    SDA_dir = 1;
    SCL_dir = 1;

    //SSPADD = _XTAL_FREQ / (4 * (Baud_Rate)) - 1;
    SSPCON1 = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPADD = ((_XTAL_FREQ / 4) / Baud_Rate) - 1;

    //    SSPSTATbits.SMP = 0; // Slew rate control disabled for Standard Speed mode (100 kHz and 1 MHz)
    //    SSPCON1bits.SSPEN = 1;
    //    SSPCON1bits.SSPM = 0b1000; //  I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))(2,3)
    TRISBbits.RB5 = 0;
    TRISBbits.RB4 = 0;
    TRISBbits.RB3 = 0;
    TRISBbits.RB2 = 0;
}

//-------------------------------------------------------------------------
















//
////void __interrupt() ISR(void) {
////    if (PIR1bits.SSPIF) {
////        if (SSPSTATbits.BF)
////        {
////            LED = SSPBUF;
////            //PIR1bits.SSPIF =0;
////        }
////
////    }
////}
//
//void I2C_Master_Wait() {
//    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //  00000100(R/W bit) ,  00011111.
//}
//
//__bit I2C_Write(unsigned char address, unsigned char *data, unsigned char datasize) {
//
//    //--------------- Start I2C -------------------------
//    //    while (SSPSTATbits.BF); // wait for buffer to get free
//    I2C_Master_Wait();
//
//    SSPCON2bits.SEN = 1; //  Initiate Start condition on SDA and SCL pins. Automatically cleared by hardware
//    //    while (!SSPIF); // if this does not work then use BF(is occure at rising clk))(SSPIF occures at advance falling edge )
//    //    PIR1bits.SSPIF = 0;
//    I2C_Master_Wait();
//    LED1 = 1;
//
//    //while (SSPCON2bits.SEN); // if this does not work then use BF(is occure at rising clk))(SSPIF occures at advance falling edge )
//
//
//    if (PIR2bits.BCLIF) {
//        PIR2bits.BCLIF = 0;
//        ERROR =1;
//        return WriteSuccessful = 1;
//    }
//
//
//    //---------------- Writer address --------------------
//
//    //while (SSPSTATbits.BF); // wait for buffer to get free
//    SSPBUF = address;
//    I2C_Master_Wait();
//    LED2 = 1;
//    //    while (SSPSTATbits.BF); // at 9th falling edge SSPIF occures (BF occures at 8th falling edge )
//    //    PIR1bits.SSPIF = 0;
//    if (PIR2bits.BCLIF) {
//        PIR2bits.BCLIF = 0;
//        return WriteSuccessful = 0;
//    }
//    if (SSPCON1bits.WCOL) {
//        SSPCON1bits.WCOL = 0;
//        ACK = 1;
//        return WriteSuccessful = 0;
//    }
//
//    //    while (!SSPCON2bits.ACKSTAT);
//
//    //------------------ Sending data ---------------------
//
//
//    //    if (SSPCON2bits.ACKSTAT) {
//    //        SSPCON2bits.PEN = 1;
//    //        while (PEN);
//    //        ACK = 1;
//    //        return WriteSuccessful = 0;
//    //    }
//    //Read_data = SSPBUF;
//    //LED3 = 1;
//    int i;
//    for (i = 0; i < datasize; i++) {
//        //        while (SSPSTATbits.BF); // wait for buffer to get free
//
//        SSPBUF = *data;
//        //        while (SSPSTATbits.BF);
//        I2C_Master_Wait();
//        LED3 = 1;
//        //        PIR1bits.SSPIF = 0;
//        if (PIR2bits.BCLIF) {
//            ACK = 1;
//            PIR2bits.BCLIF = 0;
//            return WriteSuccessful = 0;
//        }
//        if (SSPCON1bits.WCOL) {
//            ACK = 1;
//            SSPCON1bits.WCOL = 0;
//            return WriteSuccessful = 0;
//        }
//
//        //        SSPCON2bits.ACKSTAT = 0;
//        //        while (SSPCON2bits.ACKSTAT);
//        LED = *data;
//        data++;
//    }
//    // LED3 = 1;
//    //---------------------i2c stop ---------------------------
//
//    PEN = 1; // I2C Stop
//    //    while (PEN);
//    I2C_Master_Wait();
//    //    PIR1bits.SSPIF = 0;
//    LED4 = 1;
//    return WriteSuccessful = 1;
//}
//
//void I2C_INIT(void) {
//    SDA_dir = 1; // (Input) This will allow the MSSP module to control the direction of these pins automatically,
//    SCL_dir = 1; // depending on whether the PIC microcontroller is acting as an I2C master or slave.
//    //ADCON1bits.PCFG = 0b1111;
//
//    SSPADD = (_XTAL_FREQ / (4 * Baud_Rate)) - 1; // writting Baud Rate to SSPADD (Master Mode)
//    SSPSTATbits.SMP = 1; // Slew rate control disabled for Standard Speed mode (100 kHz and 1 MHz)
//
//    SSPCON1bits.SSPM = 0b1000; //  I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))(2,3)
//    SSPCON1bits.SSPEN = 1; // Enables the serial port and configures the SDA and SCL pins as the serial port pins(1)
//
//    PIR2bits.BCLIF = 0; //clear flag
//    TRISBbits.RB5 = 0;
//    TRISBbits.RB4 = 0;
//    TRISBbits.RB3 = 0;
//    TRISBbits.RB2 = 0;
//}
//

