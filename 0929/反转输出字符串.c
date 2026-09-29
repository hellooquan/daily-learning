#include <stdio.h>
#include <string.h>

void strTran(char *str,int len)
{
    if(len==1||len==0)
        return;
    char tmp;
    tmp=str[0];
    str[0]=str[len-1];
    str[len-1]=tmp;
    strTran(str+1,len-2);
}
int main()
{
    char sstr[]="abcdefg";
    strTran(sstr,strlen(sstr));
    printf("%s\n",sstr);

    return 0;
}