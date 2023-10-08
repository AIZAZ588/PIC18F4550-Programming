/* 
 * File:   led_cube.h
 * Author: aizaz
 *
 * Created on January 4, 2023, 9:40 PM
 */

#ifndef LED_CUBE_H
#define	LED_CUBE_H

#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* LED_CUBE_H */

///////////////////EXTRA AVALIBLE PINS/////////////////////

#define TB0 TRISBbits.TRISB0 //----->BJT
#define TB1 TRISBbits.TRISB1 //---> BJT
#define TB2 TRISBbits.TRISB2 // --> main switch (will be conf as input)

#define TE0 TRISEbits.TRISE0 // --> BJT
#define TE1 TRISEbits.TRISE1  //--->BJT
#define TE2 TRISEbits.TRISE2  // --> push button
#define TC7 TRISCbits.TRISC7 //

/////////////////LEDS//////////////////////
#define TA0 TRISAbits.TRISA0 //1
#define TA1 TRISAbits.TRISA1 //2
#define TA2 TRISAbits.TRISA2 //3
#define TA3 TRISAbits.TRISA3 //4
#define TA5 TRISAbits.TRISA5 //5

#define TC1 TRISCbits.TRISC1 //6
#define TC2 TRISCbits.TRISC2 //7
#define TC6 TRISCbits.TRISC6 //8

#define TD0 TRISDbits.TRISD0 //9
#define TD1 TRISDbits.TRISD1 //10
#define TD2 TRISDbits.TRISD2 //11
#define TD3 TRISDbits.TRISD3 //12
#define TD4 TRISDbits.TRISD4 //13
#define TD5 TRISDbits.TRISD5 //14
#define TD6 TRISDbits.TRISD6 //15
#define TD7 TRISDbits.TRISD7 //16

/////////////led latch////////////////
#define a0 LATAbits.LATA0
#define a1 LATAbits.LA1
#define a2 LATAbits.LA2
#define a3 LATAbits.LA3
#define a5 LATAbits.LA5

#define c1 LATCbits.LC1
#define c2 LATCbits.LC2
#define c6 LATCbits.LC6

#define d LATD
#define d0 LATDbits.LATD0
#define d1 LATDbits.LATD1
#define d2 LATDbits.LATD2
#define d3 LATDbits.LATD3
#define d4 LATDbits.LATD4
#define d5 LATDbits.LATD5
#define d6 LATDbits.LATD6
#define d7 LATDbits.LATD7

/////////BJT LATCH///////////
#define L0 LATBbits.LATB0
#define L1 LATBbits.LATB1
#define L2 LATEbits.LE0
#define L3 LATEbits.LE1

///////// SWITCHES///////////
#define SWITCH PORTBbits.RB2
#define push_button PORTEbits.RE2

/////////// /unpacking //////////

#define A0 a0 = (unsigned)(*led >> 0) & 0xff; 
#define A1 a1 = (unsigned)(*led >> 1) & 0xff;
#define A2 a2 = (unsigned)(*led >> 2) & 0xff; 
#define A3 a3 = (unsigned)(*led >> 3) & 0xff;
#define A5 a5 = (unsigned)(*led >> 4) & 0xff;
#define C1 c1 = (unsigned)(*led >> 5) & 0xff;
#define C2 c2 = (unsigned)(*led >> 6) & 0xff;
#define C6 c6 = (unsigned)(*led >> 7) & 0xff;
#define D0 d0 = (unsigned)(*led >> 8) & 0xff;
#define D1 d1 = (unsigned)(*led >> 9) & 0xff;
#define D2 d2 = (unsigned)(*led >> 10) & 0xff;
#define D3 d3 = (unsigned)(*led >> 11) & 0xff;
#define D4 d4 = (unsigned)(*led >> 12) & 0xff;
#define D5 d5 = (unsigned)(*led >> 13) & 0xff;
#define D6 d6 = (unsigned)(*led >> 14) & 0xff;
#define D7 d7 = (unsigned)(*led >> 15) & 0xff;

#define Update_leds A0 A1 A2 A3 A5 C1 C2 C6 D0 D1 D2 D3 D4 D5 D6 D7
////////////////////////////////////////
#define initalizing_all_ports_dir TA1 =0;TA2=0;TA3=0;TA5=0;TB0=0;TB1=0;TC1=0;TC2=0;TC6=0;TE0=0;TE1=0;TB2 = 1;TA0 =0;TRISD =0b00000000;TE2=1;
///////////////////////////////////////////


////////////////////packing///////////////////////////////////////////
//led = led | (a0 >> 0);
//led = led | (a1 >> 1);
//led = led | (a2 >> 2);
//led = led | (a3 >> 3);
//led = led | (a5 >> 4);
//led = led | (c1 >> 5);
//led = led | (c2 >> 6);
//led = led | (c6 >> 7);
//led = led | (PORTD >> 15);


///////////////////////////////////////////////////////////////////////////////////
#define l0 L0 = (unsigned)(*LAYER >> 0) & 0xf;
#define l1 L1 = (unsigned)(*LAYER >> 1) & 0xf;
#define l2 L2 = (unsigned)(*LAYER >> 2) & 0xf;
#define l3 L3 = (unsigned)(*LAYER >> 3) & 0xf;

#define Update_layers l0 l1 l2 l3


   
