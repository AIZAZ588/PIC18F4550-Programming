#include<stdio.h>
#define size 5
int arr_sum(int b[],int l);
int main()
{
    int num[size] = {50,60,70,80,90};
    int sum;
    sum = arr_sum(num,size);
    printf("%d\n",sum);
    return 0;
}
int arr_sum(int b[],int l) 
{
    int sum =0;
    unsigned char i;
    for(i=0; i<l ; i++)
    {
        sum += b[i];
    }
    return sum;
}