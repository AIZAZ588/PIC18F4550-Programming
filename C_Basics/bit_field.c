#include <stdio.h>
typedef struct {
    unsigned int b0:1; //-> 1 means bit
    unsigned int b1:2;
    unsigned int b2:3;
    unsigned int b3:4;
}Bit;

int main(){
    printf("hello");
    return 0;
}