#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 8000000

#define DATA PORTD
#define DATA_DIR TRISD

#define RS_DIR TRISBbits.RB2 
#define RS PORTBbits.RB2

#define E_DIR TRISBbits.RB4
#define E PORTBbits.RB4
void INIT_LCD(void);
void CMD_LCD(char);

void DATA_LCD(char);
void LCD_WRITE(char*);

void config() {
    TRISAbits.RA0 = 1;
    ADCON1bits.PCFG = 0b1110; // AN0 is configured 
    ADCON2bits.ADCS = 0b001; // conversion clock select bits 
    ADCON2bits.ACQT = 0b010; // Acquistion time for 8 bit  
    ADCON2bits.ADFM = 1; 
    ADCON0bits.CHS = 0; 
    ADCON0bits.ADON = 1; 
}
unsigned short adc_read(unsigned char channel) {
    ADCON0bits.CHS = channel; 
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1; 
    __delay_us(10); 
    while (ADCON0bits.GO)
        continue; 
    ADCON0bits.ADON = 0;
    return (unsigned short)((ADRESH << 8) | ADRESL); 
}
void main(void) {
   unsigned short data;
   TRISBbits.RB1 = 0;
   INIT_LCD();
   config();
   float voltage;
   char voltage_str[10];
   //LCD_WRITE(" HELLO");
   char new =0;
   while (1) {
        data = adc_read(0);
       while (data > 10 ) {
        voltage = (float)data * (5.0f / 1023.0f); // Scale the ADC reading to the voltage range (5V)
        sprintf(voltage_str, "%.2fV", voltage); // Format the voltage value as a string with 2 decimal places

           //new = data << 8;
           LCD_WRITE(voltage_str);
            PORTBbits.RB1 = 1;
            __delay_ms(5);
            PORTBbits.RB1 = 0;
            CMD_LCD(0b00000001);
            data=0;
        }
        
        __delay_ms(5);
   }
    return;
}
void INIT_LCD(){
    DATA_DIR = 0;
    RS_DIR = 0;
    E_DIR = 0;
    CMD_LCD(0b00000110); // Entry mode Set
    CMD_LCD(0b00001111); // Display ON/OFF
    CMD_LCD(0b00111100); // Set Function
}
void CMD_LCD(char CMD){
    RS = 0;
    E = 1;
    __delay_ms(1);
    DATA = CMD;
    E = 0;
    __delay_ms(5);
}
void DATA_LCD(char CMD){
    RS = 1;
    E = 1;
    __delay_ms(1);
    DATA = CMD;
    E = 0;
    __delay_ms(5);
}
void LCD_WRITE(char* data){
    while (*data != '\0'){
        DATA_LCD(*data);
        ++data;
    }
}