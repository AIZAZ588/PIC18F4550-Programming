/* * File: interrupts.c * Author: aizaz * * Created on September 9, 2023, 3:44 PM */
#include <xc.h>
void interrupt_init(void)
{ INTCONbits.GIE =1; 
	INTCONbits.PEIE =1; 
}