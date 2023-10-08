/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <xc.h>        /* XC8 General Include File */
#include <stdio.h>
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
#define _XTAL_FREQ 8000000      //Used by the compiler for the delay_ms(x) macro

#define DATA_DIR TRISD
#define DATA PORTD
#define EN_DIR TRISBbits.RB0
#define EN PORTBbits.RB0
#define RS_DIR TRISBbits.RB1
#define RS PORTBbits.RB1

void ADC_INT(void);
unsigned short ADC_READ(void);

void LCD_INT(void); //initialize
void LCD_INST(char cmd);
void LCD_DATA(char data);
void LCD_TEXT(char* text);
void LCD_CURSOR(char col,char line);

void main(void) {
    unsigned short result = 0;
    char buf[15] = {0};
    LCD_INT();
    ADC_INT();
    LCD_TEXT("WELCOME0");
//    LCD_CURSOR(4,2);
//    LCD_TEXT("AIZAZ0");
            
    while (1) {
        LCD_CURSOR(4,2);
        result = ADC_READ();
        sprintf(buf," %d code",result);
        LCD_TEXT(buf);
        __delay_ms(1000);
    }
    return;
}
void ADC_INT(void)
{
    TRISAbits.RA0 = 1;
    ADCON0bits.CHS = 0;
    ADCON1bits.PCFG = 0b1110; //AN0 as ADC
    ADCON2bits.ACQT = 0b010;  //4TAD (Which is greater then 2.48us)
    ADCON2bits.ADCS = 0b100;  //(12*TAD-> 12*1us)
    ADCON2bits.ADFM = 0;
}
unsigned short ADC_READ(void)
{
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
    while(ADCON0bits.DONE);
    unsigned short result = 0;
    result = (unsigned short)(ADRESH<<8)|(unsigned short) ADRESL;
    ADCON0bits.ADON = 0;
    return result;
}
void LCD_CURSOR(char col,char line){
    if (line == 1)
    {
        LCD_INST(0b10000000 | col);
    }
    else if (line == 2)
    {
        LCD_INST(0b11000000 | col);
    }
}
void LCD_TEXT(char* text){
    while(*text != '\0')
    {
        LCD_DATA(*text);
        ++text;
    }
}
void LCD_INT(void){
    DATA_DIR = 0;
    EN_DIR = 0;
    RS_DIR = 0;
    
    //LCD_INST(0b00000001); // clear display
    LCD_INST(0b00111100); // set function
    LCD_INST(0b00000110); // set mode
    LCD_INST(0b00001111); // display on/off
    
    
}
void LCD_INST(char cmd){
    RS = 0;
    EN = 1;
    __delay_ms(1);
     DATA = cmd;
    EN = 0;
    __delay_ms(5); //5ms
    
}
void LCD_DATA(char data){
    EN = 1;
    __delay_ms(1);
     RS = 1;
     DATA = data;
    EN = 0;
    __delay_ms(5);
}
