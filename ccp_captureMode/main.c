/* * File: main.c * Author: aizaz * * Created on September 8, 2023, 4:30 PM */
 #include 
 #include "interrupt.h"
  #define XTAL_FREQ 4000000
   void ccp_init(void); 
   void TM3_cnfig(void); 
   void main(void) 
   { TRISD = 0; 
   ccp_init();
    TM3_cnfig(); 
	init_interrupt();
	 while(1); return;
	  } 
	  
   void ccp_init(void) 
   
   { 
   TRISCbits.RC2 = 1; // CCP 1 
   CCP1CONbits.CCP1M =0b0100;
    }
    void TM3_cnfig(void)
	 { T3CONbits.RD16 =1;
	  T3CONbits.T3CCP2 =1; 
	  T3CONbits.T3CKPS = 0b10;
	   T3CONbits.TMR3CS =0; 
	   T3CONbits.TMR3ON =1; }
