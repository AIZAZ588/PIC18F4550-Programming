/*
 * File:   main.c
 * Author: aizaz
 *
 * Created on January 19, 2024, 12:51 PM
 */


#include <xc.h>
#define _XTAL_FREQ 8000000
void interrept_init(void){
     TRISBbits.RB0 = 1;
     ADCON1bits.PCFG = 0xf;
     INTCON2bits.RBPU =0;
     INTCONbits.GIE = 1;

     INTCONbits.INT0IE = 1;
     INTCONbits.INT0IF = 0;
    
}

void __interrupt() ISR(void){
    if (INTCONbits.INT0IE && INTCONbits.INT0IF){
        INT0IF =0;
        LATD =~ LATD;

    }
}
void main(void) {
    
    TRISD = 0;
    interrept_init();
    
    while(1){
        LATD = 0x50;
        __delay_ms(500);
    }
    return;
}
