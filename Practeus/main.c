/*
 * File:   main.c
 * Author: aizaz
 *
 * Created on January 20, 2024, 12:32 AM
 */


#include <xc.h>
#define _XTAL_FREQ 8000000

//#include "LCD.h"
void ADC_INIT(void){
    TRISAbits.RA0 = 1; 
    ADCON0bits.CHS = 0x0; //ANO
    
    ADCON1bits.PCFG = 0b1110;
    ADCON1bits.VCFG1 = 0; //VSS
    ADCON1bits.VCFG0 = 0; //VDD
    
    ADCON2bits.ADFM = 1; //right justified
    ADCON2bits.ACQT = 0b010;; //4TAD
    ADCON2bits.ADCS = 0b001; // FOSC/8
}

unsigned short ADC_READ(void){
  ADCON0bits.ADON =1;
  ADCON0bits.GO =1;
  while(ADCON0bits.GO);
  __delay_ms(10);
  ADCON0bits.ADON = 0;
  return (unsigned short)((ADRESH<<8) | ADRESL);
    
}
void main(void) {
    ADC_INIT();
    TRISD = 0;
    while(1){
        LATD = ADC_READ();
        __delay_ms(500);
    }
    return;
}
