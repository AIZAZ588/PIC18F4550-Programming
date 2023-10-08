#include<stdio.h>
#define __TEST__        0
#define __PACKING__     
#define __STRUCT__      1
typedef unsigned char uint8;
typedef unsigned __int8 s8;

typedef struct
{
    int matches;
    int win;
    int loss;
}states ;


int main(){
    printf("Hello Aizaz!\n");
    ////////////////////////////////////////////////////////////////////
    #if __TEST__
    char x = 0b00000111,b;
    printf("%d\n",x);
    b = x<<1;
    printf("%d\n",b);

    
    // checking of 5th bit is 1 or not
    printf("%d\n",1<<3); //--> 8 (1000) 
    int result;
    result = x & (1<<5); //-->00000111 & 100000 = 0 
    printf("5th bit is : %d\n",result);

    // changing 5th bit and leave the rest as it is 
    x = x | (1<<5);
    printf("value of x : %d\n",x);
#endif
    ///////////////////Packing//////////////////////////
#ifndef __PACKING__
    unsigned int    x;
    unsigned char   a = 50, b = 60 , c = 70, d = 80,test;
    x = (unsigned int)a;
    printf("%d\n",x);
    x = x | (b<<8);
    x = x | (c<<16);
    x = x | (d<<24);

    // Unpacking
    for (int num=24; num>-1; num-=8)
    {
        test = 0xfff & (x>>num);
        printf("Unpacked num is  : %d\n",test);
        // test = 0xfff & (x>>8);
        // printf("Unpacked num is  : %d\n",test);
        // test = 0xfff & (x>>16);
        // printf("Unpacked num is  : %d\n",test);
        // test = 0xfff & (x>>24);
        // printf("Unpacked num is  : %d\n",test);

    }
#endif

#ifdef __STRUCT__
    states pakistan = {5,3,2};
   // states india    = {5,2,3};
    printf("Pakiatan wins are : %d\n",pakistan.win);
    int size=0;
    size = sizeof(pakistan);
    printf("size of paklistan is : %d\n", size);

#endif
    return 0;
}