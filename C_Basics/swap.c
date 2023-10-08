#include <stdio.h>
void swap(int *val1, int *val2);

int main(){

    int x = 5, y = 7;

    swap(&x,&y);
    printf("value of x after  : %d\n,value of y after : %d\n",x,y);

    return 0;
}
void swap (int *val1, int *val2)
{
    int temp;
    temp = *val1;
    *val1 = *val2; 
    *val2 = temp;
}