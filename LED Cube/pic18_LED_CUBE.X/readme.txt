#include<stdio.h>

int main(){
    unsigned char a,b,c,d=0;
    unsigned int num =0;
    
    num = 0b1111;
    ////////////////////////////packing/////////////////////////////////////////////////
    // num = num | ( a << 7); // starting from lsb 0-->7 ---  This method will only pack      
    // num = num | ( b << 15);                           ---   variables, and is use to
    // num = num | ( c << 23);                           ---   transfer that packet ;
    // num = num | ( d << 31);                           ---   it won`t initalize them
    ////////////////////////////////////////////////////////////////////////////////
    //unpacking
    a =  (num & 0xff);     // --> 0xff is 0b1111 1111 , it will strat from LSB
    b =  ((num>>8) & 0xff);  // & is use to extract the values
    c =  ((num>>16) & 0xff);
    d =  ((num>>24) & 0xff);

    
    printf("value is : %d \n",a);
    printf("value is : %d \n",b);
    printf("value is : %d \n",c);
    printf("value is : %d \n",d);
    

    return 0;
}