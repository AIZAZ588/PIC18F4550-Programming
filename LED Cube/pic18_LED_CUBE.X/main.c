/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <xc.h>        /* XC8 General Include File */
#include "led_cube.h"
#define delay 7
#define Time 20
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
#define _XTAL_FREQ 4000000 //4Mhz     //Used by the compiler for the delay_ms(x) macro

void delay_100ms(int n_100ms) {
    int i;
    for (i = 0; i < n_100ms * 2; i++)
        __delay_ms(50);
}
void Rand(unsigned short*,unsigned char*);
void rain(unsigned short*,unsigned char*);
void slices(unsigned short*,unsigned char*);
void col_rotation(unsigned short*,unsigned char*);
void on_all_leds(unsigned short*,unsigned char*);
void single_layer(unsigned short*,unsigned char*);
void main(void) {
   initalizing_all_ports_dir //Direction - configuration
   
    unsigned short led =0;
    unsigned char LAYER = 0;
   // unsigned char push = 0;
    
    while (1) { 
                delay_100ms(delay); 
                single_layer(&led,&LAYER);
//                Rand(&led,&LAYER);
//                    rain(&led,&LAYER);
//                    slices(&led,&LAYER);
//                    col_rotation(&led,&LAYER);
                   // on_all_leds(&led,&LAYER);

}
}
void Rand(unsigned short* led ,unsigned  char* LAYER)
{
   unsigned char time = 0;
   while(time<Time){
        unsigned char num = 0;
        num = (unsigned char)rand()%15;
        *led  = (unsigned) num;
         *LAYER = (unsigned)num & 0b1111; //--> first 4 LSB
         Update_leds
         Update_layers
         *led=0;*LAYER=0;
          delay_100ms(delay);
         *led  = *led | (unsigned) (num << 4 );
         *LAYER =  num & 0b1111; //-->  4 LSB
          Update_leds
          Update_layers
          *led=0;*LAYER=0;
          delay_100ms(delay);
         *led  = *led | (unsigned) (num << 8 );
         *LAYER =  num & 0b1111; //-->  4 LSB
          Update_leds
          Update_layers
          *led=0;*LAYER=0;
          delay_100ms(delay);
         *led  = *led | (unsigned) (num << 12 );
         *LAYER =  num & 0b1111; //-->  4 LSB
          Update_leds
          Update_layers
         delay_100ms(delay);
   time++;}

}
void rain(unsigned short* led ,unsigned  char* LAYER)
{
    unsigned char time = 0;
    while(time<Time){
        unsigned short num = 0;
        num = (unsigned short)rand();
        *led  = (unsigned) num;
        Update_leds
        *LAYER = 0b0001;
        Update_layers //*LAYER=0;
        delay_100ms(delay);
        *LAYER = 0b0011;
        Update_layers //*LAYER=0;
        delay_100ms(delay);
        *LAYER = 0b0111;
        Update_layers //*LAYER=0;
        delay_100ms(delay);
        *LAYER = 0b1111;
        Update_layers
        delay_100ms(delay);
                *LAYER=0;
        *led=0;
        delay_100ms(delay); 
   time++;
    }
}
void slices(unsigned short* led,unsigned char* LAYER)
{
    unsigned char time =0;
    while(time<Time){
    *led=0b1111;
    *LAYER=0b1000;
    Update_leds
    Update_layers
    *LAYER=0;*led=0;
    delay_100ms(delay);
    *led=0b1111;
    *LAYER=0b0100;
    Update_leds
    Update_layers
    *LAYER=0;*led=0;
    delay_100ms(delay);
    *led=0b1111;
    *LAYER=0b0010;
    Update_leds
    Update_layers
    *LAYER=0;*led=0;
    delay_100ms(delay);
    *led=0b1111;
    delay_100ms(delay);
    *LAYER=0b0001;
    Update_leds
    Update_layers
    *LAYER=0;*led=0;
    delay_100ms(delay);/////////////////
    *led=0b1111;
    *LAYER=0b1111;
    Update_leds
    Update_layers
    delay_100ms(delay);
    *led=0;*LAYER=0;
    *led = *led |(unsigned)(0b1111<<4);
    *LAYER=0b1111;
    Update_leds
    Update_layers
    delay_100ms(delay);
    *led=0;*LAYER=0;
    *led = *led |(unsigned) (0b1111<<8);
    *LAYER=0b1111;
    Update_leds
    Update_layers
    delay_100ms(delay);
    *led=0;*LAYER=0;
    *led = *led |(unsigned)(0b1111<<12);
    *LAYER=0b1111;
    Update_leds
    Update_layers
    *led=0;*LAYER=0;
    time++;
    }
}
void col_rotation(unsigned short* led,unsigned char* LAYER)
{   
    unsigned char shift =0;
    *LAYER = 0xf;
    Update_layers
     while(shift++ < 16){
         *led = *led | (unsigned) (1<<shift);
         Update_leds
         delay_100ms(delay);
          *led = 0;
     }
     }
void on_all_leds(unsigned short* led,unsigned char* LAYER)
{
    
        *LAYER = 0xf;
        Update_layers
        *led  = 0xffff;
         Update_leds
    
    }
void single_layer(unsigned short* led,unsigned char* LAYER)
{
    *led = 0xffff;
    *LAYER = 0b0010;
    Update_layers
    Update_leds
}

