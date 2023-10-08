/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <xc.h>        /* XC8 General Include File */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
#define _XTAL_FREQ 8000000 //8Mhz     //Used by the compiler for the delay_ms(x) macro

void delay_100ms(int n_100ms) {
    int i;
    for (i = 0; i < n_100ms * 2; i++)
        __delay_ms(50);
}

void main(void) {
    // initialize digital I/O
    TRISDbits.TRISD1 = 0; // PORTD pin 1 as output
    TRISAbits.TRISA1 = 0; // PORTD pin 2 as output
    TRISDbits.TRISD3 = 1; // PORTB pin 4 as input

    while (1) {
        delay_100ms(5);   // delay for 0.5 second

        LATDbits.LATD1 ^= 1;	// toggle the pin D1

        LATAbits.LATA1 = PORTDbits.RD3; // read B4 and write it to D2
        
    }
}
