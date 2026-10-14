#include <stdio.h>
#include <string.h>

void delSpace(char str[])
{
    int i=0,j=0;
    while(str[i]!='\0')
    {
        if(str[i]!=' ')
        {
            str[j++]=str[i];
        }
        i++;
    }
    str[j]='\0';
}
int main()
{
    char str[100]="hello world";
    delSpace(str);
    printf("%s\n",str);
}