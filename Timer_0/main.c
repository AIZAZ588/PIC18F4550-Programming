#include #include "interruts.h" #define XTAL_FREQ 4000000 void init_timer_0(void); void main(void) { TRISD = 0; LATD = 0xAA; int_interrupt(); init_timer_0(); while(1); return; } void init_timer_0(void) { T0CONbits.PSA = 0; //ON prescaler T0CONbits.T0PS = 7; T0CONbits.T0SE = 1; T0CONbits.T0CS = 0; T0CONbits.T08BIT = 1; T0CONbits.TMR0ON = 1; } 