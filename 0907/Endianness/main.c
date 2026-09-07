#include <stdio.h>

int main(void)
{
    int x= 0x12345678;
    char *ptr=(char *)&x;
    printf("The value is 0x%x\n",*ptr);

    return 0;
}