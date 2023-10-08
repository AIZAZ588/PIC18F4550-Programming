#include <stdio.h>
void data(char* data)
{
    while (*data != NULL)
    {
        printf("%c", *data);
        ++data;
    }
    
}
int main(void)
{
    printf("size of char is : %d \n",sizeof(char));
    data("Hello, World!");
    return 0; 
}
