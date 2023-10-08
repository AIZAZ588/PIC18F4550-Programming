/* * File: main.c * Author: aizaz * * Created on September 8, 2023, 10:25 PM */ #include #include #define XTAL_FREQ 4000000 void CCP_COMPARE_INIT(void); void TMR_1_INIT(void); void INTE_INIT(void); void __interrupt() ISR(void); void main(void) { TMR_1_INIT(); INTE_INIT(); CCP_COMPARE_INIT(); while(1); return; } void CCP_COMPARE_INIT(void) { TRISCbits.RC2 = 0; //CCP1 CCPR1H =0xAA ; CCPR1L =0xBC; } void TMR_1_INIT(void) { T1CONbits.RD16 = 1; T1CONbits.T1RUN = 1; T1CONbits.T1CKPS = 0b01; T1CONbits.T1OSCEN = 0; T1CONbits.TMR1CS =0; T1CONbits.TMR1ON = 1; } void INTE_INIT(void) { INTCONbits.GIE =1; INTCONbits.PEIE =1; //PIR1bits.TMR1IF =0; // PIE1bits.TMR1IE =1; // IPR1bits.TMR1IP =1; PIR1bits.CCP1IF =0; PIE1bits.CCP1IE =1; IPR1bits.CCP1IP =1; CCP1CONbits.CCP1M =0b0010; } void __interrupt() ISR(void) { if(PIR1bits.CCP1IF) { PIR1bits.CCP1IF =0; LATCbits.LC2 =~LATCbits.LC2; return; } }