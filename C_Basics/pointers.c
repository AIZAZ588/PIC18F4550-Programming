#include<stdio.h>
int main()
{
    int y = 10;
    int *ptr;
    ptr = &y;
    printf(
        "address of y is : %p\n",&y
    );

    printf(
        "address of y is : %p\n",ptr
    );
    printf(
        "value at y is : %d",*ptr
    );
    return 0;
}